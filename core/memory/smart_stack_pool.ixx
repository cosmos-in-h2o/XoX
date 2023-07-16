module;
#include <list>
export module xox.memory.smart_stack_pool;
import xox.log;
#include <xox_def.hpp>
#define ERROR

namespace xox{

    struct ISSPool{
        virtual void destroy(size_t)=0;
    };

    export template<typename T_>
    struct SSPoolPtr{
        friend class SSPool;
    private:
        T_*ptr;
        ISSPool* iss_pool;
        SSPoolPtr(T_*ptr,ISSPool*ss_pool): ptr(ptr), iss_pool(ss_pool){}
    public:
        SSPoolPtr()=default;
        SSPoolPtr(const SSPoolPtr&)=delete;
        SSPoolPtr(SSPoolPtr<T_>&& ss_pool_ptr) noexcept
            :ptr(ss_pool_ptr.ptr),iss_pool(ss_pool_ptr.iss_pool) {
            ss_pool_ptr.ptr=nullptr;
            ss_pool_ptr.iss_pool=nullptr;
        }
        SSPoolPtr& operator=(const SSPoolPtr&)=delete;
        SSPoolPtr& operator=(SSPoolPtr&&)  noexcept {}
        ~SSPoolPtr(){
            iss_pool->destroy(sizeof(T_));
        }
        inline T_& operator*(){
            return *this->ptr;
        }
        inline T_* operator->(){
            return this->ptr;
        }
    };

    //智能栈内存池，需要配合SSPoolPtr来实现自动回收
    export class XOX_API SSPool:public ISSPool{
    private:
        size_t size;//byte number
        size_t pos;
        void* memory;
        void destroy(size_t) override;
    public:
        SSPool();
        explicit SSPool(size_t);
        ~SSPool();
        SSPool(const SSPool&);
        SSPool(SSPool&&) noexcept;

        template<typename T_>
        SSPoolPtr<T_>&& create(){
            if(this->isEnough(sizeof(T_))) {
                ERROR
                log::error(this,"size is too small.\n");
                return SSPoolPtr<T_>();
            }
            auto ptr=(T_*)((size_t)this->memory+this->pos);
            this->pos+=sizeof(T_);
            return SSPoolPtr<T_>(ptr,this);
        }
        template<typename T_,typename...AT_>
        SSPoolPtr<T_>&& create(AT_... args){
            if(this->isEnough(sizeof(T_))) {
                ERROR
                log::error(this,"size is too small.\n");
                return SSPoolPtr<T_>();
            }
            auto ptr=(T_*)((size_t)this->memory+this->pos);
            *ptr=T_(this,std::forward<AT_>(args)...);
            this->pos+=sizeof(T_);
            return SSPoolPtr<T_>(ptr,this);
        }

        void resize(size_t);

        bool isEnough(size_t) const;

        size_t get_size() const;
    };
}

