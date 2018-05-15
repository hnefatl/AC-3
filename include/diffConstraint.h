#ifndef _DIFF_CONSTRAINT_H
#define _DIFF_CONSTRAINT_H

#include "constraint.h"

template<typename V>
class DiffConstraint
    : public Constraint<V>
{
protected:
    virtual bool isValid(const V &v1, const V &v2) const
    {
        return v1 != v2;
    }

public:
    DiffConstraint(Variable<V> &i, Variable<V> &j)
        : Constraint<V>(i, j)
    {
    }
};

#endif