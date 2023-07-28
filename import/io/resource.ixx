module;
#include <xox/xox_def.hpp>
#include <xox/xox_res_array.hpp>
#include <vector>
export module xox.core.io.resource;
import xox.core.xtl.safe_refcount;
namespace xox {
	export struct Resource {
		static XOX_RES_ARRAY ref_conters;
	};
	export template<typename RT_>
	class ResPtr {
	private:
		RT_* _ptr;
		uint32_t _pos;
	public:
		explicit ResPtr(RT_* ptr, uint32_t pos) :_ptr(ptr), _pos(pos) {}
		ResPtr(const ResPtr& ref_ptr){

		}
		ResPtr(ResPtr&& ref_ptr) {

		}
		~ResPtr() {
			Resource::ref_conters[_pos].unref();
		}

		_FORCE_INLINE_ RT_* operator->(){
			return this->_ptr;
		}
		_FORCE_INLINE_ RT_& operator*() {
			return *this->_ptr;
		}
		_FORCE_INLINE_ RT_* get_ptr() {
			return this->_ptr;
		}

		void operator=(const ResPtr& ref_ptr) {
		}
		void operator=(ResPtr&& ref_ptr) {
		}
	};

	export template<typename RT_>
	class WeakResPtr {
	private:
		RT_* _ptr;
	public:
		WeakResPtr(ResPtr<RT_>& ref_ptr) {
			this->_ptr = ref_ptr.get_ptr();
		}
		~WeakResPtr() = default;
	};

	template<typename RT_>
	ResPtr<RT_>&& loadResource() {
	
	}
}