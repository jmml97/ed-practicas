/**
  * @file stack_max.cpp
  * @brief Fichero de implementación del T.D.A. StackMax
  *
  * Permite elegir entre tres implementaciones, según la especificación escogida
  *
  */

#include "stack_max.hpp"

#if COMPILE_HEADER == 1
  #include "stack_max_list.cpp"
#elif COMPILE_HEADER == 2
  #include "stack_max_dv.cpp"
#else
  #include "stack_max_queue.cpp"
#endif

bool StackMax::sameMax(const StackMax& s) const
{
  return top().max == s.top().max;
}

/* _________________________________________________________________________ */

istream& StackMax::loadStack(istream& is)
{
  Element x;
  StackMax aux;
  while (is) {
    is >> x.num;
    is >> x.max;
    aux.push(x.num);
  }
  if (is) {
    clear();  // Borrar pila actual
    while (!aux.empty()) {
      x = aux.top();
      v.push(x.num);
      aux.pop();
    }
  }
  return is;
}

/* _________________________________________________________________________ */

ostream& StackMax::writeStack(ostream& os) const
{
  StackMax aux;
  while (!aux.empty()) {
    Element x = aux.top();
    os << x.num << " " << x.max << endl;
    aux.pop();
  }
  return os;
}

/* _________________________________________________________________________ */

ostream& StackMax::prettyPrint(ostream& os) const
{
  StackMax aux;
  while (!aux.empty()) {
    Element x = aux.top();
    os << "(" << x.num << "," << x.max << ")" << endl;
    aux.pop();
  }
  return os;
}

/* _________________________________________________________________________ */

istream& operator>>(istream& is, StackMax& s)
{
  return s.loadStack(is);
}

/* _________________________________________________________________________ */

ostream& operator<<(ostream& os, const StackMax& s)
{
  return s.writeStack(os);
}

/* _________________________________________________________________________ */

/* Fin fichero: stack_max.cpp */
