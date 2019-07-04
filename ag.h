/*
file: ag.h
author: Marcelo Arroyo (marcelo.arrroyo@dc.exa.unrc.edu.ar)
date: Jun 24 2019
description: Attibute Grammar (AG) representation types
*/

#ifndef _AG_H_
#define _AG_H_

#include "tree.h"
#include "attr.h"

/*=======================================================================================
AG representation:

An AG=<G,A,E>, with G is a context free grammar (set of rules), A is the attributes set
and E is a set of equations (associated to grammar rules).

It is represented as a tree with the root node labeled "ag:name" and three childs:
1: Grammar set rules: root with label "ag_rules" and childs are trees representing
   grammar rules with root labeled as lhs symbol and childs = rhs
   Besides the root node have an "ag_rules" attribute collection (collection of
   references to substrees) for fast finding access to rules subtrees.
2: Attributes: Stored as root node attribute collection "ag_attrs" which represents a
   map:id -> type
   where type is a four character encoding with the form "ktc" where
   k is the attribute kind (synthetized/inherited),
   t is the base value type ('i'=int, 'f'=float, 'c'=char, 's'=string, 't'=tree) and
   c is the collection type ('m'=map, 'l'=list, 's'=set, ...)
3: Equations: Tree with root labeled "ag_eqtns" and childs representing equations.
   Also, the root node contains an attribute "ag_eqtns", which is a collection of
   references to equations trees for fast findind and access to equations subtrees.
   An equation as X.a = expression is represented as a tree with root labeled as '=',
   the attribute occurrence as left child and the tree representing the rhs expression.
   The equation root node contains an collection attribute "rules" containing references the tree node representing the grammar rules it belongs to.
*/

class ag {
public:

    ag(std::string name);

    // define a new grammar rule
    void def_grammar_rule(tree* rule);

    // define a new attribute (with no value)
    void def_attribute(std::string id, char kind, char type, char dep_type = ' ');

    // define a new equation
    void def_equation(std::string id, tree* eq);

    // attribute types
    bool is_syn(std::string type) const { return type[0] == 's'; }
    bool is_inh(std::string type) const { return type[0] == 'i'; }

    // basic types
    bool is_int(std::string type) const { return type[1] == 'i'; }
    bool is_float(std::string type) const { return type[1] == 'f'; }
    bool is_bool(std::string type) const { return type[1] == 'b'; }
    bool is_char(std::string type) const { return type[1] == 'c'; }
    bool is_string(std::string type) const { return type[1] == 's'; }
    bool is_reference(std::string type) const { return type[1] == 'r'; }

    // collections (map, list or set)
    bool is_collection(std::string type) const {
        return type[2] == 'm' || type[2] == 'l' || type[2] == 's';
    }

    // equation building
    tree* literal(std::string value);
    tree* attr_instance(std::string symbol, char occ, std::string attr);
    tree* equation(std::string target, std::string fn, std::list<tree*> args);

    // evaluate attribute ant node t
    void eval(std::string attr_name, tree* t);

private:
    tree _ag;
};

#endif
