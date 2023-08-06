#include <stdexcept>
#include <xox/arena.hh>
namespace xox {
MemoryBlock::MemoryBlock(void *begin, void *end) : _begin(begin), _end(end) {}
size_t MemoryBlock::size() { return _rsize_ptr_sub_ptr(_end, _begin); }

Blocks::Blocks() : _size(16), _use_size(0) {
    _blocks = static_cast<MemoryBlock *>(
        Memory::allocate_aligned(sizeof(MemoryBlock) * 16));
}
Blocks::Blocks(size_t size) : _size(size), _use_size(0) {
    _blocks = static_cast<MemoryBlock *>(
        Memory::allocate_aligned(sizeof(MemoryBlock) * size));
}
Blocks::~Blocks() { Memory::deallocate_aligned(_blocks); }
void Blocks::push_back(const MemoryBlock &block) {
    if (_use_size >= _size) {
        this->resize(_size * 2);
    }
    *static_cast<MemoryBlock *>(
        _rptr_ptr_add_size(_blocks, _use_size * sizeof(MemoryBlock))) = block;
}
void Blocks::pop_back() { _use_size--; }
void Blocks::erase(size_t index) {
    if (index >= _use_size) {
        return;
    }
    this->pop_back();
    for (; index < _use_size; index++) {
        this->at(index) = this->at(index + 1);
    }
}
MemoryBlock &Blocks::at(size_t index) {
    return *static_cast<MemoryBlock *>(
        _rptr_ptr_add_size(_blocks, index * sizeof(MemoryBlock)));
}
MemoryBlock &Blocks::operator[](size_t index) { return this->at(index); }
void Blocks::resize(size_t size) {
    if (size <= _use_size) {
        return;
    }
    Memory::reallocate_aligned(_blocks, size * sizeof(MemoryBlock));
}
MemoryBlock &Blocks::back() { return this->at(this->size() - 1); }
size_t Blocks::size() { return _use_size; }

MemoryFragments::MemoryFragments() : _use_size(0) {
    _ptrs =
        static_cast<void **>(Memory::allocate_aligned(sizeof(void *) * 128));
}
MemoryFragments::~MemoryFragments() { Memory::deallocate_aligned(_ptrs); }
void MemoryFragments::push_back(void *ptr) {
    *static_cast<void **>(
        _rptr_ptr_add_size(_ptrs, _use_size * sizeof(MemoryBlock))) = ptr;
}
void MemoryFragments::pop_back() { _use_size--; }

void *&MemoryFragments::at(size_t index) {
    return *static_cast<void **>(
        _rptr_ptr_add_size(_ptrs, index * sizeof(MemoryBlock)));
}
void *&MemoryFragments::operator[](size_t index) { return this->at(index); }
size_t MemoryFragments::size() { return _use_size; }
void *&MemoryFragments::back() { return this->at(this->size() - 1); }

Arena::Arena(size_t fragment_size) : _fragment_size(fragment_size) {
    void *ptr = Memory::allocate_aligned(16 * fragment_size);
    _fragments[0] = ptr;
    this->_blocks.push_back(
        MemoryBlock(ptr, _rptr_ptr_add_size(ptr, fragment_size)));
}
Arena::~Arena() {
    for (size_t i = 0; i < _fragments.size(); i++) {
        Memory::deallocate_aligned(_fragments[i]);
    }
}
void *Arena::allocate(size_t size) {
    if (size > _fragment_size) {
        throw std::runtime_error("error:allocate error");
    }
    size_t mem_block = SIZE_MAX;
    // 内存对齐
    _alignment(size);
    // 从前往后遍历
    for (size_t i = 0; i < this->_blocks.size(); ++i) {
        if (_blocks[i].size() >= size) {
            mem_block = i;
            break;
        }
    }
    // 内存不足时
    if (mem_block == SIZE_MAX) {
        mem_block = _blocks.size();
        newFragment();
    }

    void *result = _blocks[mem_block]._begin;
    if (_blocks[mem_block].size() == size) {
        _blocks.erase(mem_block);
    } else {
        _blocks[mem_block]._begin =
            _rptr_ptr_add_size(_blocks[mem_block]._begin, size);
    }
    return result;
}
void Arena::deallocate(size_t size, void *&mem_ptr) {
    // 判断是否在范围内
    bool error = true;
    if (reinterpret_cast<size_t>(mem_ptr) <
            reinterpret_cast<size_t>(_fragments[0]) ||
        reinterpret_cast<size_t>(mem_ptr) >
            reinterpret_cast<size_t>(_fragments[0]) + _fragment_size * 16) {
        error = false;
    }
    if (error) {
        for (size_t i = 1; i < _fragments.size(); i++) {
            if (reinterpret_cast<size_t>(mem_ptr) <
                    reinterpret_cast<size_t>(_fragments[0]) ||
                reinterpret_cast<size_t>(mem_ptr) >
                    reinterpret_cast<size_t>(_fragments[0]) +
                        _fragment_size * 16) {
                error = false;
                break;
            }
        }
    }
    if (error) {
        throw std::runtime_error("error");
    }
    // 要回收的内存的头部
    size_t mem_head = reinterpret_cast<size_t>(mem_ptr);
    // 要回收的内存的尾部
    size_t mem_tail = reinterpret_cast<size_t>(mem_ptr) + size;

    size_t head_block_pos = SIZE_MAX; // 头部与mem_ptr相接的block
    size_t tail_block_pos = SIZE_MAX; // 尾部与mem_ptr相接的block

    for (size_t i = 0; i < this->_blocks.size(); ++i) {
        // 尾部相接
        if (reinterpret_cast<size_t>(_blocks[i]._end) == mem_head)
            tail_block_pos = i;
        // 头部相接
        else if (reinterpret_cast<size_t>(_blocks[i]._begin) == mem_tail)
            head_block_pos = i;
        if (head_block_pos != SIZE_MAX && tail_block_pos != SIZE_MAX) {
            // 当处于两片内存中间时
            // 先吞并
            _blocks[tail_block_pos]._end = _blocks[head_block_pos]._end;
            // 然后移除多余块
            this->_blocks.erase(head_block_pos);
            mem_ptr = nullptr;
            return;
        }
    }
    // 只与头部相连
    if (head_block_pos != SIZE_MAX) {
        // 直接吞并
        _blocks[head_block_pos]._begin = mem_ptr;
    }
    // 只与尾部相连
    else if (tail_block_pos != 1) {
        // 直接吞并
        this->_blocks[tail_block_pos]._end = reinterpret_cast<void *>(mem_tail);
    } else {
        // 开辟新的块
        this->_blocks.push_back(
            MemoryBlock(mem_ptr, reinterpret_cast<void *>(mem_tail)));
    }
    mem_ptr = nullptr;
}
void Arena::newFragment() {
    _fragments.push_back(Memory::allocate_aligned(_fragment_size));
}
void Arena::popFragment() {
    Memory::deallocate_aligned(_fragments.back());
    _fragments.pop_back();
}
} // namespace xox
