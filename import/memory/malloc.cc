module;
#include <mimalloc.h>
#include <xox/xox_def.hpp>
module xox.core.memory.malloc;

namespace xox {
	_FORCE_INLINE_ void* Memory::malloc(size_t size) {
		return ::mi_malloc(size);
	}

	_FORCE_INLINE_ void* Memory::realloc(void* ptr, size_t size) {
		return ::mi_realloc(ptr, size);
	}

	_FORCE_INLINE_ void Memory::free(void* ptr) {
		::mi_free(ptr);
	}
	_FORCE_INLINE_ void* Memory::malloc_aligned(size_t size, size_t alignment) {
		return ::mi_malloc_aligned(size, alignment);
	}

	_FORCE_INLINE_ void* Memory::realloc_aligned(void* ptr, size_t size, size_t alignment) {
		return ::mi_realloc_aligned(ptr, size, alignment);
	}

	_FORCE_INLINE_ void Memory::free_aligned(void* ptr, size_t alignment) {
		::mi_free_aligned(ptr, alignment);
	}
	_FORCE_INLINE_ void* Memory::new_obj(size_t size) {
		return ::mi_new(size);
	}
	_FORCE_INLINE_ void Memory::delete_obj(void* ptr) {
		::mi_free(ptr);
	}
	_FORCE_INLINE_ void* Memory::new_obj_aligned(size_t size, size_t alignment) {
		return ::mi_malloc_aligned(size, alignment);
	}
	_FORCE_INLINE_ void Memory::delete_obj_aligned(void* ptr, size_t alignment) {
		::mi_free_aligned(ptr, alignment);
	}
}