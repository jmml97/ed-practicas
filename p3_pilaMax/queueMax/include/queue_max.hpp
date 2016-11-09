/**
 * @file queue_max.hpp
 * @brief Fichero de cabecera del T.D.A. queueMax
 *
 * Gestiona una secuencia de parejas de enteros realizando todas las operaciones
 * únicamente sobre uno de los extremos. El segundo elemento de la pareja es
 * el entero máximo (de entre los primeros elementos) que hay en la secuencia en ese momento.
 *
 */

#ifndef __QUEUE_MAX_HPP__
#define __QUEUE_MAX_HPP__

#include <iostream>
#include "stack.hpp"

/**
 * @brief T.D.A. Element
 *
 * Una instancia @e e del tipo de datos abstracto Element es un objeto del conjunto
 * de las parejas de números enteros, compuesto por dos enteros @e num y @e max. Este T.D.A.
 * está pensado para usarse en conjunción con el T.D.A. QueueMax, ya que el primer entero
 * representa un número cualquiera (que se introduce en la pila), y el segundo representa
 * el máximo número que en ese instante se encuentra en la pila.
 *
 * Lo representamos: `(num,max)`
 *
 * @see QueueMax
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
 * representa una cola de Element. Está compuesto por una estructura de datos (@c QueueType) @e v,
 * que es una pila. Este dato constituye la representación interna de una cola de Element.
 * Una StackMax de longitud @e k la denotamos:
 *
 * > <(num_1,max_1), (num_2, max_2),...,(num_k, max_k)>
 *
 * @see Stack
 *
 * @author Antonio Coín Castro
 * @author Miguel Lentisco Ballesteros
 * @author Jose María Martín Luque
 * @date 09/11/2016
 *
 */
class QueueType
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
        Stack<Element> v;   ///< Representación interna de una cola

    public:
        // ---------------  Constructores ----------------
        /**
         * @brief Constructor por defecto
         * @post Construye una QueueMax vacía
         */
        QueueMax() {};

        // ---------------  Funciones de acceso ----------------

        /**
         * @brief Devuelve el elemento del frente de la cola
         * @return Referencia al elemento frente de la cola
         */
        T& front();

        /**
         * @brief Devuelve el elemento del frente de una cola constante
         * @return Referencia constante al elemento frente de la cola
         */
        const T& front() const;

        // ---------------  Funciones de modificación ----------------

        /**
         * @brief Añade un elemento al final de QueueMax
         * @param int n usado para crear el Elemento a añadir.
         */
        void push(int n);

        /**
         * @brief Quita el elemento del frente de QueueMax
         */
        void pop();

        /**
         * @brief Borra QueueMax
         */
        void clear();

        // ---------------  Funciones de consulta ----------------

        /**
         * @brief Devuelve el número de elementos de QueueMax
         */
        int size() const;

        /**
         * @brief Comprueba si QueueMax está vacía
         * @retval true Si está vacía
         * @retval false Si no está vacía
         */
        bool empty() const;


        // ---------------  Funciones de entrada/salida ----------------

        std::istream& loadQueue(std::istream& is);
        std::ostream& writeQueue(std::ostream& os) const;
        std::ostream& prettyPrint(std::ostream& os = std::cout) const;  // formato: (num,max)
};

/**
 * @brief Sobrecarga del operador >> para QueueMax
 * @param is Flujo de entrada
 * @param s QueueMax donde leer
 * @pre El formato de lecura es el siguiente, donde la primera línea indica
 *      el tope de la QueueMax:
 *
 * ???????????????????????
 *
 * @post QueueMax leída en @e s
 *
 * @relates QueueMax
 */
std::istream& operator>>(std::istream& is, QueueMax& q);

/**
 * @brief Sobrecarga del operador << para QueueMax
 * @param os Flujo de salida
 * @param s QueueMax a escribir
 * @post El formato de escritura es el mismo que el de lectura
 *
 * @see operator>>
 * @relates QueueMax
 */
std::ostream& operator<<(std::ostream& os, const QueueMax& q);

#endif

/* Fin fichero: queue_max.hpp */
