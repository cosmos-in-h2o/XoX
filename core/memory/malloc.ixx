module;
#include <xox/xox_def.hpp>
export module xox.core.memory.malloc;

namespace xox {
	export struct XOX_API Memory {
		static void* malloc(size_t size);
		static void* realloc(void* ptr, size_t size);
		static void free(void* ptr);
	};
};