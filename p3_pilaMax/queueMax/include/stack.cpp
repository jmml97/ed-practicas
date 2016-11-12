/**
  * @file stack.cpp
  * @brief Implementación del T.D.A Stack
  *
  */

template <class T>
Stack<T>::Stack(const Stack<T>& s)
{
  if (s.first)
  {
    Node<T>* p = s.first;
    first = new Node<T>(p->element, 0);
    p = p->next;
    Node<T>* aux = first;

    while (p)
    {
      aux->next = new Node<T>(p->element, 0);
      aux = aux->next;
      p = p->next;
    }
  }
  else
    first = 0;
}

/* _________________________________________________________________________ */

template <class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& s)
{
  Stack<T> aux(s);

  Node<T>* p = first;
  first = aux.first;
  aux.first = p;

  return *this;
}

/* _________________________________________________________________________ */

template <class T>
void Stack<T>::push(const T& e)
{
  Node<T>* aux = first;
  first = new Node<T>(e, aux);
}

/* _________________________________________________________________________ */

template <class T>
void Stack<T>::pop()
{
  assert(first);
  Node<T>* aux = first;
  first = first->next;
  delete aux;
}

/* _________________________________________________________________________ */

template <class T>
int Stack<T>::size() const
{
  int n = 0;
  for (Node<T>* p = first; p; p = p->next)
    n++;
  return n;
}

/* _________________________________________________________________________ */

template <class T>
void Stack<T>::clear()
{
  while (first)
  {
    Node<T>* aux = first;
    first = first->next;
    delete aux;
  }
}

/* _________________________________________________________________________ */

/* Fin fichero: stack.cpp */
