module;
#include <xox/xox_def.hpp>
export module xox.core.xtl.vector;

namespace xox {
	template <class T_>
	class VectorWriteProxy {
	public:
		_FORCE_INLINE_ T_& operator[](int p_index) {
			CRASH_BAD_INDEX(p_index, ((Vector<T_> *)(this))->_cowdata.size());

			return ((Vector<T_> *)(this))->_cowdata.ptrw()[p_index];
		}
	};

	template <class T_>
	class Vector {
		friend class VectorWriteProxy<T_>;

	public:
		VectorWriteProxy<T_> write;

	private:
		CowData<T_> _cowdata;

	public:
		bool push_back(T_ p_elem);
		_FORCE_INLINE_ bool append(const T_& p_elem) { return push_back(p_elem); } //alias
		void fill(T_ p_elem);

		void remove_at(int p_index) { _cowdata.remove_at(p_index); }
		_FORCE_INLINE_ bool erase(const T_& p_val) {
			int idx = find(p_val);
			if (idx >= 0) {
				remove_at(idx);
				return true;
			}
			return false;
		}

		void reverse();

		_FORCE_INLINE_ T_* ptrw() { return _cowdata.ptrw(); }
		_FORCE_INLINE_ const T_* ptr() const { return _cowdata.ptr(); }
		_FORCE_INLINE_ void clear() { resize(0); }
		_FORCE_INLINE_ bool is_empty() const { return _cowdata.is_empty(); }

		_FORCE_INLINE_ T_ get(int p_index) { return _cowdata.get(p_index); }
		_FORCE_INLINE_ const T_& get(int p_index) const { return _cowdata.get(p_index); }
		_FORCE_INLINE_ void set(int p_index, const T_& p_elem) { _cowdata.set(p_index, p_elem); }
		_FORCE_INLINE_ int size() const { return _cowdata.size(); }
		Error resize(int p_size) { return _cowdata.resize(p_size); }
		Error resize_zeroed(int p_size) { return _cowdata.template resize<true>(p_size); }
		_FORCE_INLINE_ const T_& operator[](int p_index) const { return _cowdata.get(p_index); }
		Error insert(int p_pos, T_ p_val) { return _cowdata.insert(p_pos, p_val); }
		int find(const T_& p_val, int p_from = 0) const { return _cowdata.find(p_val, p_from); }
		int rfind(const T_& p_val, int p_from = -1) const { return _cowdata.rfind(p_val, p_from); }
		int count(const T_& p_val) const { return _cowdata.count(p_val); }

		void append_array(Vector<T_> p_other);

		_FORCE_INLINE_ bool has(const T_& p_val) const { return find(p_val) != -1; }

		void sort() {
			sort_custom<_DefaultComparator<T_>>();
		}

		template <class Comparator, bool Validate = SORT_ARRAY_VALIDATE_ENABLED, class... Args>
		void sort_custom(Args &&...args) {
			int len = _cowdata.size();
			if (len == 0) {
				return;
			}

			T_* data = ptrw();
			SortArray<T_, Comparator, Validate> sorter{ args... };
			sorter.sort(data, len);
		}

		int bsearch(const T_& p_value, bool p_before) {
			return bsearch_custom<_DefaultComparator<T_>>(p_value, p_before);
		}

		template <class Comparator, class Value, class... Args>
		int bsearch_custom(const Value& p_value, bool p_before, Args &&...args) {
			SearchArray<T_, Comparator> search{ args... };
			return search.bisect(ptrw(), size(), p_value, p_before);
		}

		Vector<T_> duplicate() {
			return *this;
		}

		void ordered_insert(const T_& p_val) {
			int i;
			for (i = 0; i < _cowdata.size(); i++) {
				if (p_val < operator[](i)) {
					break;
				}
			}
			insert(i, p_val);
		}

		inline void operator=(const Vector& p_from) {
			_cowdata._ref(p_from._cowdata);
		}

		Vector<uint8_t> to_byte_array() const {
			Vector<uint8_t> ret;
			if (is_empty()) {
				return ret;
			}
			ret.resize(size() * sizeof(T_));
			memcpy(ret.ptrw(), ptr(), sizeof(T_) * size());
			return ret;
		}

		Vector<T_> slice(int p_begin, int p_end = INT_MAX) const {
			Vector<T_> result;

			const int s = size();

			int begin = CLAMP(p_begin, -s, s);
			if (begin < 0) {
				begin += s;
			}
			int end = CLAMP(p_end, -s, s);
			if (end < 0) {
				end += s;
			}

			ERR_FAIL_COND_V(begin > end, result);

			int result_size = end - begin;
			result.resize(result_size);

			const T_* const r = ptr();
			T_* const w = result.ptrw();
			for (int i = 0; i < result_size; ++i) {
				w[i] = r[begin + i];
			}

			return result;
		}

