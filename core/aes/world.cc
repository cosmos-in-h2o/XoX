module;
#include <xox/xox_def.hpp>
#include <entt/entt.hpp>
module xox.core.aes.world;

namespace xox {
	_FORCE_INLINE_ entt::registry& World::_getReg() {
		return this->_registry;
	}

	_FORCE_INLINE_ entt::entity World::createAtom(){
		return this->_registry.create();
	}
}