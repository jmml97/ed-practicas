/**
  * @file stack.cpp
  * @brief Implementación del TDA Stack
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
  if (this != &s)
  {
    clear();
    Stack<T> aux(s);
    first = new Node<T>(aux.first->element, 0);
    aux.first = aux.first->next;
    Node<T>* p_new = first->next;

    while (aux.first)
    {
      p_new = new Node<T>(aux.first->element, 0);
      aux.first = aux.first->next;
      p_new = p_new->next;
    }
  }
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
  Node<T>* p;

  int n = 0;
  for (p = first; p; p = p->next)
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
