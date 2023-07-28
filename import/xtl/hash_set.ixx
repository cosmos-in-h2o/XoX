module;
#include <EASTL/hash_set.h>
export module xox.core.xtl.set;
export import xox.core.memory.malloc;
namespace xox {
	export template<typename KT_>
	using HashSet = eastl::hash_set<KT_>;
}