		bool operator==(const Vector<T_>& p_arr) const {
			int s = size();
			if (s != p_arr.size()) {
				return false;
			}
			for (int i = 0; i < s; i++) {
				if (operator[](i) != p_arr[i]) {
					return false;
				}
			}
			return true;
		}

		bool operator!=(const Vector<T_>& p_arr) const {
			int s = size();
			if (s != p_arr.size()) {
				return true;
			}
			for (int i = 0; i < s; i++) {
				if (operator[](i) != p_arr[i]) {
					return true;
				}
			}
			return false;
		}

		struct Iterator {
			_FORCE_INLINE_ T_& operator*() const {
				return *elem_ptr;
			}
			_FORCE_INLINE_ T_* operator->() const { return elem_ptr; }
			_FORCE_INLINE_ Iterator& operator++() {
				elem_ptr++;
				return *this;
			}
			_FORCE_INLINE_ Iterator& operator--() {
				elem_ptr--;
				return *this;
			}

			_FORCE_INLINE_ bool operator==(const Iterator& b) const { return elem_ptr == b.elem_ptr; }
			_FORCE_INLINE_ bool operator!=(const Iterator& b) const { return elem_ptr != b.elem_ptr; }

			Iterator(T_* p_ptr) { elem_ptr = p_ptr; }
			Iterator() {}
			Iterator(const Iterator& p_it) { elem_ptr = p_it.elem_ptr; }

		private:
			T_* elem_ptr = nullptr;
		};

		struct ConstIterator {
			_FORCE_INLINE_ const T_& operator*() const {
				return *elem_ptr;
			}
			_FORCE_INLINE_ const T_* operator->() const { return elem_ptr; }
			_FORCE_INLINE_ ConstIterator& operator++() {
				elem_ptr++;
				return *this;
			}
			_FORCE_INLINE_ ConstIterator& operator--() {
				elem_ptr--;
				return *this;
			}

			_FORCE_INLINE_ bool operator==(const ConstIterator& b) const { return elem_ptr == b.elem_ptr; }
			_FORCE_INLINE_ bool operator!=(const ConstIterator& b) const { return elem_ptr != b.elem_ptr; }

			ConstIterator(const T_* p_ptr) { elem_ptr = p_ptr; }
			ConstIterator() {}
			ConstIterator(const ConstIterator& p_it) { elem_ptr = p_it.elem_ptr; }

		private:
			const T_* elem_ptr = nullptr;
		};

		_FORCE_INLINE_ Iterator begin() {
			return Iterator(ptrw());
		}
		_FORCE_INLINE_ Iterator end() {
			return Iterator(ptrw() + size());
		}

		_FORCE_INLINE_ ConstIterator begin() const {
			return ConstIterator(ptr());
		}
		_FORCE_INLINE_ ConstIterator end() const {
			return ConstIterator(ptr() + size());
		}

		_FORCE_INLINE_ Vector() {}
		_FORCE_INLINE_ Vector(std::initializer_list<T> p_init) {
			Error err = _cowdata.resize(p_init.size());
			ERR_FAIL_COND(err);

			int i = 0;
			for (const T& element : p_init) {
				_cowdata.set(i++, element);
			}
		}
		_FORCE_INLINE_ Vector(const Vector& p_from) { _cowdata._ref(p_from._cowdata); }

		_FORCE_INLINE_ ~Vector() {}
	};

	template <class T_>
	void Vector<T_>::reverse() {
		for (int i = 0; i < size() / 2; i++) {
			T_* p = ptrw();
			SWAP(p[i], p[size() - i - 1]);
		}
	}

	template <class T_>
	void Vector<T_>::append_array(Vector<T_> p_other) {
		const int ds = p_other.size();
		if (ds == 0) {
			return;
		}
		const int bs = size();
		resize(bs + ds);
		for (int i = 0; i < ds; ++i) {
			ptrw()[bs + i] = p_other[i];
		}
	}

	template <class T_>
	bool Vector<T_>::push_back(T_ p_elem) {
		Error err = resize(size() + 1);
		ERR_FAIL_COND_V(err, true);
		set(size() - 1, p_elem);

		return false;
	}

	template <class T_>
	void Vector<T_>::fill(T_ p_elem) {
		T_* p = ptrw();
		for (int i = 0; i < size(); i++) {
			p[i] = p_elem;
		}
	}
}