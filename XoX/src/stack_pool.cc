module;
#include<list>
#include <cstdlib>
#include <cstring>
module xox.memory.stack_pool;
#define ERROR
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