/**
 * @file stack_max_queue.cpp
 * @brief Implementación del T.D.A. StackMax mediante una cola de Element
 *
 */

#include <cassert>

Element& StackMax::top()
{
  assert(!v.empty());
  return v.front();
}

/* _________________________________________________________________________ */

const Element& StackMax::top() const
{
  assert(!v.empty());
  return v.front();
}

/* _________________________________________________________________________ */

void StackMax::push(int n)
{
  Element x;
  x.num = n;

  if (v.size() == 0)
  {
    x.max = n;
    v.push(x);
  }

  else
  {
    int curr_max = v.front().max;
    x.max = curr_max >= n ? curr_max : n;
    Queue<Element> aux;
    aux.push(x);
    while (v.size() != 0)
    {
      aux.push(v.front());
      v.pop();
    }
    v = aux;
  }
}

/* _________________________________________________________________________ */

void StackMax::pop()
{
  assert(!v.empty());
  v.pop();
}

/* _________________________________________________________________________ */

/* Fin fichero: stack_max_queue.cpp */
