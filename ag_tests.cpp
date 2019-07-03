#include <iostream>
#include "ag.h"
int main()
{
    tree* ast = t("A", t("B"), t("C"));

    std::cout << ast->arity() << std::endl;
    std::cout << ast->child(0)->arity() << std::endl;
    std::cout << ast->child(1)->label() << std::endl;

    std::any v1 = 1000;

    ast->set_property("a1", v1);
    std::cout << "a1:" << ast->get_property("a1").type().name() << " = ";
    std::cout << std::any_cast<int>(ast->get_property("a1")) << std::endl;

    return 0;
}
