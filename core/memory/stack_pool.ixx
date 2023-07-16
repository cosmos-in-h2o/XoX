module;
#include <list>
#include <xox_def.hpp>
export module xox.memory.stack_pool;
import xox.log;
#define ERROR
using std::list;
namespace xox{
    //stack pool
    export class XOX_API SPool{
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
        void create(T_*& ptr){
            if(this->isEnough(sizeof(T_))) {
                ERROR
                return;
            }
            this->ptr_list.push_back((void**)&ptr);
            ptr=(T_*)((size_t)this->memory+this->pos);
            this->pos+=sizeof(T_);
        }
        template<typename T_,typename...AT_>
        void create(T_*& ptr,AT_... args){
            if(this->isEnough(sizeof(T_))) {
                ERROR
                log::error(this,"size is too small.\n");
                return;
            }
            this->ptr_list.push_back((void**)&ptr);
            ptr=(T_*)((size_t)this->memory+this->pos);
            *ptr=T_(this,std::forward<AT_>(args)...);
            this->pos+=sizeof(T_);
        }

        bool isEnough(size_t) const;

        void destroy();

        size_t get_size() const;
    };
}