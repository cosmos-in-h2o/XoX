module;
#include <mimalloc.h>
#include <xox/xox_def.hpp>
module xox.core.memory.malloc;
#define ALIGNMENT 8

namespace xox {
	_FORCE_INLINE_ void* Memory::malloc(size_t size){
		return ::mi_malloc_aligned(size,ALIGNMENT);
	}

	_FORCE_INLINE_ void* Memory::realloc(void* ptr, size_t size){
		return ::mi_realloc_aligned(ptr, size, ALIGNMENT);
	}

	_FORCE_INLINE_ void Memory::free(void* ptr){
		::mi_free_aligned(ptr,ALIGNMENT);
	}
}