module;
#include <xox/xox_def.hpp>
#include <atomic> //std::atomic
export module xox.core.xtl.safe_refcount;

// Design goals for these classes:
// - No automatic conversions or arithmetic operators,
//   to keep explicit the use of atomics everywhere.
// - Using acquire-release semantics, even to set the first value.
//   The first value may be set relaxedly in many cases, but adding the distinction
//   between relaxed and unrelaxed operation to the interface would make it needlessly
//   flexible. There's negligible waste in having release semantics for the initial
//   value and, as an important benefit, you can be sure the value is properly synchronized
//   even with threads that are already running.

// These are used in very specific areas of the engine where it's critical that these guarantees are held
namespace xox {
	export template <class T_>
	class SafeNumeric {
		std::atomic<T_> _value;
		static_assert(std::atomic<T_>::is_always_lock_free);
	public:
		_ALWAYS_INLINE_ void set(T_ value) {
			_value.store(value, std::memory_order_release);
		}

		_ALWAYS_INLINE_ T_ get() const {
			return _value.load(std::memory_order_acquire);
		}

		_ALWAYS_INLINE_ T_ increment() {
			return _value.fetch_add(1, std::memory_order_acq_rel) + 1;
		}

		// Returns the original value instead of the new one
		_ALWAYS_INLINE_ T_ postincrement() {
			return _value.fetch_add(1, std::memory_order_acq_rel);
		}

		_ALWAYS_INLINE_ T_ decrement() {
			return _value.fetch_sub(1, std::memory_order_acq_rel) - 1;
		}

		// Returns the original value instead of the new one
		_ALWAYS_INLINE_ T_ postdecrement() {
			return _value.fetch_sub(1, std::memory_order_acq_rel);
		}

		_ALWAYS_INLINE_ T_ add(T_ value) {
			return _value.fetch_add(value, std::memory_order_acq_rel) + value;
		}

		// Returns the original value instead of the new one
		_ALWAYS_INLINE_ T_ postadd(T_ value) {
			return _value.fetch_add(value, std::memory_order_acq_rel);
		}

		_ALWAYS_INLINE_ T_ sub(T_ value) {
			return _value.fetch_sub(value, std::memory_order_acq_rel) - value;
		}

		_ALWAYS_INLINE_ T_ bit_or(T_ value) {
			return _value.fetch_or(value, std::memory_order_acq_rel);
		}
		_ALWAYS_INLINE_ T_ bit_and(T_ value) {
			return _value.fetch_and(value, std::memory_order_acq_rel);
		}

		_ALWAYS_INLINE_ T_ bit_xor(T_ value) {
			return _value.fetch_xor(value, std::memory_order_acq_rel);
		}

		// Returns the original value instead of the new one
		_ALWAYS_INLINE_ T_ postsub(T_ value) {
			return _value.fetch_sub(value, std::memory_order_acq_rel);
		}

		_ALWAYS_INLINE_ T_ exchange_if_greater(T_ value) {
			while (true) {
				T_ tmp = _value.load(std::memory_order_acquire);
				if (tmp >= value) {
					return tmp; // already greater, or equal
				}

				if (_value.compare_exchange_weak(tmp, value, std::memory_order_acq_rel)) {
					return value;
				}
			}
		}

		_ALWAYS_INLINE_ T_ conditional_increment() {
			while (true) {
				T_ c = _value.load(std::memory_order_acquire);
				if (c == 0) {
					return 0;
				}
				if (_value.compare_exchange_weak(c, c + 1, std::memory_order_acq_rel)) {
					return c + 1;
				}
			}
		}

		_ALWAYS_INLINE_ explicit SafeNumeric<T_>(T_ value = static_cast<T_>(0)) {
			set(value);
		}
	};

	export class SafeFlag {
		std::atomic_bool _flag;

		static_assert(std::atomic_bool::is_always_lock_free);

	public:
		_ALWAYS_INLINE_ bool is_set() const {
			return _flag.load(std::memory_order_acquire);
		}

		_ALWAYS_INLINE_ void set() {
			_flag.store(true, std::memory_order_release);
		}

		_ALWAYS_INLINE_ void clear() {
			_flag.store(false, std::memory_order_release);
		}

		_ALWAYS_INLINE_ void set_to(bool value) {
			_flag.store(value, std::memory_order_release);
		}

		_ALWAYS_INLINE_ explicit SafeFlag(bool value = false) {
			set_to(value);
		}
	};

	export class SafeRefCount {
		SafeNumeric<uint32_t> _count;

	#ifdef DEV_ENABLED
		_ALWAYS_INLINE_ void _check_unref_sanity() {
			// This won't catch every misuse, but it's better than nothing.
			CRASH_COND_MSG(_count.get() == 0,
				"Trying to unreference a SafeRefCount which is already zero is wrong and a symptom of it being misused.\n"
				"Upon a SafeRefCount reaching zero any object whose lifetime is tied to it, as well as the ref count itself, must be destroyed.\n"
				"Moreover, to guarantee that, no multiple threads should be racing to do the final unreferencing to zero.");
		}
	#endif

	public:
		_ALWAYS_INLINE_ bool ref() { // true on success
			return _count.conditional_increment() != 0;
		}

		_ALWAYS_INLINE_ uint32_t refval() { // none-zero on success
			return _count.conditional_increment();
		}

		_ALWAYS_INLINE_ bool unref() { // true if must be disposed of
#ifdef DEV_ENABLED
			_check_unref_sanity();
#endif
			return _count.decrement() == 0;
		}

		_ALWAYS_INLINE_ uint32_t unrefval() { // 0 if must be disposed of
#ifdef DEV_ENABLED
			_check_unref_sanity();
#endif
			return _count.decrement();
		}

		_ALWAYS_INLINE_ uint32_t get() const {
			return _count.get();
		}

		_ALWAYS_INLINE_ void init(uint32_t value = 1) {
			_count.set(value);
		}
	};

	//游戏资源计数器
	export class ResCounter {
	private:
		std::atomic<uint32_t> _count;
	public:
		ResCounter() :_count(0) {}
		ResCounter(const ResCounter&) = delete;
		ResCounter(ResCounter&&) = delete;
		~ResCounter() = default;

		_FORCE_INLINE_ void ref() {
			this->_count.fetch_add(1, std::memory_order_acq_rel);
		}
		_FORCE_INLINE_ void unref() {
			this->_count.fetch_sub(1, std::memory_order_acq_rel);
		}
		_FORCE_INLINE_ uint32_t get() {
			return this->_count.load();
		}
	};
}