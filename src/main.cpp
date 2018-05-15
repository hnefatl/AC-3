#include <iostream>

#include "diffConstraint.h"
#include "variable.h"

#include <vector>

enum Colour { R, C, B };

int main(int argc, char *argv[])
{
    std::set<Colour> domain = { R, C, B };
    Variable<Colour> a("1", domain);
    Variable<Colour> b("2", domain);
    Variable<Colour> c("3", domain);
    Variable<Colour> d("4", domain);
    Variable<Colour> e("5", domain);
    Variable<Colour> f("6", domain);
    Variable<Colour> g("7", domain);
    Variable<Colour> h("8", domain);

    std::vector<DiffConstraint<Colour>> constraints;

    return 0;
}
