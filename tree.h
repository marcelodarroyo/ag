#ifndef _TREE_H_
#define _TREE_H_

#include <string>
#include <list>
#include <map>
#include <any>

class tree {
    public:
        tree(std::string label = "")
            : _label(label), _parent(nullptr), _left(nullptr), _right(nullptr) {}

        std::string label()      const { return _label; }
        tree*       parent()     const { return _parent; }
        tree*       left()       const { return _left; }
        tree*       right()      const { return _right; }
        tree*       child(int n) const { return _childs[n]; }
        int         arity()      const { return _childs.size(); }
        tree*       last_child() const { return _childs[_childs.size()-1]; }
        bool        isleaf()     const { return arity() == 0; }
        bool        is_root()    const { return _parent == 0; }

        void add_child(tree* child);

        void def_attribute(std::string name);
        attribute_value get_value(std::string name) const { return _attrs.at(name); }
        attribute_value& get_ref(std::string name) { return _attrs.at(name); }
        void set_value(std::string name, attribute_value value) { _attrs[name] = value; }

        void def_collection(std::string name) { _attrs[name] = collection(); }
        void add_to_collection(std::string name, attribute_value v);

        ~tree();
    private:
        std::string                             _label;
        tree*                                   _parent;
        tree*                                   _left;
        tree*                                   _right;
        std::vector<tree*>                      _childs;
        std::map<std::string, attribute_value>  _attrs;

};

//=============================================================================
// Search in trees
//=============================================================================
tree* find_in_subtree(const std::string& label);
tree* find_left_up(const std::string& label);

//=============================================================================
// tree builder: t(t(t(1), t(2)), t(3), t(4))
//=============================================================================

// Adding childs to tree node
void add_childs(tree* n);

template<typename... Args>
void add_childs(tree* n, tree* child, Args... others)
{
    n->add_child(child);
    add_childs(n, others...);
}

// tree builder
template<typename... Args>
tree* t(std::string label, Args... childs)
{
    tree* n = new tree(label);
    add_childs(n, childs...);
    return n;
}

#endif
