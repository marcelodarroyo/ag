#include "ag.h"

static const char* ag_rules = "(ag_rules)";
static const char* ag_attrs = "(ag_attrs)";
static const char* ag_eqtns = "(ag_eqtns)";

using rules_collection = std::map<std::string, tree*>;
using attrs_collection = std::map<std::string, std::string>;
using eqtns_collection = std::map<std::string, tree*>;

ag::ag(std::string name)
    : _ag(name)
{
    _ag.add_child(mk_tree(ag_rules));
    _ag.add_child(mk_tree(ag_attrs));

    // define collection attributes
    _ag.def_attribute(ag_rules);
    _ag.set_attr_value(ag_rules, rules_collection());

    _ag.def_attribute(ag_attrs);
    _ag.set_attr_value(ag_attrs, attrs_collection());

    _ag.def_attribute(ag_eqtns);
    _ag.set_attr_value(ag_eqtns, eqtns_collection());
}

void def_grammar_rule(tree* rule); {
    _ag.child(0)->add_child(rule);
    rules_collection *c = _ag.get_attr(ag_rules).get_ref<rules_collection>();
    (*c)[rule.label()] = rule;
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
