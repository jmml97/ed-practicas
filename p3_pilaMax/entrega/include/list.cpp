/**
 * @file list.cpp
 * @brief Implementación del T.D.A. List
 *
 */

#include <cassert>

template <class T>
List<T>::List()
{
  tail = head = new Node<T>;
  head->next = 0;
}

/* _________________________________________________________________________ */

template <class T>
List<T>::List(const List& original)
{
  Node<T>* p = original.head->next;
  tail = head = new Node<T>;
  head->next = 0;

  while(p)
  {
    push_back(p->element);
    p = p->next;
  }
}

template <class T>
List<T>::~List()
{
  clear();
  delete head;
  tail = head = 0;
}

/* _________________________________________________________________________ */

template <class T>
List<T>& List<T>::operator=(const List<T>& l)
{
  List aux(l);

  Node<T>* p = head;
  head = aux.head;
  aux.head = p;

  p = tail;
  tail = aux.tail;
  aux.tail = p;

  return *this;
}

/* _________________________________________________________________________ */

template <class T>
void List<T>::push_back(const T& e)
{
  Node<T>* aux = new Node<T>(e,0);
  tail->next = aux;
  tail = tail->next;
}

/* _________________________________________________________________________ */

template <class T>
void List<T>::pop_back()
{
  assert(head->next);
  Node<T>* p;
  // Movemos un puntero hasta el nodo anterior a tail
  for (p = head; p->next != tail; p = p->next);
  delete tail;
  tail = p;
  p->next = 0;
}

/* _________________________________________________________________________ */

template <class T>
void List<T>::clear()
{
  while (head->next)
  {
    Node<T>* aux = head->next;
    head->next = head->next->next;
    delete aux;
  }
  tail = head;
}

/* _________________________________________________________________________ */

template <class T>
int List<T>::size() const
{
  int n = 0;
  for (Node<T>* aux = head->next; aux; aux = aux->next)
    n++;
  return n;
}

/* _________________________________________________________________________ */

/* Fin fichero: list.cpp */
