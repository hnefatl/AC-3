#include <iostream>

#include "diffConstraint.h"
#include "variable.h"
#include "graph.h"
#include "edge.h"

#include <vector>

enum Colour { R, C, B };

std::string colourToString(const Colour &c)
{
    switch (c)
    {
        case R:  return "R";
        case C:  return "C";
        case B:  return "B";
        default: return "ERROR";
    }
}

Graph<Colour> makeDemoGraph();

int main(int argc, char *argv[])
{
    Graph<Colour> g = makeDemoGraph();

    std::vector<std::pair<std::string, Colour>> assignments;
    assignments.emplace_back(std::make_pair("1", R));
    assignments.emplace_back(std::make_pair("4", C));
    assignments.emplace_back(std::make_pair("5", R));
    assignments.emplace_back(std::make_pair("8", C));
    assignments.emplace_back(std::make_pair("6", B));

    unsigned int counter = 0;
    for (const auto &a : assignments)
    {
        std::cout << "Assignment " << ++counter << ": " << a.first << " = " << colourToString(a.second) << std::endl;

        // Get the variable
        const auto vars = g.getVariables();
        const auto it = std::find_if(vars.begin(), vars.end(), [a](const auto v) { return v->name == a.first; });

        if (it == vars.end() || *it == nullptr)
        {
            std::cout << "Invalid assignment" << std::endl;
            return -2;
        }

        // Set the domain
        const auto v = *it;
        v->domain = { a.second };

        bool failed = !g.performAC3();
        for (const auto v : g.getVariables())
        {
            std::cout << v->name << ":";
            for (const auto d : v->domain)
                std::cout << " " << colourToString(d);
            std::cout << std::endl;
        }
        if (failed)
        {
            std::cout << "Consistency fail" << std::endl;
            return -1;
        }
        std::cout << std::endl;
    }

    return 0;
}

Graph<Colour> makeDemoGraph()
{
    using VarPtr = std::shared_ptr<Variable<Colour>>;
    using ConstraintPtr = std::shared_ptr<Constraint<Colour>>;
    const std::set<Colour> domain = { R, C, B };

    VarPtr a = std::make_shared<Variable<Colour>>("1", domain);
    VarPtr b = std::make_shared<Variable<Colour>>("2", domain);
    VarPtr c = std::make_shared<Variable<Colour>>("3", domain);
    VarPtr d = std::make_shared<Variable<Colour>>("4", domain);
    VarPtr e = std::make_shared<Variable<Colour>>("5", domain);
    VarPtr f = std::make_shared<Variable<Colour>>("6", domain);
    VarPtr g = std::make_shared<Variable<Colour>>("7", domain);
    VarPtr h = std::make_shared<Variable<Colour>>("8", domain);

    std::vector<VarPtr> variables = { a, b, c, d, e, f, g, h };

    ConstraintPtr constraint = std::make_shared<DiffConstraint<Colour>>();
    std::map<VarPtr, std::vector<Edge<Colour>>> edges;

    // Constructs bidirectional constraints
    const auto helper = [&edges, constraint](const auto v1, const auto v2)
                        {
                            edges[v1].push_back(Edge<Colour>(v2, v1, constraint));
                            edges[v2].push_back(Edge<Colour>(v1, v2, constraint));
                        };
    // Left ring
    helper(a, b);
    helper(a, c);
    helper(a, d);
    helper(b, d);
    helper(c, d);

    // Right ring
    helper(e, f);
    helper(e, g);
    helper(h, f);
    helper(h, g);
    helper(f, g);

    // Ring links
    helper(b, f);
    helper(d, e);
    helper(c, g);

    return Graph<Colour>(variables, edges);
}