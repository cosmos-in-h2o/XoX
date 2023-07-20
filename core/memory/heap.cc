#include <cstring>
#include <algorithm>
module xox.core.memory.heap;
import xox.core.memory.malloc;

void _alignment(size_t& size){
	if (size % sizeof(void*) != 0)
		size += sizeof(void*) - (size % sizeof(void*));
}

namespace xox {
	void* HeapPool::_allocate(size_t pos, size_t size){
		::_alignment(size);
		return (void*)((size_t)this->_memory+pos);
	}

	HeapPool::HeapPool(size_t size)
		:_from_front(false),_size(size){
		this->_memory = Memory::malloc(size);
		this->_blocks.push_back(MemoryBlock(this->_memory,(void*)(((size_t)(this->_memory)) + size),size));
		if (this->_memory == NULL) {
			
		}
	}

	HeapPool::~HeapPool(){
		Memory::free(this->_memory);
		this->_memory = nullptr;
	}

	//默认分配0.5MB内存
	HeapPool::HeapPool():HeapPool(524288){}

	HeapPool::HeapPool(const HeapPool& hp)
		:_blocks(hp._blocks),_size(hp._size){
		memcpy(this->_memory,hp._memory,hp._size);
	}

	HeapPool::HeapPool(HeapPool&& hp) noexcept
		:_blocks(std::move(hp._blocks)),_size(std::move(hp._size)) {
		this->_memory = hp._memory;
		hp._memory = nullptr;
	}

	void HeapPool::resize(size_t size){
		this->_memory = Memory::realloc(this->_memory, size);
		if (this->_memory == NULL) {

		}
	}

	void* HeapPool::allocate(size_t size){
		int mem_block = 0;
		//内存对齐
		::_alignment(size);
		//从前往后遍历
		if (this->_from_front) {
			for (int i = 0; i < this->_blocks.size(); ++i) {
				if (this->_blocks[i].size >= size) {
					mem_block = i;
					break;
				}
			}
		}
		//从后往前遍历
		else {
			for (int i = this->_blocks.size() - 1; i >= 0; --i) {
				if (this->_blocks[i].size >= size) {
					mem_block = i;
					break;
				}
			}
		}
		//内存不足时
		if (mem_block == 0) {
			//当分配的内存大于内存增加量就将内存上限调到原来内存加要分配的内存加内存增加量
			if (size > HeapPool::increase_bytes)
				this->resize(this->_size + size + HeapPool::increase_bytes);
			else
				this->resize(this->_size + HeapPool::increase_bytes);
			//增加内存后直接进行分配
			//当前只有尾部有内存，所以不管遍历顺序直接从前往后分配,因此结果也应该是未分配前的begin
			void* result = this->_blocks.back().begin;
			this->_blocks.back().begin = (void*)((size_t)(this->_blocks.back()).begin + size);
			return result;
		}
		else {
			//从前往后遍历就从前往后分配，反之亦然
			if (this->_from_front) {
				void* result = this->_blocks[mem_block].begin;
				this->_blocks[mem_block].begin = (void*)((size_t)(this->_blocks[mem_block]).begin + size);
				return result;
			}
			else {
				//是从后往前分配的内存，所以结果应该是被分配块的end加1
				this->_blocks[mem_block].end = (void*)((size_t)(this->_blocks[mem_block]).end - size);
				return (void*)((size_t)this->_blocks[mem_block].end + 1);
			}
			//下一次使用就是换一个方向遍历以提高效率
			this->_from_front = !this->_from_front;
		}
		return nullptr;
	}

	void* HeapPool::reallocate(void* ptr, size_t new_size, size_t old_size) {
	}

	void HeapPool::deallocate(size_t size,void*& mem_ptr){
		//判断是否在范围内
		if ((size_t)mem_ptr<(size_t)this->_memory || (size_t)mem_ptr>(size_t)this->_memory + this->_size) {

		}
		size_t mem_head = (size_t)mem_ptr;
		size_t mem_tail = (size_t)mem_ptr + size;

		int head_block_pos = -1;//头部与mem_ptr相接的block
		int tail_block_pos = -1;//尾部与mem_ptr相接的block

		for (int i = 0; i < this->_blocks.size(); ++i) {
			//尾部相接
			if ((size_t)this->_blocks[i].end + 1 == mem_head)
				tail_block_pos = i;
			//头部相接
			else if ((size_t)this->_blocks[i].begin - 1 == mem_tail)
				head_block_pos = i;

			if (head_block_pos != -1 && tail_block_pos != -1) {
				//当处于两片内存中间时
				//先吞并
				this->_blocks[head_block_pos].end = this->_blocks[tail_block_pos].end;
				//然后移除多余块
				this->_blocks.erase(this->_blocks.begin() + tail_block_pos);
				mem_ptr = nullptr;
				return;
			}
		}
		//只与头部相连
		if (head_block_pos != -1) {
			//直接吞并
			this->_blocks[head_block_pos].begin = mem_ptr;
		}
		//只与尾部相连
		else if (tail_block_pos != 1) {
			//直接吞并
			this->_blocks[tail_block_pos].end = (void*)mem_tail;
		}
		else {
			//开辟新的块
			this->_blocks.push_back(MemoryBlock{ mem_ptr,(void*)mem_tail ,size });
		}
		mem_ptr = nullptr;
	}

	size_t HeapPool::get_size(){
		return this->_size;
	}
}