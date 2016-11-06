/**
 * @file stack_max_queue.cpp
 * @brief Implementación del T.D.A. StackMax mediante una cola de Element
 *
 */

#include <iostream>
#include <cassert>

using namespace std;

Element& StackMax::top()
{
  assert(!empty());
  return v.front();
}

/* _________________________________________________________________________ */

const Element& StackMax::top() const
{
  assert(!empty());
  return v.front();
}

/* _________________________________________________________________________ */

void StackMax::push(int n)
{
  Element x;
  x.num = n;

  if (v.size() == 0) {
    x.max = n;
    v.push(x);
  }

  else {
    int curr_max = top().max;
    x.max = curr_max >= n ? curr_max : n;
    StackMax aux;
    aux.v.push(x);
    while (v.size() != 0) {
      aux.v.push(v.front());
      v.pop();
    }
    while (aux.v.size() != 0) {
      v.push(aux.v.front());
      aux.v.pop();
    }
  }
}

/* _________________________________________________________________________ */

void StackMax::pop()
{
  assert(!empty());
  v.pop();
}

/* _________________________________________________________________________ */

// void StackMax::swap(StackMax& s) {}

void StackMax::clear()
{
  while (v.size() != 0)
    v.pop();
}

/* _________________________________________________________________________ */

/* Fin fichero: stack_max_queue.cpp */
