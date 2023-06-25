module;
#include<list>
#include <cstdlib>
#include <cstring>
#include <iostream>
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

        template<typename T_>
        void push(T_*& ptr,auto... args){
            this->pos+=sizeof(T_);
            if(this->pos>this->size) {
                ERROR
                this->pos -= sizeof(T_);
                log::error(this,"size is too small.\n");
                return;
            }
            this->ptr_list.push_back((void**)&ptr);
            ptr=(T_*)((size_t)this->memory+this->pos);
            *ptr=T_(this,args...);
        }
        bool isEnough(size_t) const;
        void destroy();
        size_t get_size() const;
    };

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
module : private;
namespace xox {
    //stack pool
    SPool::SPool()
            : size(0), pos(0), memory(nullptr) {}

    SPool::SPool(size_t size) : pos(0) {
        this->memory = malloc(size);
        if (this->memory == nullptr) {
            ERROR
            return;
        }
        this->size = size;
    }

    SPool::~SPool() {
        if (this->memory != nullptr) {
            free(this->memory);
            this->memory = nullptr;
        }
    }

    SPool::SPool(const SPool &s_pool)
            : size(s_pool.size), pos(s_pool.pos) {
        this->memory = malloc(s_pool.size);
        if (this->memory == nullptr) {
            ERROR
            return;
        }
        memcpy(memory, s_pool.memory, s_pool.size);
    }

    SPool::SPool(SPool &&s_pool) noexcept
    :size(s_pool.size),pos(s_pool.pos),memory(s_pool.memory){
        if (s_pool.memory != this->memory) {
            this->ptr_list = std::move(s_pool.ptr_list);
            s_pool.size = 0;
            s_pool.pos = 0;
            s_pool.memory = nullptr;
        }
    }

    inline void SPool::resize(size_t _size) {
        this->memory = realloc(this->memory, _size);
        if (this->memory == nullptr) {
            ERROR
            return;
        }
        this->size = _size;
    }

    void SPool::destroy() {
        if (this->ptr_list.size() >= 2)
            this->pos - ((size_t) **this->ptr_list.rbegin() - (size_t) (**++this->ptr_list.rbegin()));
        else if (!this->ptr_list.empty())
            this->pos - (size_t) **this->ptr_list.rbegin();
        else
            return;
        *this->ptr_list.back()=nullptr;
        this->ptr_list.pop_back();
    }

    inline bool SPool::isEnough(size_t _size) const {
        return this->pos + _size <= this->size;
    }

    inline size_t SPool::get_size() const {
        return this->size;
    }
}
namespace xox{
    //smart stack pool

}