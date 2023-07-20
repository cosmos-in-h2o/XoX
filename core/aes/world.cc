module;
#include <xox/xox_def.hpp>
#include <entt/entt.hpp>
module xox.core.aes.world;
import xox.core.aes.atom;

namespace xox {
	Atom World::createAtom(){
		return this->_registry.create;
	}

	_FORCE_INLINE_ void World::destoryAtom(Atom atom){
		this->_registry.destory(atom);
	}
}