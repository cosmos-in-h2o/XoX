module;
#include <functional>
#include <list>
export module xox.delegate;
using std::list;
using std::function;
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
        Func(const SFunc &s_func) {
            this->func_list.push_back(s_func);
        }
        Func(SFunc &&s_func) {
            this->func_list.push_back(std::forward<SFunc>(s_func));
        }
        Func(const Func& func_obj){}
        Func(Func&& func_obj){}


        RT_ operator()(AT_...args){}
        inline RT_ invoke(AT_...args){*this(args...);}
    };

    export template<typename ...AT_> using Action=Func<void,AT_...>;
}