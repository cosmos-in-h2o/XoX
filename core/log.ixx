module;
#include <format>
#include <string_view>
export module xox.core.log;
static void print(std::string_view str) {
    
}
namespace xox::log{
    export template<typename ...AT_> void msg(std::string_view fmt, const AT_&&... args) {
        ::print(std::format(fmt, std::forward<AT_>(args)...));
    }
    export void warn(auto...args);
    export void error(auto...args);
}
