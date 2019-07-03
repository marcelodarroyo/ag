#ifndef _ATTR_H_
#define _ATTR_H_

#include <any>

class tree;

// An attribute instance with value (maybe empty) and a reference to tree node definition
class attribute_value {
    public:
        attribute_value(tree* ref_to_def) : _def(ref_to_def) {}

        template<typename T>
        T get_value() { std::any_cast<T>(_value); }

        template<typename T>
        T set_value(const T & v) { _value = v; }

        bool evaluated() { return _value.has_value(); }

    private:
        tree* _def;
        std::any _value;
};

#endif
