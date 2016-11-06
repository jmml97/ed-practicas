/**
 * @file stack_max_queue.cpp
 * @brief Implementación del T.D.A. StackMax mediante una cola de Element
 *
 */

#include <iostream>
#include <cassert>
#include "stack_max.hpp"  //////////////////// QUITAR

using namespace std;

Element& StackMax::top()
{
  return v.front();
}

/* _________________________________________________________________________ */

const Element& StackMax::top() const
{
  return v.front();
}

/* _________________________________________________________________________ */

void StackMax::push(int n)
{

}

/* _________________________________________________________________________ */

void StackMax::pop()
{
  v.pop();
}

/* _________________________________________________________________________ */

// void StackMax::swap(StackMax& s) {}

void StackMax::clear()
{
  v.~Queue();
}

/* _________________________________________________________________________ */

/* Fin fichero: stack_max_queue.cpp */
