module;
#include <EASTL/set.h>
export module xox.core.xtl.set;
export import xox.core.memory.malloc;
namespace xox {
	export template<typename KT_>
	using Set = eastl::set<KT_>;
}