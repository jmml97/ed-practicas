/**
  * @file cola.h
  * @brief Fichero cabecera del TDA Cola
  *
  * Gestiona una secuencia de elementos con facilidades para la inserci�n y
  * borrado de elementos en un extremo
  */

#ifndef __Cola_H__
#define __Cola_H__

#include <cassert>

/**
 *  @brief T.D.A. Cola
 *
 *
 * Una instancia @e c del tipo de dato abstracto Cola sobre un dominio @e T es
 * una sucesi�n finita de elementos del mismo con un funcionamiento @e FIFO
 * (First In, First Out}). En una cola, las operaciones de inserci�n tienen
 * lugar en uno de los extremos, denominado @e final de la cola, mientras que
 * el borrado y consulta se lleva a cabo en el otro extremo, denominado
 * @e frente de la cola. Una cola de longitud @e n la denotamos

 * - <a1,a2,a3,..,an<

 * En esta cola, tendremos acceso �nicamente al elemento del @e Frente,
 * es decir, a @e a1. El borrado o consulta de un elemento ser� sobre @e a1,
 * mientras que la inserci�n de un nuevo elemento se har� despu�s de
 * @e an (final de la cola).
 *
 * Si n=0 diremos que la cola est� vac�a.
 *
 * El espacio requerido para el almacenamiento es O(n), donde n es el n�mero
 * de elementos de la cola.
 *
 * @author
 * @date
*/
template <class T>
class Cola{

  private:
    struct Celda {
      T elemento;        ///< Elemento de informaci�n.
      Celda * siguiente; ///< Puntero al siguiente nodo.

      /**
       * @brief Constructor por defecto
       */
      Celda() : siguiente(0){
      }
      /**
       * @brief Constructor con par�metros
       * @param elem Elemento de informaci�n.
       * @param sig Puntero al siguiente nodo.
       */
      Celda(const T & elem, Celda * sig): elemento(elem), siguiente(sig){
      }
    };

    Celda * primera; ///< Puntero al primer nodo de la lista.
    Celda * ultima;  ///< Puntero al �ltimo nodo de la lista.
    int num_elem;    ///< N�mero de elementos de la cola.

  public:
    // ---------------  Constructores ----------------
    /**
     * @brief Constructor por defecto
     */
    Cola(): primera(0), ultima(0), num_elem(0){
    }
    /**
     * @brief Constructor de copias
     * @param original La cola de la que se har� la copia.
     */
    Cola(const Cola<T> & original);
    // ------------------ Destructor ------------------
    /**
     * @brief Destructor
     */
    ~Cola();
    // --------------- Otras funciones ---------------
    /**
     * @brief Operador de asignaci�n
     * @param otra La cola que se va a asignar.
     */
    Cola& operator= (const Cola<T> & otra);
    /**
     * @brief Comprueba si la cola est� vac�a
     */
    bool vacia() const{
      return num_elem==0;
    }
    /**
     * @brief Devuelve el elemento del frente de la cola
     */
    T& frente (){
      assert(primera!=0);        //Si la cola est� vac�a, abortar
      return primera->elemento;  //Devuelve el elemento del frente de la cola
    }
    /**
     * @brief Devuelve el elemento del frente de una cola constante
     */
    const T & frente () const{
      assert(primera!=0);        //Si la cola est� vac�a, abortar
      return primera->elemento;  //Devuelve el elemento del frente de la cola
    }
    /**
     * @brief A�ade un elemento al final de la cola
     * @param elem Elemento que se va a a�adir.
     */
    void poner(const T & elem);
    /**
     * @brief Quita el elemento del frente de la cola
     */
    void quitar();
    /**
     * @brief Devuelve el n�mero de elementos de la cola
     */
    int num_elementos() const{
      return num_elem;
    }
};

#include <cola.cpp>

#endif // __Cola_H__
