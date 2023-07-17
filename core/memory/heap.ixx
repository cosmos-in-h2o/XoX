module;
#include <xox/xox_def.hpp>
#include <vector>
export module xox.core.memory.heap;
using namespace std;
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
		template<typename T_> void deallocate(T_* mem_ptr) {}
		template<typename CT_> void deallocateClass(CT_* obj_ptr) {}
	};
}