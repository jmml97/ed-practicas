/**
 * @file queue_max.hpp
 * @brief Fichero de cabecera del T.D.A. QueueMax
 *
 * Gestiona una secuencia de parejas de elementos, con facilidades para la inserción en
 * un extremo, y para la consulta y el borrado en otro extremo. El segundo elemento de la
 * pareja es el máximo (de entre los primeros elementos de las parejas) que hay en la secuencia
 * en ese momento.
 *
 * Un ejemplo de su uso puede verse en:
 * @example use_queue_max.cpp
 *
 */

#ifndef __QUEUE_MAX_HPP__
#define __QUEUE_MAX_HPP__

#include <iostream>
#include <cassert>
#include "stack.hpp"

/**
 * @brief T.D.A. Element
 *
 * Una instancia @e e del tipo de datos abstracto Element es un objeto del conjunto
 * de las parejas de números enteros, compuesto por dos enteros @e num y @e max. Este T.D.A.
 * está pensado para usarse en conjunción con el T.D.A. QueueMax, ya que el primer entero
 * representa un número cualquiera (que se introduce en la cola), y el segundo representa
 * el máximo número que en ese instante se encuentra en la cola.
 *
 * Lo representamos: `(num,max)`
 *
 * @relates QueueMax
 *
 */

struct Element
{
  int num;    ///< Número entero.
  int max;    ///< Número máximo en QueueMax.
};

/**
 * @brief Sobrecarga del operador << para Element
 * @param os Flujo de salida
 * @param e Element a escribir
 * @post El formato de escritura es el siguiente:
 *   > e.num, e.max
 *
 * @relates Element
 */
std::ostream& operator<<(std::ostream& os, const Element& e);

/**
 * @brief T.D.A. QueueMax
 *
 * Una instancia @e s del tipo de datos abstracto QueueMax es un objeto que
 * representa una cola de objetos de tipo Element. La representación interna se
 * logra mediante una pila (Stack) de objetos de tipo Element.
 * Una ColaMax de longitud @e k la denotamos:
 *
 * > <(num_1,max_1),(num_2, max_2),...,(num_k, max_k)>
 *
 * @see Stack
 *
 * @author Antonio Coín Castro
 * @author Miguel Lentisco Ballesteros
 * @author José María Martín Luque
 * @date Noviembre 2016
 *
 */

class QueueMax
{
  /**
   * @page repConjunto5 Rep del T.D.A. QueueMax
   *
   * @section invConjunto5 Invariante de la representación
   *
   * El invariante es: @e v.first apunta al final de la cola, o es 0 si está vacía
   *
   * @section faConjunto5 Función de abstracción
   *
   * Un objeto válido @e rep del T.D.A. QueueMax representa al valor:
   *
   * > (Stack<Element>) v
   *
   */
  private:
    Stack<Element> v;   ///< Pila de parejas de enteros

  public:
    // ---------------  Constructores ----------------

    /**
     * @brief Constructor por defecto
     * @post Construye una cola vacía
     */
    QueueMax() {};

    // ---------------  Funciones de acceso ----------------

    /**
     * @brief Devuelve el elemento del frente de la cola
     * @pre La cola no es vacía
     * @return Referencia al elemento frente de la cola
     */
    Element& front();

    /**
     * @brief Devuelve el elemento del frente de la cola
     * @pre La cola no es vacía
     * @return Referencia constante al elemento frente de la cola
     */
    const Element& front() const;

    /**
     * @brief Devuelve el elemento del final de la cola
     * @pre La cola no es vacía
     * @return Referencia al elemento último de la cola
     */
    Element& tail()
    {
      assert(!v.empty());
      return v.top();
    }

    /**
     * @brief Devuelve el elemento del final de la cola
     * @pre La cola no es vacía
     * @return Referencia constante al elemento último de la cola
     */
    const Element& tail() const
    {
      assert(!v.empty());
      return v.top();
    }

    // ---------------  Funciones de modificación ----------------

    /**
     * @brief Añade un elemento al final de la cola
     * @param n Entero usado para crear el elemento a añadir.
     * @post El tamaño de la cola aumenta en 1
     */
    void push(int n);

    /**
     * @brief Quita el elemento del frente de la cola
     * @pre La cola no es vacía
     * @post El tamaño de la cola disminuye en 1
     */
    void pop();

    /**
     * @brief Borra la cola completamente
     */
    void clear() {v.clear();}

    // ---------------  Funciones de consulta ----------------

    /**
     * @brief Consulta el número de elementos de la cola
     * @return Tamaño de la cola (0 si es vacía)
     */
    int size() const {return v.size();}

    /**
     * @brief Consulta si la cola está vacía
     * @retval true Si está vacía
     * @retval false Si no está vacía
     */
    bool empty() const {return v.empty();}

    /**
     * @brief Consulta si dos colas tienen el mismo máximo
     * @param q Cola para comparar con el objeto implícito
     * @pre Tanto el objeto implícito como @e q son colas no vacías.
     * @retval true Si tienen el mismo máximo
     * @retval false Si no tienen el mismo máximo.
     */
    bool sameMax(const QueueMax& q) const;

    // ---------------  Funciones de entrada/salida ----------------

    /**
     * @brief Carga una QueueMax desde un flujo de entrada
     * @param is Flujo de entrada
     * @pre Hay dos formatos de lectura. En ambos, el frente de la cola
     *      es el que se encuentra más arriba.
     *
     * - Formato 1:
     *
     *       n1 max1
     *       n2 max2
     *       n3 max3
     *       ...
     *
     * - Formato 2:
     *
     *       $
     *       n1
     *       n2
     *       n3
     *       ...
     *
     * El segundo formato necesita el símbolo '$' al inicio del archivo
     * para ser reconocido como un formato válido de entrada. El primer formato
     * se mantiene por compatibilidad con el formato de escritura, aunque los
     * diferentes máximos son ignorados en la lectura.
     *
     * @see writeQueue
     */
    std::istream& loadQueue(std::istream& is);

    /**
     * @brief Escribe una QueueMax en un flujo de salida
     * @param os Flujo de salida
     * @post El formato de escritura es el siguiente:
     *
     *     n1 max1
     *     n2 max2
     *     n3 max3
     *     ...
     *
     * @see loadQueue
     */
    std::ostream& writeQueue(std::ostream& os) const;

    /**
     * @brief Escribe una QueueMax en un flujo de salida
     * @param os Flujo de salida. Por defecto es std::cout
     * @post El formato de escritura es el siguiente:
     *
     *     (n1,max1)
     *     (n2,max2)
     *     (n3,max3)
     *     ...
     */
    std::ostream& prettyPrint(std::ostream& os = std::cout) const;
};

/**
* @brief Sobrecarga del operador >> para QueueMax
* @param is Flujo de entrada
* @param q Cola donde leer
* @pre El formato de lectura es el especificado en la documentación
*      de QueueMax.
* @post QueeuMax leída en @e q
*
* @see QueueMax::loadQueue
* @relates QueueMax
*/
std::istream& operator>>(std::istream& is, QueueMax& q);

/**
* @brief Sobrecarga del operador << para QueueMax
* @param os Flujo de salida
* @param q Cola a escribir
* @post El formato de escritura es el especificado en la documentación
*       de QueueMax
*
* @see QueueMax::writeQueue
* @relates QueueMax
*/
std::ostream& operator<<(std::ostream& os, const QueueMax& q);

#endif

/* Fin fichero: queue_max.hpp */
