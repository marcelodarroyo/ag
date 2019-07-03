#ifndef _ATTR_H_
#define _ATTR_H_

#include <any>

class attribute_value {
    public:

        attribute_value() {}

        template<typename T>
        attribute_value(T v) : _value(v) {}

        template<typename T>
        T get_value() { std::any_cast<T>(_value); }

        template<typename T>
        T set_value(const T & v) { _value = v; }

        bool evaluated() { return _value.has_value(); }

    private:
        std::any _value;
};

// Composite values (collections)
using collection = std::list<attribute_value>;

#endif
