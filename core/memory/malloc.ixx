module;
#include <xox/xox_def.hpp>
export module xox.core.memory.malloc;

namespace xox {
	export struct XOX_API Memory {
		_FORCE_INLINE_ static void* malloc(size_t size);
		_FORCE_INLINE_ static void* realloc(void* ptr, size_t size);
		_FORCE_INLINE_ static void free(void* ptr);
	};

	export struct XOX_API DefaultAllocator {
		_FORCE_INLINE_ static void* alloc(size_t size);
		_FORCE_INLINE_ static void free(void* ptr);
	};
};