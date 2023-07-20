module;
#include <xox/xox_def.hpp>
module xox.core.memory.allocator;
import xox.core.memory.malloc;

namespace xox {
	_FORCE_INLINE_ void* DefaultAllocator::allocate(size_t size) {
		return Memory::malloc(size);
	}
	_FORCE_INLINE_ void* DefaultAllocator::reallocate(void* ptr, size_t new_size)
	{
		return Memory::realloc(ptr, new_size);
	}
	_FORCE_INLINE_ void DefaultAllocator::deallocate(void* ptr) {
		Memory::free(ptr);
	}
}