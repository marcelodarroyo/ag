#include "tree.h"

// end recursion for template add_childs(tree* n, Args... childs)
void add_childs(tree* n)
{
    n->childs.shrink_to_fit();
}

// leaf node builder
tree* mk_leaf(std::string label)
{
    return new tree(label);
}

void tree::add_child(tree* child)
{
    child->left = _childs.size()>0 ? _childs[_childs.size()-1] : nullptr;
    if (child->left)
        child->left->right = child;
    _childs.push_back(child);
    child->_parent = this;
}

void tree::def_attribute(std::string name)
{
    _attrs[name] = attribute_value();
}

void tree::add_to_collection(std::string name, attribute_value v)
{
    attribute_value &c = _ag.get_ref(name);
    c.push_back(v);
}

tree::~tree() {
    for (int i=0; i<_childs.size(; i++)) {
        delete _childs[i];
    }
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

//=============================================================================
// Search in trees
//=============================================================================

// deph first search
tree* find_in_subtree(tree* node, const std::string& label)
{
    if (node->label == label)
        return node;
    else {
        tree* result = nullptr;
        for (var i=0; i<node->arity(); i++) {
            result = find_from(node->child(i), label);
            if (result)
                break;
        }
        return result;
    }
}


tree* find_left_up(tree* node, const std::string& label)
{
    tree* previous = node->left() || node->parent();
    if (previous) {
        if (label == previous->label)
            return previous;
        else
            return find_left_up(previous);
    }
    return previous;
}
