/**
  * @file cronologia.hpp
  * @brief Fichero cabecera del TDA Cronologia
  *
  */

#ifndef __CRONOLOGIA_HPP__
#define  __CRONOLOGIA_HPP__

#include <iostream>
#include <vector>
#include "eventoHistorico.hpp"

/**
  * @brief T.D.A. Cronologia
  *
  * Una instancia @e e del tipo de datos abstracto @c Cronologia es un objeto que
  * representa una sucesión de eventos históricos ordenados cronológicamente por año. Está compuesto por
  * un vector @e c de EventoHistorico, que representa la sucesión de años y los distintos
  * hechos históricos que han tenido lugar en ese año, todos ordenados.
  * Lo representamos:
  *
  * <eventoHistorico_1, eventoHistorico_2, ..., eventoHistorico_n>
  *
  * @author Miguel Lentisco Ballesteros
  * @author Jose María Martín Luque
  * @author Antonio Coín Castro
  * @date Octubre 2016
  *
  */

class Cronologia
{
  private:
    /**
        * @page repConjunto2 Rep del TDA Cronologia
        *
        * @section invConjunto2 Invariante de la representación
        *
        * El invariante es \e rep. EventoHistorico_1 < ... < EventoHistorico_n.
        *
        * @section faConjunto2 Función de abstracción
        *
        * Un objeto válido @e rep del TDA Cronologia representa al valor
        *
        * (rep.c)
        *
    */
    std::vector<EventoHistorico> c;

    /**
     * @brief Busca en el vector c un @c EventoHistorico en concreto
     * @param f @c Fecha del EventoHistorico a buscar
     * @return Devuelve un iterador apuntando a la posición del vector donde
     *         se ha encontrado el @c EventoHistorico, o @e c.end() si no se
     *         ha encontrado.
     */
    std::vector<EventoHistorico>::iterator busquedaBinaria(Fecha f);  // buscar evento en this->c

    /**
     * @brief Busca en el vector c un @c EventoHistorico en concreto
     * @param f @c Fecha del EventoHistorico a buscar
     * @return Devuelve un iterador constante apuntando a la posición del vector donde
     *         se ha encontrado el @c EventoHistorico, o @e c.end() si no se
     *         ha encontrado.
     */
    std::vector<EventoHistorico>::const_iterator busquedaBinaria(Fecha f) const;


    /**
     * @brief Ordena el vector de EventoHistorico
     * @param izq @c indice izquierdo del vector, med @c indice medio del vector, der @c indice derecho del vector
     */
    void merge(int izq, int med, int der);

    /**
     * @brief Divide el vector en trozos muy pequeños para ordenarlo más fácilmente
     * @param  izq @c índice izquierdo del vector, der @c índice derecho del vector
     */
    void mergeSort(int izq, int der);

    /**
     * @brief Ordena los EventoHistorico cronológicamente mediante mergeSort
     */
    void ordenar(); // ordenar vector completo por fecha

  public:
      /**
       * @brief Constructor de la clase
       * @param v Vector de EventoHistorico
       * @return Crea una Cronologia con el vector de EventoHistorico determinado
       * @pre @c Vector ordenado
       * @pre Los elementos del vector @e v no deben estar repetidos
       */
    Cronologia(std::vector<EventoHistorico> v);

    /**
     * @brief Acceder al vector de EventoHistorico
     * @return El vector de EventoHistorico asociado a la Cronologia
     */
    std::vector<EventoHistorico> getCronologia() const { return c; }

    /**
     * @brief Acceder a un EventoHistorico del vector @c c
     * @param f @c Fecha del EventoHistorico necesitado
     * @return El EventoHistorico asociado a la fecha
     */
    EventoHistorico getEventoHistorico(Fecha f) const;

    /**
     * @brief Modificar vector de EventoHistorico
     * @param v Nuevo vector
     * @return Sustituye el vector this->c por v
     */
    void setCronologia(std::vector<EventoHistorico> v) { this->c = v; }

