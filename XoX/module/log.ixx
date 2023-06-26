export module xox.log;

namespace xox::log{
    export void msg(auto...args);
    export void warn(auto...args);
    export void error(auto...args);
}