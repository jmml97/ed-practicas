/**
 * @file list.cpp
 * @brief Implementación del T.D.A. List
 *
 */

template <class T>
List<T>::List(const List& original)
{
  Node<T>* p = original.head;

  if (p) {
    do
    {
      push_back(p->element);
      p = p->next;
    } while(p);
  }
  else
    head = tail = 0;
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
int List<T>::size() const
{
  int n = 0;
  for (Node<T>* aux = head; aux; aux = aux->next)
    n++;
  return n;
}

/* _________________________________________________________________________ */

template <class T>
void List<T>::push_back(const T& e)
{
  Node<T>* aux = new Node<T>(e,0);

  if (head)
      tail->next = aux;
  else
      head = aux;
  tail = aux;
}

/* _________________________________________________________________________ */

template <class T>
void List<T>::pop_back()
{
  assert(head);
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
  while (head)
  {
      Node<T>* aux = head;
      head = head->next;
      delete aux;
  }
  tail = 0;
}

/* Fin fichero: list.cpp */
