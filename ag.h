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
and E is a set of equations (associated to grammar rules). It is represented as a tree
with the root node labeled "ag:name" and three childs:
1: Grammar set rules: root with label "grammar_rules" and childs are trees representing
 grammar rules with root labeled as lhs symbol and childs = rhs
2: Attributes: Tree with root labeled "attributes" and childs represents each attribute
 with label "name:s/i:t" (t is the value type)
3: Equations: Tree with root labeled "eqtns" and childs representing equations:

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

Attibute definitions are stored as attributes of type string with attribute name as id and
attribute type (kind and base type) encoded in a string (ktc), where k (kind) is 's' or 'i'
(synthetized or inherith), t is the base type (i,f,c,s,b,r) and c is 'c' or ' ' (blank) if
it is a collection.

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

    // build grammar rules
    tree* grule(std::string id, std::string lhs, std::list<std::string> rhs);

    // define a new grammar rule
    void def_grammar_rule(tree* rule) {
        _ag.child(0)->add_child(rule);
    }

    // define a new attribute (with no value)
    void def_attribute(std::string id, char kind, char type, char ref_or_coll = ' ');

    // equation building
    tree* literal(char type, std::string value);
    tree* attr_instance(std::string name, char occ, std::string attr);
    tree* eqtn(std::string target, std::string fn, std::list<tree*> args);

    // define a new equation
    void def_equation(tree* eqtn) {
        _ag.child(1)->add_child(rule);
    }

    // evaluate attribute ant node t
    void eval(std::string attr_name, tree* t);

private:
    tree _ag;
};

#endif
