/**
 * @file list.hpp
 * @brief Fichero de cabecera del T.D.A. List
 *
 */

#ifndef __LIST_HPP__
#define __LIST_HPP__

#include "node.hpp"

/**
 * @brief T.D.A. List
 *
 * Lista enlazada con cabecera
 */

template <class T>
class List
{
  private:
    Node<T>* head;
    Node<T>* tail;

  public:
    // ---------------  Constructores ----------------

    /**
     * @brief Constructor por defecto
     * @post Crea una lista vacía (solo contiene la cabecera)
     */
    List();

    /**
     * @brief Constructor copia
     * @param original Lista a copiar
     */
    List(const List<T>& original);

    // ---------------  Destructor ----------------

    /**
     * @brief Destructor
     * @post Destruye la lista entera
     */
    ~List() { clear(); }

    // ---------------  Sobrecarga de operadores ----------------

    /**
     * @brief Sobrecarga del operador de asignación
     * @param l lista que se va a asignar al objeto implícito
     * @post Copia la información de la lista pasada a la actual
     * @return Referencia al objeto implícito
     */
    List& operator=(const List<T>& l);

    // ---------------  Funciones de acceso ----------------

    /**
     * @brief Devuelve el principio de la lista
     * @return Elemento del principio
     * @pre La lista no es vacía
     */
    T& first() { return head->element; }

    /**
     * @brief Devuelve el principio de la lista
     * @return Referencia constante al elemento del principio
     * @pre La lista no es vacía
     */
    const T& first() const { return head->element; }

    /**
     * @brief Devuelve la cola de la lista
     * @return Elemento del final
     * @pre La lista no es vacía
     */
    T& last() { return tail->element; }

    /**
     * @brief Devuelve la cola de la lista
     * @return Referencia constante al elemento del final
     * @pre La lista no es vacía
     */
    const T& last() const { return tail->element; }

    // ---------------  Funciones de modificación ----------------

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

    // ---------------  Funciones de consulta ----------------

    /**
      * @brief Tamaño de la lista
      * @return Devuelve el tamaño de la lista
      */
    int size() const;

    /**
     * @brief Consulta si la lista está vacía
     * @retval true si está vacía
     * @retval false si no está vacía
     */
    bool empty() const { return head->next; }
};

#include "list.cpp"

#endif

/* Fin fichero: list.hpp */
