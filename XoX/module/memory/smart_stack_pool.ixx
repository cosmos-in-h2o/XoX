module;
#include <cstddef>
export module xox.memory.smart_stack_pool;

namespace xox{
    export template<typename T_>
    struct SSPoolPtr{
    private:
        T_*ptr;
    public:
        SSPoolPtr()=default;
        SSPoolPtr(const SSPoolPtr&)=delete;
        SSPoolPtr(SSPoolPtr<T_>&&){}
        SSPoolPtr& operator=(const SSPoolPtr&)=delete;
        SSPoolPtr& operator=(SSPoolPtr&&)  noexcept {}
        ~SSPoolPtr(){}
        inline T_& operator*(){
            return *this->ptr;
        }
        inline T_* operator->(){
            return this->ptr;
        }
    };

    //smart stack pool
    export class SSPool{
    private:
        size_t size;//byte number
        size_t pos;
        void* memory;
    public:
        SSPool();
        explicit SSPool(size_t);
        ~SSPool();
        SSPool(const SSPool&);
        SSPool(SSPool&&) noexcept;
        template<typename T_>
        SSPoolPtr<T_*> push(){

        }

        template<typename T_>
        SSPoolPtr<T_*> push(auto... args){

        }

        void resize(size_t);
        bool isEnough(size_t) const;
        size_t get_size() const;
    };
}