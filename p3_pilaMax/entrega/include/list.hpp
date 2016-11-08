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
     * @param original Lista a copiar
     */
    List(const List<T>& original);

    /**
     * @brief Destructor
     * @post Destruye la lista entera
     */
    ~List() { clear(); }

    /**
     * @brief Sobrecarga del operador de asignación
     * @param l lista que se va a asignar al objeto implícito
     * @post Copia la información de la lista pasada a la actual
     * @return Referencia al objeto implícito
     */
    List& operator=(const List<T>& l);

    /**
     * @brief Tamaño de la lista
     * @return Devuelve el tamaño de la lista
     */
    int size() const;

    /**
     * @brief Devuelve el principio de la lista
     * @return Elemento del principio
     */
    T& first() { return head->element; }

    /**
     * @brief Devuelve el principio de la lista
     * @return Referencia constante al elemento del principio
     */
    const T& first() const { return head->element; }

    /**
     * @brief Devuelve la cola de la lista
     * @return Elemento del final
     */
    T& last() { return tail->element; }

    /**
     * @brief Devuelve la cola de la lista
     * @return Referencia constante al elemento del final
     */
    const T& last() const { return tail->element; }

    /**
     * @brief Añade un elemento al final de la lista
     * @param e, elemento de tipo @c T que se quiere añadir
     */
    void push_back(const T& e);

    /**
     * @brief Elimina el último elemento de la lista
     * @pre El obeto implícito es una lista no vacía
     */
    void pop_back();

    /**
     * @brief Limpiar la lista
     * @post Elimina la lista completamente, dejando head y tail a 0
     */
    void clear();
};

#include "list.cpp"

#endif

/* Fin fichero: list.hpp */
