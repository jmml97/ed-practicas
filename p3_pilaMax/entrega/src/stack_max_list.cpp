/**
 * @file stack_max_list.cpp
 * @brief Implementación del T.D.A. StackMax mediante una lista enlazada con cabecera
 *        de Element
 *
 */

#include <iostream>
#include <cassert>

using namespace std;

Element& StackMax::top()
{
    return v.last()->element;
}

/* _________________________________________________________________________ */

const Element& StackMax::top() const
{
    return v.last()->element;
}

/* _________________________________________________________________________ */

void StackMax::push(int n)
{
    int max = v.last()->element.max;
    if (max < n)
        max = n;
    Element e = {n, max};
    v.push_back(e);
}

/* _________________________________________________________________________ */

void StackMax::pop()
{
    v.pop_back();
}

/* _________________________________________________________________________ */

void StackMax::clear()
{
    v.clear();
}

/* _________________________________________________________________________ */

/* Fin fichero: stack_max_list.cpp */
