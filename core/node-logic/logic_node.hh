#ifndef XOX_LOGIC_NODE_HEADER
#define XOX_LOGIC_NODE_HEADER
#include <array>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>
#include <xox/xox_def.hpp>
namespace xox {
using String = std::string;
using StringView = std::string_view;
template <typename T_, size_t Size> using Array = std::array<T_, Size>;
template <typename T_> using Vector = std::vector<T_>;
template <typename KT_, typename VT_>
using HashMap = std::unordered_map<KT_, VT_>;

template <size_t ContentSize> struct LogicNode {
    String name;
    Array<String, ContentSize> content;
    Vector<LogicNode *> branchs;
};
template <typename NT_> class Nodes {
  public:
    Nodes() = default;
    ~Nodes() = default;
    void createNode(NT_ &&logic_node = {});
    void removeNode(StringView name);
    NT_ &getNode(StringView name);

  private:
    HashMap<StringView, NT_> _nodes;
};
template <typename NT_> void Nodes<NT_>::createNode(NT_ &&logic_node) {
    StringView name = logic_node.name;
    if (name == "") {
        return;
    }
    for (int num = 1; true; num++) {
        if (_nodes.find(name) == _nodes.end()) {
            break;
        } else {
            logic_node.name =
                std::move(logic_node.name + "_" + std::to_string(num));
        }
    }
    _nodes[name] = std::forward<NT_>(logic_node);
}
template <typename NT_> void Nodes<NT_>::removeNode(StringView name) {
    _nodes.erase(name);
}
template <typename NT_> NT_ &Nodes<NT_>::getNode(StringView name) {
	auto result=_nodes.find(name);
    if (result != _nodes.end()) {
		return *result; 
    }
	return {};
}

} // namespace xox

#endif // ! XOX_LOGIC_NODE_HEADER
