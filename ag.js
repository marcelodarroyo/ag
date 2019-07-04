//=============================================================================
// A tree have a label, parent childs and a attributes map.
// An attribute is an object {id: string, value: object, evaluated: bool}
//=============================================================================
class tree {
    constructor(name, childs = []) {
        this.label = name;
        this.parent = null;
        this.childs = childs;
        this.attributes = {};
    }

    addChild(c) {
        this.childs.push(c);
        c.parent = this;
    }

    getChilds() {
        return this.childs;
    }

    getChild(i) {
        return this.childs[i];
    }

    isLeaf() {
        return this.childs.length() == 0;
    }

    isRoot() {
        return this.parent == null;
    }

    setAttribute(name, value) {
        this.attributes[name] = value;
    }

    getAttribute(name) {
        return this.attributes[name];
    }

    addToCollection(attr, key, value) {
        this.getAttribute(attr)[key] = value;
    }
}

//=============================================================================
// An ag object represents an attribute grammar ag=<R,A,E> with
// R is a set of grammar rules with the form: id: X -> Y Z ...
// A = S + I is the set of attributes
// E is the set of equations (for rules)
//=============================================================================
class ag {
    constructor(name) {
        this.ag_tree = new tree("ag:" + name);

        this.ag_tree.addChild(new tree("rules"));
        this.ag_tree.addChild(new tree("equations"));

        // maps collections for fast search and access
        this.ag_tree.setAttribute("rules", {});
        this.ag_tree.setAttribute("attrs", {});
        this.ag_tree.setAttribute("eqtns", {});
    }

    defRule(name, lhs, rhs) {
        let rule = new tree(name);

        rule.addChild(new tree(lhs));

        rule.addChild(new tree("rhs"));
        for (let s of rhs)
            rule.getChild(1).addChild(new tree(s));

        this.ag_tree.getChild(0).addChild(rule);
        this.ag_tree.addToCollection("rules", name, rule);
    }

    getRule(name) {
        return this.ag_tree.getAttribute("rules")[name];
    }

    defAttribute(name, type) {
        this.ag_tree.getAttribute("attrs")[name] = type;
    }

    setAttribute(name, value) {
        this.ag_tree.setAttribute(name, value);
    }

    getAttribute(name) {
        return this.ag_tree.getAttribute("attrs")[name];
    }

    eqtnLabel(rule, occ, attr) {
        return rule_name + ':' + occ + '.' + attr;
    }

    defEquation(rule_name, target, expr) {
        let occ = target.getAttribute("occ"),
            attr = target.getAttribute("attr"),
            key = eqtnLabel(rule_name, occ, attr),
            eqtn = new tree(label);

        eqtn.addChild(target);
        eqtn.addChild(expr);
        this.ag_tree.getChild(1).addChild(eqtn);
        this.ag_tree.addToCollection("eqtns", key, eqtn);
    }

    getEquationFor(ruleName, symbolOcc, attribute) {
        return this.getAttribute("eqtns")[ruleName + ':' + symbolOcc + '.' + attribute];
    }

    getArgs(eqtn) {
        let childs = root.getChild(1).getChilds(),
            args = [];

        for (let child of childs) {
            if (child.label == "attr_occ") {
                args.push({occ: child.getAttribute["occ"], attr: child.getAttribute["attr"]});
            }
        }
        return args;
    }

    callFn(eqtn, root) {
        // to do...
    }
}

// Demand driven evaluator
evalAttribute(ag, attr, root) {
    let attrDef = ag.getAttribute(attr),
        attrValue = root.getAttribute(attr);

    if (!attrValue) {
        let eqtn = ag.getEquationFor(root.label, 0, attr),
            deps = ag.getArgs(eqtn, root);
        printTree(eqtn);
        console.log(deps);
        for (let dep of deps) {
            evalAttribute(ag, dep.attr, dep.occ == 0 ? root : root.childs[dep.occ-1]);
        }
        root.setAttribute("attr", ag.callFn(eqtn, root));
    }
}

//=============================================================================
// testing...
//=============================================================================
function printTree(t, level = 0) {
    let indent = "";

    for (let i=0; i<level; i++)
        indent += '\t';
    console.log(indent + t.label);

    for (let child of t.childs)
        printTree(child, level + 1);
}

let ag1 = new ag("ag1");

// Grammar rules
ag1.defRule("r1", "S", ["X","Y","Z"]);
ag1.defRule("r2", "X", ["1"]);
ag1.defRule("r3", "Y", ["2"]);
ag1.defRule("r4", "Z", ["3"]);
ag1.defRule("r5", "Z", ["3 Z"]);

// Attributes
ag1.defAttribute("s1", {kind: 's', type: 'i', isCollection: false});
let s1 = ag1.getAttribute("s1");
console.log(s1);

// equation for r5: Z.s1 = f(Z[2].s1)
let target = new tree("target");
target.setAttribute("occ", 0);
target.setAttribute("attr", "s1");

let arg = new tree("attr_occ");
target.setAttribute("occ", 2);
target.setAttribute("attr", "s1");

ag1.defEquation("r5", target, new tree("f",[arg]));

printTree(ag1.ag_tree);
