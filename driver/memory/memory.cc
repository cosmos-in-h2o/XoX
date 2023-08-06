#include <mimalloc.h>
#include <xox/memory.hh>

namespace xox {
void *Memory::allocate(size_t size) { return ::mi_malloc(size); }

void *Memory::reallocate(void *ptr, size_t size) {
  return ::mi_realloc(ptr, size);
}

void Memory::deallocate(void *ptr) { ::mi_free(ptr); }
void *Memory::allocate_aligned(size_t size, size_t alignment) {
  return ::mi_malloc_aligned(size, alignment);
}

void *Memory::reallocate_aligned(void *ptr, size_t size, size_t alignment) {
  return ::mi_realloc_aligned(ptr, size, alignment);
}

void Memory::deallocate_aligned(void *ptr, size_t alignment) {
  ::mi_free_aligned(ptr, alignment);
}
void *Memory::new_obj(size_t size) { return ::mi_new(size); }
void Memory::delete_obj(void *ptr) { ::mi_free(ptr); }
void *Memory::new_obj_aligned(size_t size, size_t alignment) {
  return ::mi_malloc_aligned(size, alignment);
}
void Memory::delete_obj_aligned(void *ptr, size_t alignment) {
  ::mi_free_aligned(ptr, alignment);
}
} // namespace xox
