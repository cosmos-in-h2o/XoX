module;
#include <xox/xox_def.hpp>
export module xox.core.memory.allocator;
#ifdef XOX_USE_HEAP
import xox.core.memory.heap;
#endif
namespace xox {
	export struct XOX_API DefaultAllocator {
		static void* allocate(size_t size);
		static void* reallocate(void* ptr, size_t new_size);
		static void deallocate(void* ptr);
	};

	//如果使用堆空间
#ifdef XOX_USE_HEAP
	export struct XOX_API HeapAllocator {
		
	};
#endif
}