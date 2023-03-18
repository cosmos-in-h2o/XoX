#ifndef DEBUG_H
#define DEBUG_H
#include <Cosmos/core/Core.h>
#include <string>
namespace Cosmos {
	CM_API void Log(...);
	CM_API void Log(std::string format, ...);
}
#endif // !DEBUG_H
