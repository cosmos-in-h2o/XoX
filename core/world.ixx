module;
#include <entt/entt.hpp>
export module xox.core.world;
import xox.core.log;
using namespace entt;

namespace xox {
	export class World {
		friend class Atom;
	private:
		registry _registry;
	public:
		World();
		~World();
		template<typename ET_,typename...AT_>
		void addEntity(AT_&&... args) {
		}
	};
}