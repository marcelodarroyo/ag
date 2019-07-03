#include "ag.h"

ag::ag(std::string name)
    : _ag(name)
{
    _ag.add_child(t("grammar_rules"), t("equations"));
}

void ag::def_attribute(std::string id, char kind, char type, char ref_or_coll)
{
    std::string type = std::string() + kind + type + ref_or_coll;
    _ag.def_attribute(id);
    _ag.set_value(type);
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
