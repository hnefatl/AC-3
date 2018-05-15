#ifndef _CONSTRAINT_H
#define _CONSTRAINT_H

#include "variable.h"

#include <algorithm>
#include <functional>

template<typename V>
class Constraint
{
private:
    Variable<V> &i, &j;

protected:
    virtual bool isValid(const V &vSource, const V &vDest) const = 0;

public:
    Constraint(Variable<V> &i, Variable<V> &j);

    virtual bool enforce() const
    {
        bool domainModified = false;

        for (const auto &v1 : i.domain)
        {
            const auto pred = std::bind(&Constraint::isValid, this, v1);
            if (!std::any_of(j.domain.begin(), j.domain.end(), pred))
            {
                i.domain.erase(v1);
                domainModified = true;
            }
        }

        return domainModified;
    }
};

#endif