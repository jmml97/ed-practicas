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
  #include "stack_max_dvector.cpp"
#else
  #include "stack_max_queue.cpp"
#endif

bool StackMax::sameMax(const StackMax& s) const
{
  assert(!empty() && !s.empty());
  return top().max == s.top().max;
}

/* _________________________________________________________________________ */

std::istream& StackMax::loadStack(std::istream& is)
{
  int i;
  StackMax aux;

  // Eliminar blancos iniciales
  while (isspace(is.peek()))
    is.ignore();

  if (is.peek() == '$') // Formato 1
  {
    is.ignore();  // ignorar '$'
    while (is >> i)
      aux.push(i);
  }
  else  // Formato 2
  {
    while (is >> i)
    {
      aux.push(i);
      is >> i;   // no importa el máximo
    }
  }

  if (is.eof())
  {
    clear(); 
    while (!aux.empty())
    {
      Element x = aux.top();
      push(x.num);
      aux.pop();
    }
  }
  return is;
}

/* _________________________________________________________________________ */

std::ostream& StackMax::writeStack(std::ostream& os) const
{
  StackMax aux(*this);
  while (!aux.empty())
  {
    os << aux.top() << std::endl;
    aux.pop();
  }
  return os;
}

/* _________________________________________________________________________ */

std::ostream& StackMax::prettyPrint(std::ostream& os) const
{
  StackMax aux(*this);
  while (!aux.empty())
  {
    Element x = aux.top();
    os << '(' << x.num << ',' << x.max << ")\n";
    aux.pop();
  }
  return os;
}

/* _________________________________________________________________________ */

std::istream& operator>>(std::istream& is, StackMax& s)
{
  return s.loadStack(is);
}

/* _________________________________________________________________________ */

std::ostream& operator<<(std::ostream& os, const StackMax& s)
{
  return s.writeStack(os);
}

/* _________________________________________________________________________ */

std::ostream& operator<<(std::ostream& os, const Element& e)
{
  os << e.num << ' ' << e.max;
  return os;
}

/* _________________________________________________________________________ */

/* Fin fichero: stack_max.cpp */
