/**
  * @file stack.hpp
  * @brief Fichero cabecera del TDA Stack
  *
  * Gestiona una secuencia de elementos con facilidades para la inserción y
  * borrado de elementos en un extremo.
  */

#ifndef __STACK_HPP__
#define __STACK_HPP__

#include "node.hpp"

template <class T>
class Stack
{
  private:
    Node<T>* first;  ///< Puntero al tope de la pìla

  public:

    Stack() : first(0) {}
    Stack(const Stack<T>& s);
    ~Stack() {clear();}
    Stack<T>& operator=(const Stack<T>& s);

    T& top() {return first->element;}
    const T& top() const {return first->element;}

    void push(const T& e);

    // pre: no vacio
    void pop();

    int size() const;

    void clear();

    bool empty() const {return !first;}
};

#include "stack.cpp"

#endif

/* Fin fichero: stack.hpp */
