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
 * acontecimientos que han tenido lugar en ese año. Lo representamos:
 *
 * <eventoHistorico_1, eventoHistorico_2, ..., eventoHistorico_n>
 *
 * Un ejemplo de su uso:
 * @include usoCronologia.hpp
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
     * El invariante es \e rep. EventoHistorico_1.f < ... < EventoHistorico_n.f,
     * con el orden natural de nuestro calendario.
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
     * @brief Ordena los EventoHistorico cronológicamente mediante mergeSort
     * @post Vector @e this->c ordenado cronológicamente
     */
    void ordenar();

  public:

    /**
     * @brief Constructor por defecto de la clase
     * Crea un objeto con un vector vacío de EventoHistorico.
     */
    Cronologia() {}

    /**
      * @brief Constructor de la clase
      * @param v Vector de EventoHistorico
      * @return Crea una Cronologia con el vector de EventoHistorico dado
      */
    Cronologia(const std::vector<EventoHistorico>& v);

    /**
     * @brief Acceder al vector de EventoHistorico
     * @return El vector de EventoHistorico asociado a la Cronologia
     */
    std::vector<EventoHistorico> getCronologia() const { return c; }

    /**
     * @brief Acceder a un EventoHistorico del vector @c c
     * @param f @c Fecha del EventoHistorico a consultar
     * @return El EventoHistorico asociado a la fecha
     * @pre Debe haber en el vector @e c un EventoHistorico que tenga a f
     *      por Fecha
     */
    EventoHistorico getEventoHistorico(Fecha f) const;

    /**
     * @brief Accede a los acontecimientos de un EventoHistorico buscando con su fecha
     * @param f @c Fecha del EventoHistorico a buscar
     * @return @c Vector de Acontecimiento del EventoHistorico buscado
     * @pre Debe haber en el vector @e c un EventoHistorico que tenga a f
     *      por Fecha
     */
    std::vector<Acontecimiento> getAcontecimientos(Fecha f) const;

    /**
     * @brief Modificar vector de EventoHistorico
     * @param v @c Nuevo vector
     * @return Sustituye el vector this->c por v
     */
    void setCronologia(const std::vector<EventoHistorico>& v);

    /**
     * @brief Modifica un EventoHistorico de la Cronologia
     * @param v @c Vector de Acontecimiento, f @c Fecha del EventoHistorico
     * @post El EventoHistorico asociado a la Fecha f contiene los acontecimientos
     *       del vector v
     * @pre Debe haber en el vector @e c un EventoHistorico que tenga a f
     *      por Fecha
     */
    void setEventoHistorico(const std::vector<Acontecimiento>& v, Fecha f);

    /**
     * @brief Añade un EventoHistorico al vector @c
     * @param  e @c EventoHistorico a añadir
     * @post Si no estaba ya presente, el nuevo EventoHistorico @e e está en @e c.
     *       En caso contrario, se mezclan los acontecimientos de los vectores de
     *       @c Acontecimiento, eliminando los repetidos. El vector @e c está ordenado.
     */
    void addEventoHistorico(const EventoHistorico& e);

    /**
     * @brief Mezcla el vector de EventoHistorico asociado al objeto implícito
     * con otro que se pasa como parámetro.
     * @param  v @c Vector a mezclar
     * @post En cada caso, si no estaba ya presente, el nuevo EventoHistorico @e e está en @e c.
     *       En caso contrario, se mezclan los acontecimientos de los vectores de
     *       @c Acontecimiento, eliminando los repetidos. El vector @e c está ordenado.
     */
    void addEventoHistorico(const std::vector<EventoHistorico>& v);

    /**
     * @brief Mezcla dos Cronologia en una sola (en el objeto implícito)
     * @param cron @c Cronologia que se quiere mezclar
     * @post this->c está ordenado y sin repetidos.
     */
    void mezclarCronologia(const Cronologia& cron);

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
     * @brief Elimina del vector @e c todos los EventoHistorico cuyos acontecimientos
     * contengan una palabra clave
     * @param  key Palabra clave
     * @return Número de EventoHistorico eliminados
     */
    int eliminarPorClave (std::string key);

    /**
     * @brief Busca en el vector @e c todos los EventoHistorico cuyos acontecimientos
     * contengan una palabra clave
     * @param  key Palabra clave
     * @return Vector que contiene los @c EventoHistorico encontrados (vacío si no se ha encontrado ninguno)
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
     *
     * @see EventoHistorico::cargarEvento
     */
    std::istream& cargarCronologia(std::istream& is);

    /**
     * @brief Mostrar el objeto implícito en un flujo de salida
     * @param  os Flujo de salida
     * @post El formato de escritura es el mismo que el de lectura
     *
     * @see cargarCronologia
     */
    std::ostream& mostrarCronologia(std::ostream& os) const;

    /**
     * @brief Mostrar el objeto implícito en un flujo de salida
     * @param  os Flujo de salida
     * @post El formato de escritura es el mismo que el de lectura, pero
     *       se muestra en orden inverso
     *
     * @see cargarCronologia
     */
    std::ostream& mostrarCronologiaInversa(std::ostream& os) const;

    /**
     * Muestra el objeto implícito en un flujo de salida en Human Readable Format (HRF)
     * @param  os Flujo de salida. Por defecto es std::cout
     * @post El formato de escritura es el siguiente:
     *       - EventoHistorico_1 (HRF)
     *       - EventoHistorico_1 (HRF)
     *       - ...
     *       - EventoHistorico_n (HRF)
     *
     * @see EventoHistorico::prettyPrint
     */
    std::ostream& prettyPrint(std::ostream& os = std::cout) const;
};

/**
 * @brief Sobrecarga del operador >>
 * @param is Flujo de entrada
 * @param cron Cronologia donde leer
 * @retval Cronología leída en @e cro
 * @pre El formato de lectura es el siguiente:
 *      EventoHistorico_1
 *      EventoHistorico_2
 *      ....
 *      EventoHistorico_n
 *
 * @relates Cronologia
 */
std::istream& operator>>(std::istream& is, Cronologia& cron);

/**
 * @brief Sobrecarga del operador <<
 * @param os Flujo de salida
 * @param cron Cronología a escribir
 * @post El formato de escritura es el mismo que el de lectura
 *
 * @see operator>>
 * @relates Cronologia
 */
std::ostream& operator<<(std::ostream& os, const Cronologia& cron);

#endif

/* Fin fichero: cronologia.hpp */
