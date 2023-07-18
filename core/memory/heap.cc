#include <cstdlib>
#include <cstring>
import xox.core.memory.heap;

void _alignment(size_t& size){
	if (size % sizeof(void*) != 0)
		size += sizeof(void*) - (size % sizeof(void*));
}

namespace xox {
	xox::HeapPool::HeapPool(size_t size)
		:_from_front(false),_size(size){
		this->_memory = malloc(size);
		this->_blocks.push_back(MemoryBlock(this->_memory,(void*)(((size_t)(this->_memory)) + size),size));
		if (this->_memory == NULL) {
			
		}
	}

	xox::HeapPool::~HeapPool(){
		free(this->_memory);
		this->_memory = nullptr;
	}

	//默认分配0.5MB内存
	xox::HeapPool::HeapPool():HeapPool(524288){}

	xox::HeapPool::HeapPool(const HeapPool& hp)
		:_blocks(hp._blocks),_size(hp._size){
		memcpy(this->_memory,hp._memory,hp._size);
	}

	xox::HeapPool::HeapPool(HeapPool&& hp) noexcept
		:_blocks(std::move(hp._blocks)),_size(std::move(hp._size)) {
		this->_memory = hp._memory;
		hp._memory = nullptr;
	}

	void xox::HeapPool::resize(size_t size){
		this->_memory = realloc(this->_memory, size);
		if (this->_memory == NULL) {

		}
	}

	void* HeapPool::allocate(size_t size){
		int mem_block = 0;
		//内存对齐
		::_alignment(size);
		//从前往后遍历
		
		//从后往前遍历
		
		for (int i = this->_blocks.size()-1; i >= 0; --i) {
			if (this->_blocks[i].size >= size) {
				mem_block = i;
				break;
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
			void* result=this->_blocks.back().begin;
			this->_blocks.back().begin=(void*)((size_t)(this->_blocks.back()).begin+size);
			return result;
		}
		else {
			//从前往后遍历就从前往后分配，反之亦然
			if (this->_from_front){
				void* result = this->_blocks[mem_block].begin;
				this->_blocks[mem_block].begin = (void*)((size_t)(this->_blocks[mem_block]).begin + size);
				return result;
			}
			else {
				//是从后往前分配的内存，所以结果应该是被分配块的end加1
				this->_blocks[mem_block].end = (void*)((size_t)(this->_blocks[mem_block]).end - size);
				return (void*)((size_t)this->_blocks[mem_block].end+1);
			}
			//下一次使用就是换一个方向遍历以提高效率
			this->_from_front = !this->_from_front;
		}
		return nullptr;
	}

	size_t HeapPool::get_size(){
		return this->_size;
	}


}