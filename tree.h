#ifndef _TREE_H_
#define _TREE_H_

#include <string>
#include <list>
#include <map>
#include <any>

class tree {
    public:
        tree(std::string label = "", bool leaf = false)
            : _label(label), _parent(nullptr)
            {
                if (leaf)
                    no_more_childs();
            }

        std::string label()             const { return _label; }
        tree*       parent()            const { return _parent; }
        int         arity()             const { return _childs.size(); }
        tree*       first_child()       const { return _childs.front(); }
        tree*       last_child()        const { return _childs.back(); }
        tree*       get_child(int i)    const { return _childs[i]; }

        bool        isleaf()      const { return arity() == 0; }
        bool        is_root()     const { return _parent == 0; }

        void add_child(tree* child) { _childs.push_back(child); }
        void no_more_childs() { _childs.shrink_to_fit(); }

        // attributes
        void def_attribute(std::string name) { _attrs[name] = attribute_value(); }
        attribute_value& get_attr(std::string name) { return _attrs.at(name); }
        void set_attr_value(std::string name, attribute_value& value) { _attrs[name] = value; }

        ~tree();
    private:
        std::string                             _label;
        tree*                                   _parent;
        std::vector<tree*>                      _childs;
        std::map<std::string, attribute_value>  _attrs;
};

tree* mk_tree(std::string label);
tree* mk_leaf(std::string label);

#endif
