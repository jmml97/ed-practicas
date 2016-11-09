/**
 * @file dvector.hpp
 * @brief Fichero de cabecera del T.D.A. DVector
 *
 * Gestiona una secuencia de elementos con funciones para la inserción
 * y borrado en posiciones aleatorias, así como posibilidad de ampliar
 * o reducir el tamaño a voluntad.
 *
 * Un ejemplo de su uso puede consultarse en:
 * @example test_dvector.cpp
 *
 */

#ifndef __DVECTOR_HPP__
#define __DVECTOR_HPP__

#include <cassert>

/**
 * @brief T.D.A. DVector
 *
 * Una instancia @e v del tipo de dato abstracto DVector (vector) sobre un
 * dominio @e T es una sucesión finita de elementos del mismo.
 * En un vector, la inserción se puede realizar en cualquier posición. De igual
 * forma, podemos obtener el elemento de la posición que queramos. Un vector de
 * @e n elementos lo representamos:
 *
 * > <a1,a2,...,an>
 *
 * Los vectores tienen un cierto tamaño, que puede ampliarse o reducirse en
 * cualquier momento. Si @e n = 0, diremos que el vector está vacío.
 *
 * @author Antonio Coín Castro
 * @author Miguel Lentisco Ballesteros
 * @author José María Martín Luque
 * @date Noviembre 2016
 *
 */

template <class T>
class DVector
{
  /**
   * @page repConjunto2 Rep del T.D.A. DVector
   *
   * @section invConjunto2 Invariante de la representación
   *
   * El invariante es: @e n >= 0, @e reserved >= 0.
   *
   * @section faConjunto2 Función de abstracción
   *
   * Un objeto válido @e rep del T.D.A. DVector representa a los valores
   *
   * > (T) data, (int) n, (int) reserved
   *
   */
  private:
    T* data;        ///< Puntero al primer elemento del vector.
    int n;          ///< Número de elementos del vector.
    int reserved;   ///< Capacidad del vector.

  public:
    // ---------------  Constructores ----------------

    /**
     * @brief Constructor por defecto
     */
    DVector() : data(0), n(0), reserved(0) {}

    /**
     * @brief Constructor con parámetros.
     * @param size Tamaño del vector.
     * @param d Elemento para rellenar todas las posiciones
     *          del vetor.
     */
    DVector(int size, T d);

    /**
     * @brief Constructor de copias
     * @param v El vector del que se hará la copia.
     */
    DVector(const DVector<T>& v);

    // ------------------ Destructor ------------------

    /**
     * @brief Destructor
     */
    ~DVector() {clear();}

    // --------------- Funciones de modificación ---------------

    /**
     * @brief Establece el elemento de la posición deseada al valor indicado.
     * @param i Posición del elemento que se quiere cambiar.
     * @param d Valor deseado para el elemento.
     * @pre La posición i debe cumplir 0 <= i < n
     */
    void set(int i, T d)
    {
      assert(i >= 0 && i < n);
      data[i] = d;
    }

    // --------------- Sobrecarga de operadores ---------------

    /**
     * @brief Operador de asignación.
     * @param v El vector que se le va a asignar al objeto implícito
     */
    DVector& operator=(const DVector<T>& v);

    /**
     * @brief Operador corchete. Permite el acceso a un elemento en la
     *        posición deseada.
     * @param i Posición del elemento que se quiere obtener.
     * @pre La posición i debe cumplir 0 <= i < n.
     * @return Referencia al elemento de la posición deseada.
     */
    T& operator[](int i)
    {
      assert(i >= 0 && i < n);
      return data[i];
    }

    /**
     * @brief Operador corchete. Permite el acceso a un elemento en la
     *        posición deseada.
     * @param i Posición del elemento que se quiere obtener.
     * @pre La posición i debe cumplir 0 <= i < n.
     * @return Referencia constante al elemento de la posición deseada.
     */
    const T& operator[](int i) const
    {
      assert(i >= 0 && i < n);
      return data[i];
    }

    // --------------- Funciones de acceso ---------------

    /**
     * @brief Devuelve el elemento de la posición deseada.
     * @param i Posición del elemento que se quiere obtener.
     * @pre La posición i debe cumplir 0 <= i < n
     * @return Elemento de la posición deseada.
     */
    T get(int i) const
    {
      assert(i >= 0 && i < n);
      return data[i];
    }

    // --------------- Funciones de modificación ---------------

    /**
     * @brief Añade un elemento al final del vector.
     * @param d Elemento que queremos añadir.
     * @post Si no hay espacio, y el vector tiene elementos, aumenta
     *       la capacidad al doble de la actual.
     */
    void push_back(T d);

    /**
     * @brief Elimina el elemento del final del vector.
     * @pre n > 0
     * @post Borrado lógico del elemento del final.
     */
    void pop_back()
    {
      assert(n > 0);
        n--;
    }

    /**
     * @brief Aumenta la capacidad del vector, si es necesario,
     *        hasta el tamaño especificado.
     * @param size Capacidad deseada
     */
    void reserve(int size);

    /**
     * @brief Disminuye la capacidad del vector a la mitad
     * @pre n <= reserved/2
     */
    void shrink();

    /**
     * @brief Cambia la capacidad del vector y el número de elementos
     *        utilizados.
     * @param nzise Nuevo número de elementos.
     * @post Si nsize < n, se realiza un borrado lógico de los elementos
     *       mayores que nsize.
     */
    void resize(int nsize);

    /**
     * @brief Ajusta el número de reservados al número de elementos.
     */
    void shrink_to_fit();

    /**
     * @brief Borra el contenido del vector, y todos sus campos a 0.
     * @post Borrado físico, el vector queda vacío
     */
    void clear();

    // --------------- Funciones de consulta ---------------

    /**
     * @brief Devuelve el tamaño del vector.
     * @return Tamaño del vector.
     */
    int size() const {return n;}

    /**
     * @brief Devuelve la capacidad del vector.
     * @return Capacidad del vector.
     */
    int capacity() const {return reserved;}

    /**
     * @brief Devuelve si el vector está vacío.
     * @retval true Si está vacío
     * @retval false Si no está vacío
     */
    bool empty() const {return n == 0;}

    // --------------- Otras funciones ---------------

    /**
     * @brief Intercambia el contenido de dos vectores.
     * @param v Vector cuyo contenido queremos intercambiar.
     */
    void swap(DVector& v);
};

#include "dvector.cpp"

#endif

/* Fin fichero: dvector.hpp */
