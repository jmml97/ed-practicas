/**
  * @file queue_max.cpp
  * @brief Fichero de implementación del T.D.A. QueueMax
  *
  */

#include <cassert>
#include "queue_max.hpp"

Element& QueueMax::front()
{
  assert(!v.empty());
  return v.last->element;
}

/* _________________________________________________________________________ */

const Element& QueueMax::front() const
{
  assert(!v.empty());
  return v.last->element;
}

/* _________________________________________________________________________ */

void QueueMax::push(int n)
{
  int max = n;
  if (!v.empty() && v.top().max > max)
    max = front().max;
  Element e = {n, max};
  v.push(e);
}

/* _________________________________________________________________________ */

void QueueMax::pop()
{
  assert(!v.empty());

  Stack<Element> aux;
  while(!v.empty())
  {
    aux.push(v.top());
    v.pop();
  }
  aux.pop();  // borrar elemento en cuestión

  while(!aux.empty())
  {
    v.push(aux.top());
    aux.pop();
  }
}

/* _________________________________________________________________________ */

bool QueueMax::sameMax(const QueueMax& q) const
{
  assert(!empty() && !q.empty());
  return front().max == q.front().max;
}

/* _________________________________________________________________________ */

std::istream& QueueMax::loadQueue(std::istream& is)
{
  int i;
  QueueMax aux;

  // Eliminar blancos iniciales
  while (isspace(is.peek()))
    is.ignore();

  clear();
  if (is.peek() == '$') // Formato 1
  {
    is.ignore();  // ignorar '$'
    while (is >> i)
      push(i);
  }
  else  // Formato 2
  {
    while (is >> i)
    {
      push(i);
      is >> i;   // no importa el máximo
    }
  }
  return is;
}

/* _________________________________________________________________________ */

std::ostream& QueueMax::writeQueue(std::ostream& os) const
{
  QueueMax aux(*this);
  while (!aux.empty())
  {
    os << aux.front() << std::endl;
    aux.pop();
  }
  return os;
}

/* _________________________________________________________________________ */

std::ostream& QueueMax::prettyPrint(std::ostream& os) const
{
  QueueMax aux(*this);
  while (!aux.empty())
  {
    Element x = aux.front();
    os << '(' << x.num << ',' << x.max << ")\n";
    aux.pop();
  }
  return os;
}

/* _________________________________________________________________________ */

std::istream& operator>>(std::istream& is, QueueMax& q)
{
  return q.loadQueue(is);
}

/* _________________________________________________________________________ */

std::ostream& operator<<(std::ostream& os, const QueueMax& q)
{
  return q.writeQueue(os);
}

/* _________________________________________________________________________ */

std::ostream& operator<<(std::ostream& os, const Element& e)
{
  os << e.num << ' ' << e.max;
  return os;
}

/* _________________________________________________________________________ */

/* Fin fichero: queue_max.cpp */
