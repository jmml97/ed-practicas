/**
 * @file stack_max.hpp
 * @brief Fichero de cabecera del T.D.A. StackMax
 *
 * Gestiona una secuencia de parejas de elementos, con facilidades para la inserción
 * y borrado en uno de los extremos. El segundo elemento de la pareja es
 * el máximo (de entre los primeros elementos de las parejas) que hay en la secuencia
 * en ese momento.
 *
 * Además, se permite elegir entre tres representaciones distintas para este T.D.A.
 * @see stack_max_list.hpp
 * @see stack_max_dvector.hpp
 * @see stack_max_queue.hpp
 *
 * Un ejemplo de su uso puede verse en:
 * @example use_stack_max.cpp
 *
 */

#ifndef __STACK_MAX_HPP__
#define __STACK_MAX_HPP__

#include <iostream>

/**
 * @brief T.D.A. Element
 *
 * Una instancia @e e del tipo de datos abstracto Element es un objeto del conjunto
 * de las parejas de números enteros, compuesto por dos enteros @e num y @e max. Este T.D.A.
 * está pensado para usarse en conjunción con el T.D.A. StackMax, ya que el primer entero
 * representa un número cualquiera (que se introduce en la pila), y el segundo representa
 * el máximo número que en ese instante se encuentra en la pila.
 *
 * Lo representamos: `(num,max)`
 *
 * @relates StackMax
 *
 */

struct Element
{
  int num;    ///< Número entero.
  int max;    ///< Número máximo en StackMax.
};

/**
 * @brief Sobrecarga del operador << para Element
 * @param os Flujo de salida
 * @param e Objeto de tipo Element a escribir
 * @post El formato de escritura es el siguiente:
 * > e.num, e.max
 *
 * @relates Element
 */
std::ostream& operator<<(std::ostream& os, const Element& e);

/**
 * Se define la representación deseada para el T.D.A. StackMax.
 *
 *      1 = Usando una lista de celdas enlazadas con cabecera
 *      2 = Usando un vector dinámico
 *      3 = Usando una cola
 */
#define COMPILE_HEADER 1

#if COMPILE_HEADER == 1
  #include "stack_max_list.hpp"
#elif COMPILE_HEADER == 2
  #include "stack_max_dvector.hpp"
#else
  #include "stack_max_queue.hpp"
#endif

/**
 * @brief T.D.A. StackMax
 *
 * Una instancia @e s del tipo de datos abstracto StackMax es un objeto que
 * representa una pila de objetos de tipo Element. Está compuesto por una estructura de
 * datos (@c StackType) @e v, que puede ser una de tres: un vector dinámico, una lista con
 * cabecera ó una cola. Este dato constituye la representación interna de la pila.
 * Una StackMax de longitud @e k la denotamos:
 *
 * > <(num_1,max_1),(num_2, max_2),...,(num_k, max_k)>
 *
 * @see List
 * @see DVector
 * @see Queue
 *
 * @author Antonio Coín Castro
 * @author Miguel Lentisco Ballesteros
 * @author José María Martín Luque
 * @date Noviembre 2016
 *
 */

class StackMax
{
  /**
   * @page repConjunto1 Rep del T.D.A. StackMax
   *
   * @section invConjunto1 Invariante de la representación
   *
   * El invariante es: @e v es de tipo DVector, List ó Queue.
   *
   * @section faConjunto1 Función de abstracción
   *
   * Un objeto válido @e rep del T.D.A. StackMax representa a uno, y solo uno de
   * estos tres valores:
   *
   * > rep = (DVector v), rep = (List v), rep = (Queue v)
   *
   */
  private:
    StackType v;    ///< Representación interna de la pila

  public:
    // ---------------  Constructores ----------------

    /**
     * @brief Constructor por defecto
     * @post Construye una pila vacía
     */
    StackMax() {};

    // ---------------  Funciones de acceso ----------------

    /**
     * @brief Devuelve el elemento del tope de la cola
     * @pre La pila no es vacía
     * @return Referencia al elemento del tope
     */
    Element& top();

    /**
     * @brief Devuelve el elemento del tope de la cola
     * @pre La pila no es vacía
     * @return Referencia constante al elemento del tope
     */
    const Element& top() const;

    // ---------------  Funciones de modificación ----------------

    /**
     * @brief Añade un elemento a la pila
     * @param n Entero usado para crear el elemento a añadir
     * @post El tamaño de la pila aumenta en 1
     */
    void push(int n);

    /**
     * @brief Elimina el elemento del tope
     * @pre La pila no es vacía
     * @post El tamaño de la pila disminuye en 1
     */
    void pop();

    /**
     * @brief Borra la pila completamente
     */
    void clear() {v.clear();}

    // ---------------  Funciones de consulta ----------------

    /**
     * @brief Consulta el tamaño de la pila
     * @return Tamaño de la pila (0 si es vacía)
     */
    int size() const {return v.size();}

    /**
     * @brief Consulta si la pila está vacía
     * @retval true Si está vacía
     * @retval false Si no está vacía
     */
    bool empty() const {return v.empty();}

    /**
     * @brief Consulta si dos pilass tienen el mismo máximo
     * @param s Pila para comparar con el objeto implícito
     * @pre Tanto el objeto implícito como @e s son pilas no vacías.
     * @retval true Si tienen el mismo máximo
     * @retval false Si no tienen el mismo máximo.
     */
    bool sameMax(const StackMax& s) const;

    // ---------------  Funciones de entrada/salida ----------------

    /**
     * @brief Carga una StackMax desde un flujo de entrada
     * @param is Flujo de entrada
     * @pre Hay dos formatos de lectura. En ambos, el tope de la pila
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
     * @see writeStack
     */
    std::istream& loadStack(std::istream& is);

    /**
     * @brief Escribe una StackMax en un flujo de salida
     * @param os Flujo de salida
     * @post El formato de escritura es el siguiente:
     *
     *     n1 max1
     *     n2 max2
     *     n3 max3
     *     ...
     *
     * @see loadStack
     */
    std::ostream& writeStack(std::ostream& os) const;

    /**
     * @brief Escribe una StackMax en un flujo de salida
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
 * @brief Sobrecarga del operador >> para StackMax
 * @param is Flujo de entrada
 * @param s Pila donde leer
 * @pre El formato de lectura es el especificado en la documentación
 *      de StackMax.
 * @post StackMax leída en @e s
 *
 * @see StackMax::loadStack
 * @relates StackMax
 */
std::istream& operator>>(std::istream& is, StackMax& s);

/**
 * @brief Sobrecarga del operador << para StackMax
 * @param os Flujo de salida
 * @param s Pila a escribir
 * @post El formato de escritura es el especificado en la documentación
 *       de StackMax
 *
 * @see StackMax::writeStack
 * @relates StackMax
 */
std::ostream& operator<<(std::ostream& os, const StackMax& s);

#endif

/* Fin fichero: stack_max.hpp */
