/**
 * @file list.hpp
 * @brief Fichero de cabecera del T.D.A. List
 *
 * Gestiona una secuencia de elementos con facilidades para la inserción y
 * borrado al final y acceso al principio y final.
 */

#ifndef __LIST_HPP__
#define __LIST_HPP__

#include "node.hpp"

/**
 *  @brief T.D.A. Lista
 *
 * Una instancia @e c del tipo de dato abstracto Lista sobre un dominio @e T es
 * una sucesión finita de elementos del mismo. Este tipo lista permite
 * operaciones de inserción y borrado al final; y acceso al principio y final.
 *
 * Una lista con cabecera de longitud @e n la denotamos:
 *
 * - <0,a1,a2,..,an>
 *
 * Donde @e Head, apunta a la cabecera que está vacía del elemento @e T (0) y
 * que apunta al siguiente elemento @e T. Tendremos también @e Tail, que apunta
 * al último elemento @e T de la lista.
 *
 * Si head->next = 0, diremos que la lista está vacia.
 *
 * El espacio requerido para el almacenamiento es O(n), donde n es el número
 * de elementos de la lista.
 *
 * @author Antonio Coín Castro, Miguel Lentisco Ballesteros, José María Martín
 * Luque
 * @date 09/11/2016
*/

template <class T>
class List
{
  private:
    Node<T>* head; ///< Puntero a la cabecera de la lista.
    Node<T>* tail; ///< Puntero al último nodo de la lista.

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
     * @post Destruye la lista entera, dejando head y tail a 0.
     */
    ~List();

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
    T& first() {return head->next->element;}

    /**
     * @brief Devuelve el principio de la lista
     * @return Referencia constante al elemento del principio
     * @pre La lista no es vacía
     */
    const T& first() const {return head->next->element;}

    /**
     * @brief Devuelve la cola de la lista
     * @return Elemento del final
     * @pre La lista no es vacía
     */
    T& last() {return tail->element;}

    /**
     * @brief Devuelve la cola de la lista
     * @return Referencia constante al elemento del final
     * @pre La lista no es vacía
     */
    const T& last() const {return tail->element;}

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
     * @post Elimina la lista completamente, salvo la cabecera.
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
    bool empty() const {return (head->next == 0);}
};

#include "list.cpp"

#endif

/* Fin fichero: list.hpp */
