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
    /**
     * @brief T.D.A. Iterator
     *
     */
    class Iterator {
      private:
        Node<T>* ptr;
        Node<T>* first;
      public:
        Iterator() : ptr(0), first(0) {}
        // ...
    };

    /**
     * @brief Constructor sin parámetros
     */
    List();
    // ...
};

#include "list.cpp"

#endif

/* Fin fichero: list.hpp */
