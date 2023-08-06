#ifndef XOX_MEMORY_HEADER
#define XOX_MEMORY_HEADER
#define XOX_ALIGNMENT 16
namespace xox {
struct Memory {
  static void *allocate(size_t size);
  static void *reallocate(void *ptr, size_t size);
  static void deallocate(void *ptr);
  static void *allocate_aligned(size_t size, size_t alignment = XOX_ALIGNMENT);
  static void *reallocate_aligned(void *ptr, size_t size,
                               size_t alignment = XOX_ALIGNMENT);
  static void deallocate_aligned(void *ptr, size_t alignment = XOX_ALIGNMENT);

  static void *new_obj(size_t size);
  static void delete_obj(void *ptr);
  static void *new_obj_aligned(size_t size, size_t alignment = XOX_ALIGNMENT);
  static void delete_obj_aligned(void *ptr, size_t alignment = XOX_ALIGNMENT);
};
} // namespace xox

#endif // !XOX_MEMORY_HEADER
