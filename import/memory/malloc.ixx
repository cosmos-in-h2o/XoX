module;
#include <xox/xox_def.hpp>
#include <cstddef>
export module xox.core.memory.malloc;

namespace xox {
	export struct XOX_API Memory {
		static void* malloc(size_t size);
		static void* realloc(void* ptr, size_t size);
		static void free(void* ptr);
		static void* malloc_aligned(size_t size, size_t alignment = XOX_ALIGNMENT);
		static void* realloc_aligned(void* ptr, size_t size, size_t alignment = XOX_ALIGNMENT);
		static void free_aligned(void* ptr, size_t alignment = XOX_ALIGNMENT);
		static void* new_obj(size_t size);
		static void delete_obj(void* ptr);
		static void* new_obj_aligned(size_t size, size_t alignment = XOX_ALIGNMENT);
		static void delete_obj_aligned(void* ptr, size_t alignment = XOX_ALIGNMENT);
	};
};
