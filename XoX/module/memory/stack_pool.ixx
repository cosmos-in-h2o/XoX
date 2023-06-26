module;
#include<list>
export module xox.memory.stack_pool;
import xox.log;

#define ERROR
using std::list;
namespace xox{
    //stack pool
    export class SPool{
    private:
        size_t size;//byte number
        size_t pos;
        void* memory;
        list<void**> ptr_list;
    public:
        SPool();
        explicit SPool(size_t);
        ~SPool();
        SPool(const SPool&);
        SPool(SPool&&) noexcept;
        void resize(size_t);

        template<typename T_>
        void push(T_*& ptr){
            this->pos+=sizeof(T_);
            if(this->pos>this->size) {
                ERROR
                this->pos -= sizeof(T_);
                return;
            }
            this->ptr_list.push_back((void**)&ptr);
            ptr=(T_*)((size_t)this->memory+this->pos);
        }

        template<typename T_,typename...AT_>
        void push(T_*& ptr,AT_... args){
            this->pos+=sizeof(T_);
            if(this->pos>this->size) {
                ERROR
                this->pos -= sizeof(T_);
                log::error(this,"size is too small.\n");
                return;
            }
            this->ptr_list.push_back((void**)&ptr);
            ptr=(T_*)((size_t)this->memory+this->pos);
            *ptr=T_(this,std::forward<AT_...>(args...));
        }
        bool isEnough(size_t) const;
        void destroy();
        size_t get_size() const;
    };
}