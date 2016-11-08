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
class List
{
  private:
    Node<T>* head;
    Node<T>* tail;

  public:
    /**
     * @brief Constructor por defecto
     * @post Crea una lista vacía
     */
    List() : head(0), tail(0) {}

    /**
     * @brief Constructor copia
     * @param list Lista
     */
    List(const List& list);

    /**
     * @brief Destructor
     * @post Destruye la lista entera
     */
    ~List() { clear(); }

    /**
     * @brief Sobrecarga del operador de asignación
     * @param list, lista que se va a copiar
     * @post Copia la información de la lista pasada a la actual
     * @return Referencia a la propia lista
     */
    List& operator =(const List& list);

    /**
     * @brief Tamaño de la lista
     * @return Devuelve el tamaño de la lista
     */
    int size() const;

    /**
     * @brief Devuelve el principio de la lista
     * @return Puntero al nodo del principio
     */
    Node<T>* head() { return head->element; }

    /**
     * @brief Devuelve el principio de la lista
     * @return Puntero const al nodo del principio
     */
    const Node<T>* head() const { return head->element; }

    /**
     * @brief Devuelve la cola de la lista
     * @return Puntero al nodo del final
     */
    Node<T>* tail() { return tail->element; }

    /**
     * @brief Devuelve la cola de la lista
     * @return Puntero const al nodo del final
     */
    const Node<T>* tail() const { return tail->element; }

    /**
     * @brief Devuelve la cola de la lista
     * @return Elemento const @c T de la cola de la lista
     */
    const T& tail() const { return tail->element; }

    /**
     * @brief Añade un elemento al final
     * @param node, elemento @c T que se quiere añadir
     * @post Añade un elemento @c T en la cola de la lista
     */
    void push_back(const T& e);

    /**
     * @brief Elimina el ultimo
     * @pre lista no vacia
     * @post Elimina el ultimo elemento @c T de la lista
     */
    void pop_back();

    /**
     * @brief Limpia la lista entera
     * @post Elimina la lista completamente, dejando head y tail a 0
     */
    void clear();

};

#include "list.cpp"

#endif

/* Fin fichero: list.hpp */
