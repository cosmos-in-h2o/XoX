module;
#include <entt/entt.hpp>
#include <xox/xox_def.hpp>
export module xox.core.aes.atom;
import xox.core.aes.world;

namespace xox {
	export class XOX_API Atom {
	private:
		atom _atom_handle;
		World* _world_ptr;
	public:
		Atom(atom atom_handle, World* world_ptr);


	};
}