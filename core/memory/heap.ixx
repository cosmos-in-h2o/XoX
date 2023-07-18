module;
#include <xox/xox_def.hpp>
#include <vector>
export module xox.core.memory.heap;
using namespace std;

static void _alignment(size_t& size);

namespace xox {
	export struct XOX_API MemoryBlock {
		void* begin;
		void* end;
		size_t size;
		MemoryBlock(void* begin = nullptr, void* end = nullptr, size_t size = 0) 
			:begin(begin),end(end),size(size){}
	};

	//特殊的array，实现了HeapPool要求的接口
	export template<typename T_>
	struct SArray {
	private:
		size_t _size;
	};

	//单线程的
	export class XOX_API HeapPool {
	private:
		void* _memory;
		size_t _size;
		vector<MemoryBlock> _blocks{};
		bool _from_front;
		//用于引擎自己多线程分配，非常不安全的函数
		void* _allocate(size_t pos, size_t size);
	public:
		static const size_t increase_bytes = 1024;

		HeapPool(size_t size);
		~HeapPool();
		HeapPool();
		HeapPool(const HeapPool& hp);
		HeapPool(HeapPool&& hp) noexcept;
		void resize(size_t size);
		//指定大小分配
		void* allocate(size_t size);
		size_t get_size();
		//模板函数
		//分配内置指定类型
		template<typename T_> T_* allocate() {
			return this->allocate(sizeof(T_));
		}
		//分配内置指定类型并赋值
		template<typename T_> T_* allocate(T_&& arg) {
			T_* result = this->allocate(sizeof(T_));
			*result = T_(arg);
			return result;
		}
		//分配自定义类型（并赋值）
		template<typename T_, typename...AT_> T_* allocateClass(AT_&&...args) {
			T_* result = this->allocate(sizeof(T_));
			*result = T_(this, std::forward<AT_>(args)...);
			return result;
		}
		template<typename T_> void deallocate(T_*& mem_ptr) {
			//判断是否在范围内
			if ((size_t)mem_ptr<(size_t)this->_memory || (size_t)mem_ptr>(size_t)this->_memory + this->_size) {

			}
			size_t mem_head = (size_t)mem_ptr;
			size_t mem_tail = (size_t)mem_ptr + sizeof(T_);

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
				this->_blocks.push_back(MemoryBlock{ mem_ptr,(void*)mem_tail ,sizeof(T_) });
			}
			mem_ptr = nullptr;
		}
		template<typename CT_> void deallocateClass(CT_*& obj_ptr) {
			//调用析构函数
			obj_ptr->~CT_(this);
			this->deallocate(obj_ptr);
		}
	};
}