#ifndef _EDGE_H
#define _EDGE_H

#include <memory>

#include "variable.h"
#include "constraint.h"

template<typename V>
class Edge
{
    using VarPtr = std::shared_ptr<Variable<V>>;
    using ConstraintPtr = std::shared_ptr<Constraint<V>>;
public:
    const VarPtr source;
    const VarPtr dest;
    const ConstraintPtr constraint;

    Edge(const VarPtr source, const VarPtr dest, const ConstraintPtr constraint)
        : source(source), dest(dest), constraint(constraint)
    {
    }

    bool operator <(const Edge<V> &rhs) const
    {
        if (source != rhs.source)
            return source < rhs.source;
        else if (dest != rhs.dest)
            return dest < rhs.dest;
        else
            return constraint < rhs.constraint;
    }
};

#endif