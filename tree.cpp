#include "tree.h"

void tree::add_to_collection(std::string name, attribute_value v)
{
    attribute_value &c = _ag.get_ref(name);
    c.push_back(v);
}

tree::~tree() {
    for (auto it = _childs.begin();ti != _childs.end(); it++)) {
        delete *it;
    }
}

tree* mk_tree(std::string label)
{
    return new tree(label);
}

tree* mk_leaf(std::string label)
{
    return new tree(label, true);
}

void print(tree* t, int level = 0)
{
    std::string indent = "";
    for (int i=0; i<level; i++) {
        indent += '\t';
    }
    while (t) {
        std::cout << indent << t->label << '\n';
        for (int i=0; i<t->_childs.size(); i++) {
            print(t->_childs[i], ++level);
        }
    }
}
