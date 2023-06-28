module ;
#include <list>
#include <functional>
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

        RT_ operator()(AT_&&...args){
            RT_ rt{};
            for (auto &func:this->func_list) {
                rt = func(std::forward<AT_>(args)...);
            }
            return rt;
        }
        RT_ invoke(AT_&&...args){
            RT_ rt{};
            for (auto &func:this->func_list) {
                rt = func(std::forward<AT_>(args)...);
            }
            return rt;
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
            this->func_list=std::move(func_obj.func_list);
            return *this;
        }

        inline Func&operator=(const SFunc& func){
            this->func_list.clear();
            this->func_list.push_back(func);
            return *this;
        }
        inline Func&operator=(SFunc&& func) noexcept{
            this->func_list.clear();
            this->func_list.push_back(std::move(func));
            return *this;
        }
        inline Func&operator+=(const SFunc& func){
            this->func_list.push_back(func);
            return *this;
        }
        inline Func&operator+=(SFunc&& func) noexcept{
            this->func_list.push_back(std::move(func));
            return *this;
        }

        inline void clear() {
            func_list.clear();
        }

        [[nodiscard]] inline size_t get_size() const {
            return func_list.size();
        }

        [[nodiscard]] inline bool empty() const {
            return func_list.empty();
        }
    };

    export template<typename... AT_>
    class Action {
    public:
        typedef list<function<void(AT_...)>> FuncList;//func list
        typedef function<void(AT_...)> SFunc;//single func
    private:
        FuncList func_list;
    public:
        Action()=default;
        ~Action()=default;
        explicit Action(const SFunc &s_func) {
            this->func_list.push_back(s_func);
        }
        explicit Action(SFunc &&s_func) {
            this->func_list.push_back(std::move(s_func));
        }
        Action(const Action& func_obj){
            this->func_list=func_obj.func_list;
        }
        Action(Action&& func_obj) noexcept {
            this->func_list=std::move(func_obj);
        }

        void operator()(AT_&&...args){
            for (auto &func:this->func_list) {
                func(std::forward<AT_>(args)...);
            }
        }
        void invoke(AT_&&...args){
            for (auto &func:this->func_list) {
                func(std::forward<AT_>(args)...);
            }
        }

        inline bool operator>(const Action& func_obj){
            return this->func_list.size()>func_obj.func_list.size();
        }
        inline bool operator<(const Action& func_obj){
            return this->func_list.size()<func_obj.func_list.size();
        }
        inline bool operator>=(const Action& func_obj){
            return this->func_list.size()>=func_obj.func_list.size();
        }
        inline bool operator<=(const Action& func_obj){
            return this->func_list.size()<=func_obj.func_list.size();
        }
        inline bool operator==(const Action& func_obj){
            return this->func_list.size()==func_obj.func_list.size();
        }

        inline Action&operator=(const Action& func_obj){
            this->func_list=func_obj.func_list;
            return *this;
        }
        inline  Action&operator=(Action&& func_obj) noexcept {
            this->func_list=std::move(func_obj.func_list);
            return *this;
        }

        inline Action&operator=(const SFunc& func){
            this->func_list.clear();
            this->func_list.push_back(func);
            return *this;
        }
        inline Action&operator=(SFunc&& func) noexcept{
            this->func_list.clear();
            this->func_list.push_back(std::move(func));
            return *this;
        }
        inline Action&operator+=(const SFunc& func){
            this->func_list.push_back(func);
            return *this;
        }
        inline Action&operator+=(SFunc&& func) noexcept{
            this->func_list.push_back(std::move(func));
            return *this;
        }

        inline void clear() {
            func_list.clear();
        }

        [[nodiscard]] inline size_t get_size() const {
            return func_list.size();
        }

        [[nodiscard]] inline bool empty() const {
            return func_list.empty();
        }
    };
    namespace conv{
        export template<typename... AT_>
        Func<void,AT_...>&& ActionToFunc(Action<AT_...>&&action){

        }
        export template<typename... AT_>
        Func<void,AT_...>&& ActionToFunc(const Action<AT_...>&action){

        }

        export template<typename... AT_>
        Func<AT_...>&& FuncToAction(Func<void,AT_...>&&func){

        }
        export template<typename... AT_>
        Func<void,AT_...>&& FuncToAction(const Func<void,AT_...>&func){

        }
    }
}
