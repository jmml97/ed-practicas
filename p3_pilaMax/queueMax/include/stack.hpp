/**
  * @file stack.hpp
  * @brief Fichero cabecera del T.D.A Stack
  *
  * Gestiona una secuencia de elementos con facilidades para la inserción y
  * borrado de elementos en un extremo.
  *
  * Un ejemplo de su uso puede consultarse en:
  * @example test_stack.cpp
  *
  */

#ifndef __STACK_HPP__
#define __STACK_HPP__

#include <cassert>
#include "node.hpp"

/**
 *  @brief T.D.A. Stack
 *
 * Una instancia @e s del tipo de dato abstracto Stack (pila) sobre un dominio @e T es
 * una sucesión finita de elementos del mismo con un funcionamiento @e LIFO
 * (Last In, First Out). En una pila, las operaciones de inserción, borrado y
 * consulta tienen lugar en uno de los extremos, denominado @e tope de la pila. Una pila
 * es un puntero al tope, donde cada elemento de la pila se representa por una celda enlazada.
 * Una pila de longitud @e n la denotamos
 *
 * > <a_n,a_n-1,...,a_1>
 *
 * En esta pila, tendremos acceso únicamente al elemento del @e tope,
 * es decir, a @e a_n. Las operaciones tanto de inserción como de borrado se
 * realizan también sobre @e a_n.
 *
 * Si @e n = 0 diremos que la pila está vacía.
 *
 * En este T.D.A. Stack se incluye un segundo dato miembro, un puntero al fondo de la
 * pila @e last [1]. Esto se hace para permitir el acceso al fondo desde un método de la clase
 * QueueMax. Sin embargo, este campo es innecesario para el correcto funcionamiento
 * del T.D.A. por sí solo.
 *
 * @see Node
 * @see QueueMax
 *
 * @author Antonio Coín Castro
 * @author Miguel Lentisco Ballesteros
 * @author José María Martín Luque
 * @date Noviembre 2016
 *
 */

template <class T>
class Stack
{
  /**
   * @page repConjunto6 Rep del T.D.A. Stack
   *
   * @section invConjunto6 Invariante de la representación
   *
   * El invariante es: @e first apunta al tope de la pila, o es 0 si está vacía
   *
   * @section faConjunto6 Función de abstracción
   *
   * Un objeto válido @e rep del T.D.A. Stack representa al valor
   *
   * > (Node<T>*) first, (Node<T>*) last
   *
   */
  private:
    Node<T>* first;  ///< Puntero al tope de la pìla
    Node<T>* last;   ///< Puntero al fondo de la pila [1]

    /**
     * Clase amiga: QueueMax.
     * Es necesario para implementar el método QueueMax::front
     */
    friend class QueueMax;

  public:
    // ---------------  Constructores ----------------

    /**
     * @brief Constructor por defecto
     */
    Stack() : first(0), last(0) {}

    /**
     * @brief Constructor de copias
     * @param s La pila de la que se hará la copia.
     */
    Stack(const Stack<T>& s);

    // ------------------ Destructor ------------------

    /**
     * @brief Destructor
     */
    ~Stack() {clear();}

    // --------------- Sobrecarga de operadores ---------------

    /**
     * @brief Operador de asignación
     * @param s La pila que se va a asignar.
     */
    Stack<T>& operator=(const Stack<T>& s);

    // --------------- Funciones de acceso ---------------

    /**
     * @brief Devuelve el tope de la pila
     * @return Referencia al tope de la pila
     * @pre Pila no vacía
     */
    T& top()
    {
      assert(first);
      return first->element;
    }

    /**
     * @brief Devuelve el tope de la pila
     * @return Referencia constante al tope de la pila
     * @pre Pila no vacía
     */
    const T& top() const
    {
      assert(first);
      return first->element;
    }

    // --------------- Funciones de modificación ---------------

    /**
     * @brief Añade un elemento a la pila
     * @param e Elemento que se va a añadir.
     */
    void push(const T& e);

    /**
     * @brief Quita el elemento del tope de la pila
     * @pre La pila no es vacía
     */
    void pop();

    /**
     * @brief Borra la pila, dejando first y last a 0
     */
    void clear();

    // --------------- Funciones de consulta ---------------

    /**
     * @brief Devuelve el número de elementos de la pila
     */
    int size() const;

    /**
     * @brief Comprueba si la pila está vacía
     * @retval true Si está vacía
     * @retval false Si no está vacía
     */
    bool empty() const {return !first;}
};

#include "stack.cpp"

#endif

/* Fin fichero: stack.hpp */
