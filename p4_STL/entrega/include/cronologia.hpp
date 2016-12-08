/**
 * @file cronologia.hpp
 * @brief Fichero cabecera del T.D.A. Cronologia
 *
 */

#ifndef __CRONOLOGIA_HPP__
#define  __CRONOLOGIA_HPP__

#include <iostream>
#include <map>
#include "evento_historico.hpp"

/**
 * @brief Comparador para el T.D.A. EventoHistorico
 *
 * Diremos que un EventoHistorico es más reciente que otro
 * si el primero sucedió en un año mayor, entendiendo los años
 * D.C. como positivos, y los años A.C. como negativos.
 *
 */

struct compEventos
{
  /**
   * @brief Comprobar cuál es el más reciente de dos eventos históricos.
   * @param  a Primer objeto @c EventoHistorico
   * @param  b Segundo objeto @c EventoHistorico
   * @retval true Si el @c EventoHistorico @e a es más reciente que el EventoHistorico @e b
   * @retval false Si el @c EventoHistorico @e b es más reciente que el EventoHistorico @e a
   */
  bool operator()(const EventoHistorico& a, const EventoHistorico& b) const
  {
      Fecha f1 = a.getFecha();
      Fecha f2 = b.getFecha();
      return !((f1.dc < f2.dc) || (f2.dc && f1.anio <= f2.anio)
                || !(f1.dc && f1.anio >= f2.anio));
  }
};

/**
 * @brief T.D.A. Cronologia
 *
 * Una instancia @e e del tipo de datos abstracto @c Cronologia es un objeto que
 * representa una sucesión de eventos históricos ordenados cronológicamente por año.
 * Está compuesto por un diccionario @e datos de EventoHistorico, que representa la sucesión
 * de años y los distintos acontecimientos que han tenido lugar en ese año, ordenados
 * según el criterio definido en compEventos. Lo representamos:
 *
 * < <f_1,eventoHistorico_1>, <f_2,eventoHistorico_2>, ..., <f_n,eventoHistorico_n> >
 *
 * @author Miguel Lentisco Ballesteros
 * @author Jose María Martín Luque
 * @author Antonio Coín Castro
 * @date Octubre 2016
 *
 */

class Cronologia
{
  /**
   * @page repConjunto3 Rep del T.D.A. Cronologia
   *
   * @section invConjunto3 Invariante de la representación
   *
   * El invariante es:
   *
   * > EventoHistorico_1 < ... < EventoHistorico_n, con el orden definido
   *   en compEventos
   *
   * @section faConjunto3 Función de abstracción
   *
   * Un objeto válido @e rep del T.D.A. Cronologia representa al valor
   *
   * rep.datos
   *
   */

  private:
    std::map<Fecha,EventoHistorico,compEventos> datos;

  public:
    /// Alias para el contenedor de la clase
    typedef std::map<Fecha,EventoHistorico,compEventos> container_type;
    /// Alias para el iterador de std::map
    typedef typename container_type::iterator iterator;
    /// Alias para el iterador constante de std::map
    typedef typename container_type::const_iterator const_iterator;

    // ---------------  Constructores ----------------

    /**
     * @brief Constructor por defecto de la clase
     * Crea un objeto con un contenedor vacío.
     */
    Cronologia() {}

    /**
      * @brief Constructor de la clase
      * @param v Contenedor de EventoHistorico
      * @return Crea una Cronologia con el contenedor de EventoHistorico dado
      */
    Cronologia(const container_type& v) { setCronologia(v); }

    // ---------------  Métodos de acceso ----------------

    /**
     * @brief Acceder al contenedor de EventoHistorico
     * @return El contenedor de EventoHistorico asociado a la Cronologia
     */
    container_type getCronologia() const { return datos; }

