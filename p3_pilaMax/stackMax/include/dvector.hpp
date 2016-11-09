/**
 * @file dvector.hpp
 * @brief Fichero de cabecera del T.D.A. DVector
 *
 * Gestiona un vector dinámico con funciones para la inserción
 * y el borrado de elementos así como para ampliar el vector.
 *
 * Un ejemplo de su uso puede consultarse en:
 * @example test_dvector.cpp
 *
 */

#ifndef __DVECTOR_HPP__
#define __DVECTOR_HPP__

/**
 * @brief T.D.A. DVector
 *
 * Una instancia @e v del tipo de dato abstracto Dvector sobre un dominio @e T
 * es una sucesión finita de elementos del mismo.
 * En un vector la inserción se puede realizar en cualquier posición. De igual
 * forma, podemos obtener el elemento de la posición que queramos.
 *
 * Los vectores tienen un cierto tamaño, que puede ampliarse o reducirse en
 * cualquier momento.
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
   * El invariante es: @e n >= 0.
   *
   * @section faConjunto2 Función de abstracción
   *
   * Un objeto válido @e rep del T.D.A. DVector representa a los valores
   *
   * > (T) data, (int) n, (int) reserved
   *
   */
  private:
    T* data;      ///< Puntero al primer elemento del vector.
    int n;        ///< Número de elementos del vector.
    int reserved; ///< Número de elementos reservados del vector.

  public:
    // ---------------  Constructores ----------------

    /**
     * @brief Constructor por defecto
     */
    DVector() : data(0), n(0), reserved(0) {}

    /**
     * @brief Constructor con parámetros.
     * @param size Tamaño del vector.
     * @param d Elemento que se le va a asignar a todos los índices
     * del vector.
     */
    DVector(int size, T d);

    /**
     * @brief Constructor de copias
     * @param v El vector del que se hará la copia.
     */
    DVector(const DVector& v);

    // --------------- Funciones de modificación ---------------

    /**
     * @brief Establece el elemento de la posición deseada al valor indicado.
     * @param i Posición del elemento que se quiere cambiar.
     * @param d Valor deseado para el elemento.
     */
    void set(int i, T d) {data[i] = d;}

    // --------------- Funciones de acceso ---------------

    /**
     * @brief Devuelve el elemento de la posición deseada.
     * @param i Posición del elemento que se quiere obtener.
     * @return Elemento de la posición deseada.
     */
    T get(int i) const {return data[i];}

    // --------------- Sobrecarga de operadores ---------------

    /**
     * @brief Operador de asignación.
     * @param v El vector que se le va a asignar.
     */
    DVector& operator= (const DVector& v);

    /**
     * @brief Operador de acceso.
     * @param i Posición del elemento que se quiere obtener.
     * @return Elemento de la posición deseada.
     */
    T& operator[] (const int i) {return get(i);}
    const T& operator[] (const int i) const {return get(i);}

    // --------------- Otras funciones ---------------

    /**
     * @brief Borra el contenido del vector. Cambia su tamaño y reservados a 0.
     */
    void clear();

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
     */
    bool empty() {return n == 0;};

    /**
     * @brief Cambia la capacidad del vector a la que se le especifique.
     */
    void reserve(int size);

    /**
     * @brief Cambia la capacidad del vector y el número de elementos
     * utilizados.
     * @param nzise Nuevo número de elementos.
     */
    void resize(int nsize);

    /**
     * @brief Intercambia el contenido de dos vectores.
     * @param v Vector cuyo contenido queremos intercambiar.
     */
    void swap(DVector& v);

    /**
     * @brief Añade un elemento al final del vector.
     * @param d Elemento que queremos añadir.
     */
    void push_back(T d);

    /**
     * @brief Elimina el elemento del final del vector.
     */
    void push_back() {resize(n--);}

    /**
     * @brief Ajusta el número de reservados al número de elementos.
     */
    void shrink_to_fit();

    // ------------------ Destructor ------------------

    /**
     * @brief Destructor
     */
    ~DVector() {clear();}

};

#include "dvector.cpp"

#endif

/* Fin fichero: dvector.hpp */
