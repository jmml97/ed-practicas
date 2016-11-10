/**
  * @file stack.cpp
  * @brief Implementación del TDA Stack
  *
  */
// No se incluye el .hpp

template <class T>
Stack<T>::Stack(const Stack<T>& s)
{
    first = new Node<T>(s.top(), 0);
    Node<T>* aux_orig = s.first->next;
    Node<T>* aux_new = first->next;

    while (aux_orig)
    {
        aux_new = new Node<T>(aux_orig->element, 0);
        aux_orig = aux_orig->next
        aux_new = aux_new->next;
    }
}

/* _________________________________________________________________________ */

template <class T>
Stack<T>& Stack<T>::operator =(const Stack<T>& s)
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
void Stack<T>::push(T e)
{
    Node<T>* aux = first;
    first = new Node<T>(e, aux);
}

/* _________________________________________________________________________ */

template <class T>
void Stack<T>::pop()
{
    Node<T>* aux = first;
    first = first->next;
    delete aux;
}

/* _________________________________________________________________________ */

template <class T>
int Stack<T>::size() const
{
    Stack<T> aux(*this);
    int n;
    for (n = 0; aux.first; ++n)
        aux.pop();
    return n;
}

/* _________________________________________________________________________ */

template <class T>
void Stack<T>::clear()
{
    while (first)
        pop();
}

/* Fin fichero: stack.cpp */
