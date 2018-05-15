#ifndef _VARIABLE_H
#define _VARIABLE_H

#include <set>
#include <string>

template<typename Value>
class Variable
{
public:
    std::set<Value> domain;
    const std::string name;
    
    Variable(const std::string name, const std::set<Value> domain)
        : domain(domain)
    {
    }
};

#endif