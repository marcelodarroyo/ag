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
1: Grammar set rules: root with label "grammar_rules" and childs are trees representing
   grammar rules with root labeled as lhs symbol and childs = rhs
   Besides the root node have an "grammar_rules" attribute collection (collection of
   references to substrees) for fast finding access to rules subtrees.
2: Attributes: Stored as root node attribute collection "attributes" which represents a
   map:id -> type

   where type is a four character encoding with the form "ktd" where
   k is the attribute kind (synthetized/inherited),
   t is the base value type ('i'=int, 'f'=float, 'c'=char, 's'=string, 't'=tree) and
   d is the dependent type: 'r'=ref, 'c'=collection
3: Equations: Tree with root labeled "equations" and childs representing equations.
   Also, the root node contains an attribute "equations", which is a collection of
   references to equations trees for fast findind and access to equations subtrees.

Let an attribute grammar as

    r1: X -> Y Y Z
    r2: Y -> t1
    r3: Z -> t2

    syn a:int =
        r1: X.a = f(Y[1].a, Y[2].a)
        r2,r3: lhs.a = int(rhs[0].label)

A grammar rule r: X0 -> X1 ... Xp is represented by a tree with root labeled X0 and p child
nodes labeled Xi (1 <= i <= p), r is the "rule name" (or id)
Rules are stored in grammar_rules map (with index as key)

An equation X_i.d = expression is represented by a binary tree with root labeled "eqtn",
an attribute occurrence node as left child and a tree representing the expression as right child.
An expression can be:
    1) A value (literal), represented as a node labeled "type:value".
    2) An attribute occurrence X[i].a, represented as a node labeled "index:a".
    3) A semantic function call g(...) with root labeled with "fcall:g" and childs are tree
       expressions for arguments.
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

    bool is_int(std::string type) const { return type[1] == 'i'; }
    bool is_float(std::string type) const { return type[1] == 'f'; }
    bool is_bool(std::string type) const { return type[1] == 'b'; }
    bool is_char(std::string type) const { return type[1] == 'c'; }
    bool is_string(std::string type) const { return type[1] == 's'; }
    bool is_reference(std::string type) const { return type[2] == 'r'; }
    bool is_collection(std::string type) const { return type[2] == 'c'; }

    // equation building
    tree* literal(char type, std::string value);
    tree* attr_instance(std::string name, char occ, std::string attr);
    tree* equation(std::string target, std::string fn, std::list<tree*> args);

    // evaluate attribute ant node t
    void eval(std::string attr_name, tree* t);

private:
    tree _ag;

    static const char* ag_rules = "(grammar_rules)";
    static const char* ag_attrs = "(attributes)";
    static const char* ag_eqtns = "(equations)";
};

#endif
