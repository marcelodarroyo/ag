#include <string>
#include <any>
#include <map>
#include <iostream>

using namespace std;

int main()
{
    using map_type = map<string, int>;
    map_type m;
    any a(m);
    map<string, int>* mp = any_cast<map_type>(&a);
    return 1;
}
