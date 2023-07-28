module;
#include <EASTL/list.h>
export module xox.core.xtl.list;
export import xox.core.memory.malloc;
namespace xox {
	export template<typename T_>
	using List = eastl::list<T_>;
}