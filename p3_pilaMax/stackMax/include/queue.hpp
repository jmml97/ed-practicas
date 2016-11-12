/**
 * @file queue.hpp
 * @brief Fichero de cabecera del T.D.A. Queue
 *
 * Gestiona una secuencia de elementos con facilidades para la inserción
 * de elementos en un extremo, y borrado y consulta en el otro.
 *
 * Un ejemplo de su uso puede consultarse en:
 * @example test_queue.cpp
 *
 */

#ifndef __QUEUE_HPP__
#define __QUEUE_HPP__

#include <cassert>
#include "node.hpp"

/**
 *  @brief T.D.A. Queue
 *
 * Una instancia @e q del tipo de dato abstracto Queue (cola) sobre un dominio @e T es
 * una sucesión finita de elementos del mismo con un funcionamiento @e FIFO
 * (First In, First Out). En una cola, las operaciones de inserción tienen
 * lugar en uno de los extremos, denominado @e final de la cola, mientras que
 * el borrado y consulta se lleva a cabo en el otro extremo, denominado
 * @e frente de la cola. Una cola de longitud @e n la denotamos
 *
 * > <a1,a2,a3,...,an>
 *
 * En esta cola, tendremos acceso únicamente al elemento del @e Frente,
 * es decir, a @e a1. El borrado o consulta de un elemento será sobre @e a1,
 * mientras que la inserción de un nuevo elemento se hará después de
 * @e an (final de la cola).
 *
 * Si @e n = 0 diremos que la cola está vacía.
 *
 * El espacio requerido para el almacenamiento es @e O(n), donde @e n es el número
 * de elementos de la cola.
 *
 */

template <class T>
class Queue
{
  /**
   * @page repConjunto4 Rep del T.D.A. Queue
   *
   * @section invConjunto4 Invariante de la representación
   *
   * El invariante es: @e n >= 0.
   *
   * @section faConjunto4 Función de abstracción
   *
   * Un objeto válido @e rep del T.D.A. Queue representa a los valores
   *
   * > (Node<T>*) head, (Node<T>*) tail, (int) n
   *
   */
  private:
    Node<T>* head;  ///< Puntero al primer nodo de la lista.
    Node<T>* tail;  ///< Puntero al último nodo de la lista.
    int n;          ///< Número de elementos de la cola.

  public:
    // ---------------  Constructores ----------------

    /**
     * @brief Constructor por defecto
     */
    Queue() : head(0), tail(0), n(0) {}

    /**
     * @brief Constructor de copias
     * @param original La cola de la que se hará la copia.
     */
    Queue(const Queue<T>& original);

    // ------------------ Destructor ------------------

    /**
     * @brief Destructor
     */
    ~Queue() {clear();}

    // --------------- Sobrecarga de operadores ---------------

    /**
     * @brief Operador de asignación
     * @param q La cola que se va a asignar.
     */
    Queue& operator=(const Queue<T>& q);

    // --------------- Funciones de acceso ---------------

    /**
     * @brief Devuelve el elemento del frente de la cola
     * @return Referencia al elemento frente de la cola
     */
    T& front()
    {
      assert(head);
      return head->element;
    }

    /**
     * @brief Devuelve el elemento del frente de una cola
     * @return Referencia constante al elemento frente de la cola
     */
    const T& front() const
    {
      assert(head);
      return head->element;
    }

    // --------------- Funciones de modificación ---------------

    /**
     * @brief Añade un elemento al final de la cola
     * @param elem Elemento que se va a añadir.
     */
    void push(const T& elem);

    /**
     * @brief Quita el elemento del frente de la cola
     * @pre La cola no puede ser vacía
     */
    void pop();

    /**
     * @brief Borra la cola, dejando head y tail a 0
     */
    void clear();

    // --------------- Funciones de consulta ---------------

    /**
     * @brief Devuelve el número de elementos de la cola
     */
    int size() const {return n;}

    /**
     * @brief Comprueba si la cola está vacía
     * @retval true Si está vacía
     * @retval false Si no está vacía
     */
    bool empty() const {return n == 0;}
};

#include "queue.cpp"

#endif

/* Fin fichero: queue.hpp */
