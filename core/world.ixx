module;
#include <entt/entt.hpp>
export module xox.core.world;
import xox.thirdparty.entt;
import xox.core.log;
namespace xox {
	export class World {
		friend class Atom;
	private:
		registry _registry;
	public:
		World() = default;
		~World();
		template<typename ET_,typename...AT_>
		void addEntity(AT_&&... args) {
		}
	};
}