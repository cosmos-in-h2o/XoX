export module xox.log;

namespace xox::log {
    void log(auto color,auto context){}
    export void msg(auto...args){}
    export void warn(auto...args){}
    export void error(auto...args){}
}