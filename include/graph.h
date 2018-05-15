#ifndef _GRAPH_H
#define _GRAPH_H

#include <vector>
#include <memory>
#include <set>
#include <map>

#include "edge.h"
#include "variable.h"

template<typename V>
class Graph
{
private:
    using VarPtr = std::shared_ptr<Variable<V>>;

    std::vector<VarPtr> variables;
    std::map<VarPtr, std::vector<Edge<V>>> edges;

public:
    // Constraint is the opposite way round to a normal adjacency list.
    // Rather than map a node to nodes it has an edge to, it maps a node to the nodes with an edge to it
    Graph(const std::vector<VarPtr> variables, const std::map<VarPtr, std::vector<Edge<V>>> edges)
        : variables(variables), edges(edges)
    {
    }

    bool performAC3()
    {
        std::set<Edge<V>> toUpdate;
        // Insert all edges
        for (const auto variableEdgePair : edges)
            toUpdate.insert(variableEdgePair.second.begin(), variableEdgePair.second.end());

        while (!toUpdate.empty())
        {
            const auto it = toUpdate.begin();
            const Edge<V> e = *it;
            toUpdate.erase(it);

            if (e.constraint->enforce(e.source, e.dest))
            {
                // Get all nodes with an edge to this constraint's source
                const auto neighbours = edges[e.source];
                // Add all neighbours to the pending set
                toUpdate.insert(neighbours.begin(), neighbours.end());
            }
        }

        return !std::any_of(variables.begin(), variables.end(), [](const auto v) { return v->domain.empty(); });
    }

    std::vector<VarPtr> getVariables() const { return variables; }
};

#endif