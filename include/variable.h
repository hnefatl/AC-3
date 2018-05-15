#ifndef _VARIABLE_H
#define _VARIABLE_H

#include <set>
#include <string>

template<typename Value>
class Variable
{
public:
    const std::string name;
    std::set<Value> domain;
    
    Variable(const std::string name, const std::set<Value> domain)
        : name(name), domain(domain)
    {
    }
};

#endif