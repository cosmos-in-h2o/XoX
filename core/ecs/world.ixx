module;
#include <entt/entt.hpp>
#include <xox/xox_def.hpp>
export module xox.core.ecs;

namespace xox {
	export using Atom=entt::entity;
	export class XOX_API World {
	private:
		entt::registry _registry;
	public:
		World() = default;
		~World() = default;
		
		//创建原子
		Atom createAtom();
		//销毁单个原子
		void destoryAtom(Atom atom);

		//获取视图
		template<typename...T_>
		decltype(auto) getView() {
			return this->_registry.view<T_...>();
		}
		//删除含有相应电子的所有原子
		template<typename...ET_>
		void destroyAtoms() {
			auto view = this->_registry.view<ET_...>();
			this->_registry.destroy(view.begin(), view.end());
		}
		//为原子添加电子
		template<typename ET_,typename...AT_>
		ET_& addElectronFor(Atom atom,AT_&&... args) {
			return this->_registry.emplace<ET_>(atom,std::forward<AT_>(args)...);
		}
		//原子是否拥有这些电子
		template<typename ...ET_>
		bool hasAnyElectronIn(Atom atom) {
			return this->_registry.any_of<ET_...>(atom);
		}
		//原子是否拥有这些电子
		template<typename ...ET_>
		bool hasElectronIn(Atom atom) {
			return this->_registry.all_of<ET_...>(atom);
		}
		//获取原子的某个电子
		template<typename ET_>
		ET_& getElectronIn(Atom atom) {
			return this->_registry.get<ET_>(atom);
		}
	};
}
