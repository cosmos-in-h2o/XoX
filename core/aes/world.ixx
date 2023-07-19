module;
#include <entt/entt.hpp>
#include <xox/xox_def.hpp>
export module xox.core.aes.world;

namespace xox {
	export using atom = entt::entity;

	export class XOX_API World {
		friend class Atom;
	private:
		entt::registry _registry;
		entt::registry& _getReg();
	public:
		World() = default;
		~World() = default;
		
		atom createAtom();
		template<typename...T_>
		auto getView() {
			return this->_registry.view<T_...>();
		}
		template<typename...T_>
		void destroyAtoms() {
			this->_registry.destroy<T_...>();
		}
	};
}