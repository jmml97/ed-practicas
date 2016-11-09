/**
 * @file list.hpp
 * @brief Fichero de cabecera del T.D.A. List
 *
 * Gestiona una secuencia de elementos con facilidades para la inserción y
 * borrado al final y acceso al principio y final.
 *
 * Un ejemplo de su uso puede consultarse en:
 * @example test_list.cpp
 *
 */

#ifndef __LIST_HPP__
#define __LIST_HPP__

#include "node.hpp"

/**
 *  @brief T.D.A. List
 *
 * Una instancia @e l del tipo de dato abstracto List (lista con cabecera) sobre
 * un dominio @e T es una sucesión finita de elementos del mismo. Este tipo de lista
 * permite operaciones de inserción y borrado al final; y acceso al principio y final.
 *
 * Representamos una lista a través de una serie de celdas enlazadas (ver Node), de tal forma
 * que en cada celda se almacena el elemento correspondiente, y un puntero al siguiente.
 * El T.D.A. List se compone de dos punteros a celdas, @e head y @e tail, que apuntan a la
 * cabecera de la lista y a la última posición, respectivamente.
 * Una lista con cabecera de longitud @e n la denotamos:
 *
 * > <*,a1,a2,..,an>
 *
 * Donde * representa la cabecera, que es una posición de la lista apuntada por @e head,
 * en la que no está permitido poner elementos. Su utilidad es que con ella, las operaciones
 * de inserción y borrado en la primera posición no son casos especiales.
 *
 * Si head->next = 0, diremos que la lista está vacia.
 *
 * @author Antonio Coín Castro
 * @author Miguel Lentisco Ballesteros
 * @author José María Martín Luque
 * @date Noviembre 2016
 *
 */

template <class T>
class List
{
  /**
   * @page repConjunto3 Rep del T.D.A. List
   *
   * @section invConjunto3 Invariante de la representación
   *
   * El invariante es: @e head != 0, @e tail != 0
   *
   * @section faConjunto3 Función de abstracción
   *
   * Un objeto válido @e rep del T.D.A. List representa a los valores
   *
   * > (Node<T>*) head, (Node<T>*) tail
   *
   * y además, a la cabecera, una celda vacía apuntada por @e head.
   *
   */
  private:
    Node<T>* head;  ///< Puntero a la cabecera de la lista.
    Node<T>* tail;  ///< Puntero al último nodo de la lista.

  public:
    // ---------------  Constructores ----------------

    /**
     * @brief Constructor por defecto
     * @post Crea una lista vacía (solo contiene la cabecera)
     */
    List();

    /**
     * @brief Constructor de copia
     * @param original Lista a copiar
     */
    List(const List<T>& original);

    // ---------------  Destructor ----------------

    /**
     * @brief Destructor
     * @post Destruye la lista completa dejando head y tail a 0.
     */
    ~List();

    // ---------------  Sobrecarga de operadores ----------------

    /**
     * @brief Sobrecarga del operador de asignación
     * @param l lista que se va a asignar al objeto implícito
     * @return Referencia al objeto implícito
     */
    List& operator=(const List<T>& l);

    // ---------------  Funciones de acceso ----------------

    /**
     * @brief Devuelve el principio de la lista
     * @pre La lista no es vacía
     * @return Referencia a elemento del principio
     */
    T& first() {return head->next->element;}

    /**
     * @brief Devuelve el principio de la lista
     * @pre La lista no es vacía
     * @return Referencia constante al elemento del principio
     */
    const T& first() const {return head->next->element;}

    /**
     * @brief Devuelve el final de la lista
     * @pre La lista no es vacía
     * @return Referencia al elemento del final
     */
    T& last() {return tail->element;}

    /**
     * @brief Devuelve el final de la lista
     * @pre La lista no es vacía
     * @return Referencia constante al elemento del final
     */
    const T& last() const {return tail->element;}

    // ---------------  Funciones de modificación ----------------

    /**
     * @brief Añade un elemento al final de la lista
     * @param e elemento de tipo @c T que se quiere añadir
     */
    void push_back(const T& e);

    /**
     * @brief Elimina el último elemento de la lista
     * @pre La lista no es vacía
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
    bool empty() const {return head->next == 0;}
};

#include "list.cpp"

#endif

/* Fin fichero: list.hpp */
