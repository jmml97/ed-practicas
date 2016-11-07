/**
 * @file list.hpp
 * @brief Fichero de cabecera del T.D.A. List
 *
 */

#ifndef __LIST_HPP__
#define __LIST_HPP__

#include <cassert>
#include "node.hpp"

/**
 * @brief T.D.A. List
 *
 */

template <class T>
class List {
  private:
    Node<T>* head;
    Node<T>* tail;
  public:
    List() : head(0), tail(0) {}
    // ...
};

#include "list.cpp"

#endif

/* Fin fichero: list.hpp */
