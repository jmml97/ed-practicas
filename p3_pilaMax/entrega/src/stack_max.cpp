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
  assert(!empty() && !s.empty());
  return top().max == s.top().max;
}

/* _________________________________________________________________________ */

istream& StackMax::loadStack(istream& is)
{
  int i;
  StackMax aux;
  while (is >> i) {
    aux.push(i);
    is >> i;   // No importa el máximo
  }

  if (is.eof()) {
    clear();  // Borrar pila actual
    while (!aux.empty()) {
      Element x = aux.top();
      push(x.num);
      aux.pop();
    }
  }
  return is;
}

/* _________________________________________________________________________ */

ostream& StackMax::writeStack(ostream& os) const
{
  StackMax aux(*this);
  while (!aux.empty()) {
    os << aux.top() << endl;
    aux.pop();
  }
  return os;
}

/* _________________________________________________________________________ */

ostream& StackMax::prettyPrint(ostream& os) const
{
  StackMax aux(*this);
  while (!aux.empty()) {
    Element x = aux.top();
    os << '(' << x.num << ',' << x.max << ')' << endl;
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

ostream& operator<<(ostream& os, const Element& e)
{
  os << e.num << ' ' << e.max;
  return os;
}

/* _________________________________________________________________________ */

/* Fin fichero: stack_max.cpp */
