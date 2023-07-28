module;
#include <EASTL/vector.h>
export module xox.core.xtl.vector;
export import xox.core.memory.malloc;
namespace xox {
	export template<typename T_>
	using Vector = eastl::vector<T_>;
}