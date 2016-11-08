/**
 * @file stack_max_list.cpp
 * @brief Implementación del T.D.A. StackMax mediante una lista de Element
 *
 */

#include <cassert>

Element& StackMax::top()
{
  return v.last();
}

/* _________________________________________________________________________ */

const Element& StackMax::top() const
{
  return v.last();
}

/* _________________________________________________________________________ */

void StackMax::push(int n)
{
  int max;
  if (v.empty())
    max = n;
  else {
    max = v.last().max;
    if (max < n)
      max = n;
  }
  Element x = {n, max};
  v.push_back(x);
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
