/**
 * @file stack_max_dvector.cpp
 * @brief Implementación del T.D.A. StackMax mediante un vector dinámico de Element
 *
 */

#include <cassert>

Element& StackMax::top()
{
    return v[v.size() - 1];
}

/* _________________________________________________________________________ */

const Element& StackMax::top() const
{
    return v[v.size() - 1];
}

/* _________________________________________________________________________ */

void StackMax::push(int n)
{
    int max = n;
    if (!v.empty() && top().max > max)
        max = top().max;
    Element e = {n, max};
    v.push_back(e);
}

/* _________________________________________________________________________ */

void StackMax::pop()
{
    v.resize(v.size() - 1);
}

/* _________________________________________________________________________ */

// void StackMax::swap(StackMax& s) {}

void StackMax::clear()
{
    v.clear();
}

/* _________________________________________________________________________ */

/* Fin fichero: stack_max_dvector.cpp */
