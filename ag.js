class tree {
    constructor(name) {
        this.label = name;
        this.parent = null;
        this.childs = [];
        this.attributes = {};
    }

    add_child(c) {
        this.childs.push(c);
        c.parent = this;
    }

    is_leaf() {
        return this.childs.length() == 0;
    }

    is_root() {
        return this.parent == null;
    }
}

// An ag object represents an attribute grammar ag=<R,A,E> with
// R is a set of grammar rules with the form: id: X -> Y Z ...
class ag {
    constructor(name) {
        this.ag_tree = new tree("ag:" + name);

        this.ag_tree.add_child(new tree("ag_grammar_rules"));
        this.ag_tree.add_child(new tree("ag_equations"));

        // maps for fast search
        this.rules_map = {};
        this.attributes = {};
        this.eqtns_map = {}
    }

    def_grammar_rule(name, lhs, rhs) {
        let rule = new tree(name);

        rule.add_child(new tree(lhs));

        for (let s of rhs)
            rule.add_child(s);

        this.ag_tree.child(0).add_child(rule);
        this.rules_map[name] = rule;
    }

    def_attribute_rule(name, ls, rs) {
        this.grammar_rules[name] = {lhs: ls, rhs: rs};
    }
}
