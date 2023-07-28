module;
#include <EASTL/hash_map.h>
export module xox.core.xtl.hash_map;
export import xox.core.memory.malloc;
namespace xox {
	export template<typename KT_, typename VT_>
	using HashMap = eastl::hash_map<KT_, VT_>;
}