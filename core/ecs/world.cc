module;
#include <entt/entt.hpp>
module xox.core.ecs;

namespace xox {
	Atom World::createAtom(){
		return this->_registry.create();
	}

	void World::destoryAtom(Atom atom){
		this->_registry.destroy(atom);
	}
}
