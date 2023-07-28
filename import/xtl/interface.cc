#include <EASTL/allocator.h>
#include <mimalloc.h>
#include <xox/xox_def.hpp>

//eastl要求的接口
void* __cdecl operator new[](size_t size, const char* name, int flags, unsigned debugFlags, const char* file, int line) {
	return ::mi_new_aligned(size,XOX_ALIGNMENT);
}
void* __cdecl operator new[](size_t size, size_t alignment, size_t alignmentOffset, const char* pName, int flags, unsigned debugFlags, const char* file, int line) {
	return ::mi_new_aligned(size, alignment);
}