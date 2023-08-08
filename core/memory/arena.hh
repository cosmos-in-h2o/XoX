#ifndef XOX_ARENA_HEADER
#define XOX_ARENA_HEADER
#include "core/memory/memory.hh"
#include <xox/xox_def.hpp>

namespace xox {
static void _alignment(size_t &size) {
    if (size % sizeof(void *) != 0)
        size += sizeof(void *) - (size % sizeof(void *));
}

static void *_rptr_ptr_add_size(void *ptr, size_t size) {
    return reinterpret_cast<void *>(reinterpret_cast<size_t>(ptr) + size);
}
static void *_rptr_ptr_sub_size(void *ptr, size_t size) {
    return reinterpret_cast<void *>(reinterpret_cast<size_t>(ptr) - size);
}
static size_t _rsize_ptr_add_ptr(void *ptr1, void *ptr2) {
    return reinterpret_cast<size_t>(ptr1) + reinterpret_cast<size_t>(ptr2);
}
static size_t _rsize_ptr_sub_ptr(void *ptr1, void *ptr2) {
    return reinterpret_cast<size_t>(ptr1) - reinterpret_cast<size_t>(ptr2);
}

struct XOX_API MemoryBlock {
    MemoryBlock(void *begin, void *end);
    void *_begin;
    void *_end;
    size_t size();
};
struct XOX_API Blocks {
    Blocks();
    Blocks(size_t size);
    ~Blocks();
    void push_back(const MemoryBlock &block);
    void pop_back();
    void erase(size_t index);
    MemoryBlock &at(size_t index);
    MemoryBlock &operator[](size_t index);
    MemoryBlock &back();
    void resize(size_t size);
    size_t size();

  private:
    MemoryBlock *_blocks;
    size_t _size;
    size_t _use_size;
};
struct XOX_API MemoryFragments {
    MemoryFragments();
    ~MemoryFragments();
    void push_back(void *ptr);
    void pop_back();
    void *&at(size_t index);
    void *&operator[](size_t index);
    size_t size();
    void *&back();

  private:
    void **_ptrs;
    size_t _use_size;
};
struct XOX_API Arena {
    Arena(size_t fragment_size);
    ~Arena();
    void *allocate(size_t size);
    void deallocate(size_t size, void *&mem_ptr);

  private:
    void newFragment();
    void popFragment();
    MemoryFragments _fragments;
    Blocks _blocks;
    size_t _fragment_size;
};
} // namespace xox
#endif // !XOX_ARENA_HEADER
