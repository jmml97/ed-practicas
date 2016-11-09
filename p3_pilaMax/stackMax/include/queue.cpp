/**
 * @file queue.cpp
 * @brief Implementación del T.D.A. Queue
 *
 */

template <class T>
Queue<T>::Queue(const Queue<T>& original)
{
  if (original.head)
  {
    Node<T>* p = original.head;
    head = tail = new Node<T>(p->element, 0);
    p = p->next;

    while (p)
    {
      tail->next = new Node<T>(p->element, 0);
      tail = tail->next;
      p = p->next;
    }
  }
  else head = tail = 0; // Cola vacía
  n = original.n;
}

/* _________________________________________________________________________ */

template <class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& q)
{
  Queue<T> aux(q);

  // Swap head
  Node<T>* p = head;
  head = aux.head;
  aux.head = p;
  // Swap tail
  p = tail;
  tail = aux.tail;
  aux.tail = p;
  // Swap n
  int i = n;
  n = aux.n;
  aux.n = i;

  return *this;
}

/*_________________________________________________________________________ */

template <class T>
void Queue<T>::push(const T& elem)
{
  Node<T>* aux = new Node<T>(elem, 0);
  if (!head)
    head = tail = aux;
  else
  {
    tail->next = aux;
    tail = aux;
  }
  n++;
}

/* _________________________________________________________________________ */

template <class T>
void Queue<T>::pop()
{
  assert(head);
  Node<T>* aux = head;
  head = head->next;
  delete aux;

  if (!head)
    tail = 0;
  n--;
}

/* _________________________________________________________________________ */

template <class T>
void Queue<T>::clear()
{
  Node<T>* aux;
  while (head)
  {
    aux = head;
    head = head->next;
    delete aux;
  }
  tail = 0;
  n = 0;
}

/* _________________________________________________________________________ */

/* Fin fichero: queue.cpp */