    /**
     * @brief Añade un EventoHistorico al vector @c c, en caso de que
     * no estuviera ya presente
     * @param  e @c EventoHistorico a añadir
     * @retval true Si se ha añadido
     * @retval false Si no se ha añadido (ya estaba presente)
     */
    bool addEventoHistorico(EventoHistorico e); // merge

    /**
     * @brief Mezcla el vector de EventoHistorico asociado al objeto implícito
     * con otro que se pasa como parámetro.
     * @param  v @c Vector a mezclar
     * @post this->c no contiene elementos repetidos
     */
    void addEventoHistorico(std::vector<EventoHistorico> v);



    void addCronologia(const Cronologia& cron);

    /**
     * @brief Comprueba si hay un EventoHistorico con la fecha dada en el vector @e c
     * @param  f @c Fecha del EventoHistorico a comprobar
     * @retval true Si se encuentra el elemento
     * @retval false Si no estaba presente
     */
    bool contieneFecha(Fecha f) const;

    /**
     * @brief Elimina un EventoHistorico del vector @e c
     * @param  f @c Fecha del EventoHistorico a eliminar
     * @retval true Si se ha eliminado el elemento
     * @retval false Si no se ha eliminado (no estaba presente)
     */
    bool eliminarEvento(Fecha f);

    /**
     * @brief Elimina del vector @e c todos los EventoHistorico que contengan una
     * palabra clave
     * @param  key Palabra clave
     * @return Número de EventoHistorico eliminados
     */
    int eliminarPorClave (std::string key);

    /**
     * @brief Busca en el vector @e c todos los EventoHistorico que contengan una
     * palabra clave
     * @param  key Palabra clave
     * @return Vector que contiene los EventoHistorico encontrados (vacío si no se ha encontrado ninguno)
     */
    std::vector<EventoHistorico> buscarPorClave (std::string key) const;

    /**
     * @brief Leer una cronologia desde un flujo de entrada
     * @param  is Flujo de entrada
     * @post Cronología leída en el objeto implícito
     * @pre El formato de lecura es el siguiente:
     *          EventoHistorico_1
     *          EventoHistorico_2
     *          ....
     *          EventoHistorico_n
     */
    std::istream& cargarCronologia(std::istream& is);

    /**
     * @brief Mostrar el objeto implícito (cronología) en un flujo de salida
     * @param  os Flujo de salida
     * @post El formato de escritura es el mismo que el de lectura
     * @see cargarEvento
     */
    std::ostream& mostrarCronologia(std::ostream& os) const;

    /**
     * @brief Mostrar el objeto implícito (cronología) en un flujo de salida
     * @param  os Flujo de salida
     * @post El formato de escritura es el mismo que el de lectura, pero
     *       se muestra a la inversa temporalmente.
     * @see cargarEvento
     */
    std::ostream& mostrarCronologiaInversa(std::ostream& os) const;

    /**
     * Muestra un evento en un flujo de salida en Human Readable Format
     * @param  os Flujo de salida. Por defecto es std::cout
     * @post El formato de escritura es el siguiente:
     *       - EventoHistorico_1
     *       - EventoHistorico_1
     *       - ...
     *       - EventoHistorico_n
     */
    std::ostream& prettyPrint(std::ostream& os = std::cout) const;
};

/**
 * @brief Sobrecarga del operador >>
 * @param is Flujo de entrada
 * @param cro Cronologia donde leer
 * @retval Cronología leída en @e cro
 * @pre El formato de lectura es el siguiente:
 *      EventoHistorico_1
 *      EventoHistorico_2
 *      ....
 *      EventoHistorico_n
 * @relates Cronologia
 */
std::istream& operator>>(std::istream& is, Cronologia& cro);

/**
 * @brief Sobrecarga del operador <<
 * @param os Flujo de salida
 * @param cro Cronología a escribir
 * @post El formato de escritura es el mismo que el de lectura
 * @see operator>>
 * @relates Cronologia
 */
std::ostream& operator<<(std::ostream& os, const Cronologia& cro);

#endif

/* Fin fichero: cronologia.hpp */
