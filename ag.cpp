#include "ag.h"

ag::ag(std::string name)
    : _ag(name)
{
    _ag.add_child(t(ag_rules), t(ag_eqtns));

    // define collections
    _ag.def_collection(ag_rules);
    _ag.def_collection(ag_attrs);
    _ag.def_collection(ag_eqtns);
}

void def_grammar_rule(tree* rule); {
    _ag.child(0)->add_child(rule);
    std::pair<std::string, tree*> v(rule.label(), rule);
    _ag.add_to_collection(ag_rules, attribute_value(v));
}

void ag::def_attribute(std::string id, char kind, char type, char dep_type)
{
    _ag.set_value(ag_attrs, id, std::string() + kind + type + dep_type);
}


//=============================================================================
// Equations building
//=============================================================================
tree* ag::literal(char type, std::string value)
{
    return t("lit:" + type + ":" + value);
}

tree* attr_instance(std::string name, char occ, std::string attr)
{
    return new t(name + '[' + occ + ']' + attr)
}


tree* eqtn(tree* target, std::string fn, std::list<tree*> args)
{
    tree* fn_args = t("args");

    for (auto it=args.begin(); it != args.end(); it++)
        fn_args.add_child(*it);
    return t(fn, target, fn_args);
}

//=============================================================================
// Attribute evaluation
//=============================================================================
void ag::eval(std::string attr_name, tree* t)
{
    // to do...
}
