module;
#include <list>
#include <functional>
#include <xox_def.hpp>
export module xox.delegate;
using namespace std;

namespace xox {
	export template<typename RT_, typename... AT_>
	class Func {
	public:
		typedef list<function<RT_(AT_...)>> FuncList;//func list
		typedef function<RT_(AT_...)> SFunc;//single func
	private:
		FuncList func_list;
	public:
		Func()=default;
		~Func()=default;
		explicit Func(const SFunc &s_func) {
			this->func_list.push_back(s_func);
		}
		explicit Func(SFunc &&s_func) {
			this->func_list.push_back(std::move(s_func));
		}
		Func(const Func& func_obj){
			this->func_list=func_obj.func_list;
		}
		Func(Func&& func_obj) noexcept {
			this->func_list=std::move(func_obj);
		}
		template <typename LF_>
		Func(LF_&& lambda_func){
			this->func_list.push_back(std::move(std::forward<LF_>(lambda_func)));
		}

		inline void addFun(const SFunc& func){
			this->func_list.push_back(func);
		}
		inline void addFun(SFunc&& func) noexcept{
			this->func_list.push_back(std::forward<SFunc>(func));
		}

		inline bool operator>(const Func& func_obj){
			return this->func_list.size()>func_obj.func_list.size();
		}
		inline bool operator<(const Func& func_obj){
			return this->func_list.size()<func_obj.func_list.size();
		}
		inline bool operator>=(const Func& func_obj){
			return this->func_list.size()>=func_obj.func_list.size();
		}
		inline bool operator<=(const Func& func_obj){
			return this->func_list.size()<=func_obj.func_list.size();
		}
		inline bool operator==(const Func& func_obj){
			return this->func_list.size()==func_obj.func_list.size();
		}

		inline Func&operator=(const Func& func_obj){
			this->func_list=func_obj.func_list;
			return *this;
		}
		inline  Func&operator=(Func&& func_obj) noexcept {
			this->func_list=std::forward<SFunc>(func_obj.func_list);
			return *this;
		}

		inline Func&operator=(const SFunc& func){
			this->func_list.clear();
			this->func_list.push_back(func);
			return *this;
		}
		inline Func&operator=(SFunc&& func) noexcept{
			this->func_list.clear();
			this->func_list.push_back(std::forward<SFunc>(func));
			return *this;
		}
		template <typename LF_>
		Func&operator=(LF_&& lambda_func){
			this->func_list.clear();
			this->func_list.push_back(std::move(std::forward<LF_>(lambda_func)));
			return *this;
		}
		inline Func&operator+=(const SFunc& func){
			this->func_list.push_back(func);
			return *this;
		}
		inline Func&operator+=(SFunc&& func) noexcept{
			this->func_list.push_back(std::forward<SFunc>(func));
			return *this;
		}

		inline void clear() {
			func_list.clear();
		}
		inline const FuncList &get_func_list() const {
			return this->func_list;
		}
		[[nodiscard]] inline size_t get_size() const {
			return func_list.size();
		}

		[[nodiscard]] inline bool empty() const {
			return func_list.empty();
		}
	};

	template <typename RT_,typename... AT_>
	RT_&& invoke(Func<RT_,AT_...>func,AT_&&...args){
		RT_&& rt{};
		for (auto &item:func.get_func_list()) {
			rt = item(std::forward<AT_>(args)...);
		}
		return std::forward<RT_>(rt);
	}
	template <typename... AT_>
	void invoke(Func<void ,AT_...>func,AT_&&...args){
		for (auto &item:func.get_func_list()) {
			item(std::forward<AT_>(args)...);
		}
	}
}