module ;
#include <functional>
#include <list>
export module xox.delegate;

using namespace std;

namespace xox{
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
        Func(const SFunc &s_func) {// NOLINT
            this->func_list.push_back(s_func);
        }
        Func(SFunc &&s_func) {// NOLINT
            this->func_list.push_back(std::move(s_func));
        }
        Func(const Func& func_obj){
            this->func_list=func_obj.func_list;
        }
        Func(Func&& func_obj) noexcept {
            this->func_list=std::move(func_obj);
        }

        explicit operator function<RT_(AT_...)>() const {
            return this->func_list.front();
        }

        RT_ operator()(AT_&&...args){
            for(auto iter=func_list.begin();iter!=this->func_list.rbegin();iter++){
                *(iter)(std::forward<AT_...>(args...));
            }
            return this->func_list.back()(std::forward<AT_...>(args...));
        }
        inline RT_ invoke(AT_&&...args){*this(std::forward<AT_...>(args...));}

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

        Func&operator=(const Func& func_obj){this->func_list=func_obj.func_list;}
        Func&operator=(Func&& func_obj) noexcept {this->func_list=std::move(func_obj.func_list);}
        Func&operator+=(const Func& func_obj){
            auto temp=func_obj.func_list;
            this->func_list.splice(temp.end(),temp);
        }
        Func&operator+=(Func&& func_obj) noexcept{this->func_list.splice(func_obj.func_list.end(),func_obj.func_list);}
        Func&operator=(const SFunc& func){
            this->func_list.clear();
            this->func_list.push_back(func);
        }
        Func&operator=(SFunc&& func) noexcept{
            this->func_list.clear();
            this->func_list.push_back(std::move(func));
        }
        Func&operator+=(const SFunc& func){this->func_list.push_back(func);}
        Func&operator+=(SFunc&& func) noexcept{this->func_list.push_back(std::move(func));}
    };
}