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
 *
 */

template <class T>
class List {
  Node<T>* head;
  int nelem;
};

#include "list.cpp"

#endif

/* Fin fichero: list.hpp */
