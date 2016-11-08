/**
 * @file node.hpp
 * @brief Especificación del T.D.A. Node
 *
 */

#ifndef __NODE_HPP__
#define __NODE_HPP__

/**
 * @brief T.D.A. Node
 *
 * Un objeto del tipo Node representa una celda, que contiene un elemento
 * de información @e element, de tipo @c T genérico, y un puntero @e next a otra celda.
 */

template <class T>
struct Node
{
  T element;       ///< Elemento de información.
  Node<T>* next;   ///< Puntero al siguiente nodo.

  /**
   * @brief Constructor por defecto
   * @post Crea una celda vacía
   */
  Node() : next(0) {}

  /**
   * @brief Constructor coopia
   * @param node Nodo a copiar
   */
   Node(const Node& node) : element(node.element), next(node.next) {}

  /**
   * @brief Constructor con parámetros
   * @param elem Elemento de información.
   * @param nxt Puntero al siguiente nodo.
   */
  Node(const T& elem, Node<T>* nxt) : element(elem), next(nxt) {}
};

#endif

/* Fin fichero: node.hpp */
