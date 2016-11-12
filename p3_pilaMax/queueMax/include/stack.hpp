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
 * consulta tienen lugar en uno de los extremos, denominado @e tope de la pila.
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
   * > (Node<T>*) first
   *
   */
  private:
    Node<T>* first;  ///< Puntero al tope de la pìla

  public:

    Stack() : first(0) {}
    Stack(const Stack<T>& s);
    ~Stack() {clear();}

    Stack<T>& operator=(const Stack<T>& s);

    // pre: no vacío
    T& top()
    {
      assert(first);
      return first->element;
    }

    // pre: no vacío
    const T& top() const
    {
      assert(first);
      return first->element;
    }

    void push(const T& e);
    // pre: no vacio. Devuelve lo que borra
    void pop();
    void clear();

    int size() const;
    bool empty() const {return !first;}
};

#include "stack.cpp"

#endif

/* Fin fichero: stack.hpp */
