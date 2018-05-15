#ifndef _CONSTRAINT_H
#define _CONSTRAINT_H

#include "variable.h"

#include <memory>
#include <algorithm>
#include <functional>
#include <typeinfo>

template<typename V>
class Constraint
{
protected:
    virtual bool isValid(const V &vSource, const V &vDest) const = 0;

    using VarPtr = std::shared_ptr<Variable<V>>;

public:
    virtual bool enforce(const VarPtr i, const VarPtr j) const
    {
        bool domainModified = false;

        for (const auto &v : i->domain)
        {
            const auto pred = std::bind(&Constraint::isValid, this, v, std::placeholders::_1);
            if (!std::any_of(j->domain.begin(), j->domain.end(), pred))
            {
                i->domain.erase(v);
                domainModified = true;
            }
        }

        return domainModified;
    }

    bool operator <(const Constraint<V> &rhs) const
    {
        typeid(this).name() < typeid(&rhs).name();
    }
};

#endif