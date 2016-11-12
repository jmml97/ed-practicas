/**
 * @file stack_max_dvector.cpp
 * @brief Implementación del T.D.A. StackMax mediante un vector dinámico de Element
 *
 */

#include <cassert>

Element& StackMax::top()
{
  assert(!v.empty());
  return v[v.size()-1];
}

/* _________________________________________________________________________ */

const Element& StackMax::top() const
{
  assert(!v.empty());
  return v[v.size()-1];
}

/* _________________________________________________________________________ */

void StackMax::push(int n)
{
  int max;
  if (v.empty())
    max = n;
  else
  {
    max = v[v.size()-1].max;
    if (max < n)
      max = n;
  }

  Element e = {n, max};
  v.push_back(e);
}

/* _________________________________________________________________________ */

void StackMax::pop()
{
  assert(!v.empty());
  v.pop_back();
  if (v.size() < v.capacity()/4)
    v.shrink();
}

/* _________________________________________________________________________ */

/* Fin fichero: stack_max_dvector.cpp */