    /**
     * @brief Accede a un EventoHistorico del contenedor @e datos
     * @param f @c Fecha del EventoHistorico a consultar
     * @return El EventoHistorico asociado a la fecha
     * @pre f debe ser una clave existente en el contenedor
     *
     * También permite la modificación del elemento.
     */
    EventoHistorico& operator[](const Fecha& f);

    /**
     * @brief Acceder al primer año de la cronología
     * @return Una @c Fecha que representa el primer año en la cronología
     */
    Fecha getPrimero() const { return datos.begin()->first; }

    /**
     * @brief Acceder al último año de la cronología
     * @return Una @c Fecha que representa el último año en la cronología
     */
    Fecha getUltimo() const { return (--datos.end())->first; }

    // ---------------  Métodos de modificación -----------------

    /**
     * @brief Modificar contenedor de EventoHistorico
     * @param v @c Nuevo contenedor
     * @return Sustituye el contenedor this->datos por v
     */
    void setCronologia(const container_type& v) { datos = v; }

    /**
     * @brief Modifica un EventoHistorico de la Cronologia
     * @param v Conjunto de Acontecimiento, f @c Fecha del EventoHistorico
     * @post El EventoHistorico asociado a la Fecha f contiene los acontecimientos del conjunto v
     * @pre f debe ser una clave existente en el contenedor
     */
    void setEventoHistorico(const std::set<Acontecimiento>& v, const Fecha& f)
    {
      datos[f].setEvento(v);
    }

    /**
     * @brief Añade un EventoHistorico al contenedor @c datos.
     * @param  e @c EventoHistorico a añadir
     * @post Si no estaba ya presente, el nuevo EventoHistorico @e e está en @e datos.
     *       En caso contrario, se mezclan los acontecimientos de los conjuntos de
     *       @c Acontecimiento, eliminando los repetidos.
     */
    void addEventoHistorico(const EventoHistorico& e);

    /**
     * @brief Elimina un EventoHistorico del contenedor @e datos
     * @param  f @c Fecha del EventoHistorico a eliminar
     * @retval true Si se ha eliminado el elemento
     * @retval false Si no se ha eliminado (no estaba presente)
     */
    bool eliminarEvento(const Fecha& f) { return datos.erase(f); }

    /**
     * @brief Elimina del contenedor @e datos todos los EventoHistorico cuyos acontecimientos
     * contengan una palabra o frase clave.
     * @param  key Palabra clave
     * @return Número de EventoHistorico eliminados
     */
    int eliminarPorClave (const std::string& key);

    // ---------------  Métodos de consulta -----------------

    /**
     * @brief Comprueba si hay un EventoHistorico con la fecha dada en el contenedor @e datos
     * @param  f @c Fecha del EventoHistorico a comprobar
     * @retval true Si se encuentra el elemento
     * @retval false Si no estaba presente
     */
    bool contieneFecha(const Fecha& f) const { return datos.count(f) > 0; }

    /**
     * @brief Busca en el contenedor @e datos un EventoHistorico en concreto
     * @param f @c Fecha del EventoHistorico a buscar
     * @return Devuelve un iterador constante apuntando a la posición del contenedor donde
     * se ha encontrado el EventoHistorico, o @e datos.end() si no se ha encontrado.
     */
    const_iterator buscarEvento(const Fecha& f) const
    {
      return datos.find(f);
    }

    // ---------------  Métodos de E/S -----------------

    /**
     * @brief Leer una cronología desde un flujo de entrada
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

    // ---------------  Iteradores ----------------

    /**
     *  Devuelven un iterador bidireccional a la pareja
     *  <Fecha, EventoHistorico> menor, según el orden marcado.
     */
    iterator begin() { return datos.begin(); }
    const_iterator begin() const { return datos.begin(); }

    /**
     *  Devuelven un iterador bidireccional a la posición siguiente a
     *  la pareja <Fecha, EventoHistorico> mayor, según el orden marcado.
     */
    iterator end() { return datos.end(); }
    const_iterator end() const { return datos.end(); }
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
