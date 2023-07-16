module;
#include <cstring>
#include <cstdlib>
module xox.memory.smart_stack_pool;
#define ERROR
namespace xox{
    SSPool::SSPool():size(0),pos(0),memory(nullptr){}
    SSPool::SSPool(size_t size)
            :pos(0){
        this->memory = malloc(size);
        if (this->memory == nullptr) {
            ERROR
            return;
        }
        this->size = size;
    }

    SSPool::~SSPool(){
        if (this->memory != nullptr) {
            free(this->memory);
            this->memory = nullptr;
        }
    }
    SSPool::SSPool(const SSPool& ss_pool): size(ss_pool.size), pos(ss_pool.pos) {
        this->memory = malloc(ss_pool.size);
        if (this->memory == nullptr) {
            ERROR
            return;
        }
        memcpy(memory, ss_pool.memory, ss_pool.size);
    }
    SSPool::SSPool(SSPool&&ss_pool) noexcept
            :size(ss_pool.size),pos(ss_pool.pos),memory(ss_pool.memory) {
        ss_pool.size = 0;
        ss_pool.pos = 0;
        ss_pool.memory = nullptr;
    }

    void SSPool::resize(size_t _size){
        this->memory = realloc(this->memory, _size);
        if (this->memory == nullptr) {
            ERROR
            return;
        }
        this->size = _size;
    }

    inline void SSPool::destroy(size_t _size) {
        this->pos-=_size;
    }

    inline bool SSPool::isEnough(size_t _size) const{
        return this->pos + _size <= this->size;
    }
    inline size_t SSPool::get_size() const{
        return this->size;
    }
}