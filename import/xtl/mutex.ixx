module;
#include <mutex>
export module xox.core.xtl.mutex;
namespace xox {
	using Mutex = std::mutex;
	using RecursiveMutex = std::recursive_mutex;
}