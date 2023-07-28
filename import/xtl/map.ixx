module;
#include <EASTL/map.h>
export module xox.core.xtl.map;
export import xox.core.memory.malloc;
namespace xox {
	export template<typename KT_,typename VT_>
	using Map = eastl::map<KT_, VT_>;
}