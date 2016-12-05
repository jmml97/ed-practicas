/**
 * @file evento_historico.hpp
 * @brief Fichero cabecera del TDA EventoHistorico
 *
 */

#ifndef  __EVENTO_HISTORICO_HPP__
#define  __EVENTO_HISTORICO_HPP__

#include <iostream>
#include <set>

/**
 * @brief Tipo @c Acontecimiento
 *
 * Definimos un nuevo tipo @c Acontecimiento, compuesto por un @e string,
 * que representa un acontecimiento histórico. Lo representamos:
 *
 * acontecimiento
 *
 */

typedef std::string Acontecimiento;

/**
 * @brief T.D.A. Fecha
 *
 * Una instancia @e f del tipo de datos abstracto @c Fecha es un objeto del conjunto
 * de los años del calendario Gregoriano, compuesto por un entero @e anio y un booleano @e dc que
 * representan, respectivamente, un año, y si ese año es Antes de Cristo (0), o
 * Despues de Cristo (1). Lo representamos:
 *
 * anio, dc
 *
 * @author Miguel Lentisco Ballesteros
 * @author Jose María Martín Luque
 * @author Antonio Coín Castro
 * @date Octubre 2016
 *
 */

struct Fecha
{
  /**
   * @page repConjunto1 Rep del TDA Fecha
   *
   * @section invConjunto1 Invariante de la representación
   *
   * El invariante es \e rep.anio >= 0.
   *
   * @section faConjunto1 Función de abstracción
   *
   * Un objeto válido @e rep del TDA Fecha representa al valor
   *
   * (rep.anio, rep.dc)
   *
   */

  int anio;   ///< Año del calendario
  bool dc;    ///< Indica si el año es AC o DC

  /**
   * @brief Constructor por defecto
   * @post Año por defecto: 1 DC
   */
  Fecha() : anio(1), dc(1) {}

  /**
   * @brief Constructor de Fecha. Funciona como conversor implícito de 'int' a 'Fecha'
   * @param n El año
   * @post Construye un objeto Fecha @e f con el año indicado, por defecto DC
   */
  Fecha(int n);
};


/**
 * @brief T.D.A. EventoHistorico
 *
 * Una instancia @e e del tipo de datos abstracto @c EventoHistorico es un objeto que
 * representa un evento hisórico sucedido en un año en concreto. Está compuesto por
 * una pareja @e ev que contiene una Fecha y un conjunto de acontecimientos, que representan, respectivamente, el
 * año en el que sucede el evento histórico, y el conjunto (finito) de acontecimientos
 * sucecidos. Lo representamos:
 *
 * < fecha, <acontecimiento_1, acontecimiento_2, ..., acontecimiento_n> >
 *
 * @author Miguel Lentisco Ballesteros
 * @author Jose María Martín Luque
 * @author Antonio Coín Castro
 * @date Octubre 2016
 *
 */

class EventoHistorico
{
  /**
   * @page repConjunto2 Rep del TDA EventoHistorico
   *
   * @section invConjunto2 Invariante de la representación
   *
   * El invariante es:
   *
   * > ev.first.anio >= 0
   *
   * @section faConjunto2 Función de abstracción
   *
   * Un objeto válido @e rep del TDA EventoHistorico representa al valor
   *
   * > rep.ev
   *
   */
  private:
      std::pair<Fecha, std::set<Acontecimiento> > ev; ///< pareja Fecha-<eventos>

  public:
      typedef typename std::set<Acontecimiento>::iterator iterator; ///< iterador de EventoHistorico
      typedef typename std::set<Acontecimiento>::const_iterator const_iterator; ///< iterador constante de EventoHistorico

      // ---------------  Constructores ----------------

      /**
       * @brief Constructor por defecto de la clase.
       * Crea el evento histórico con fecha año 1 DC, y un conjunto vacío de acontecimientos.
       */
      EventoHistorico() {}

      /**
       * @brief Constructor de la clase
       * @param f Fecha del evento histórico
       * @return Crea un evento histórico con la fecha determinada, y un conjunto vacío
       * de acontecimientos.
       * @pre f.anio >= 0
       */
      EventoHistorico(Fecha f) { setFecha(f); }

      /**
       * @brief Constructor de la clase
       * @param f Fecha del evento histórico
       * @param a Conjunto de acontecimientos
       * @return Crea un evento histórico con la fecha y el conjunto determinados.
       * @pre f.anio >= 0
       */
      EventoHistorico(Fecha f, const std::set<Acontecimiento>& a);

      /**
       * @brief Acceder a la fecha
       * @return La fecha asociada al evento histórico
       */
      Fecha getFecha() const { return ev.first; }

      /**
       * @brief Acceder al conjunto de acontecimientos
       * @return El conjunto de acontecimientos asociado al evento histórico
       */
      std::set<Acontecimiento> getEvento() const { return ev.second; }

      /**
       * @brief Modificar fecha
       * @param f Nueva fecha
       * @return Sustituye la Fecha this->ev.first por f
       * @pre f.anio >= 0
       */
      void setFecha(Fecha f);

      /**
       * @brief Modificar conjunto de acontecimientos
       * @param a Nuevo conjunto
       * @return Sustituye el conjunto this->ev.second por a
       */
      void setEvento(const std::set<Acontecimiento>& a) { ev.second = a; }

      /**
       * @brief Añade un evento al conjunto de acontecimientos, en caso de que
       * no estuviera ya presente
       * @param  a @c Acontecimiento a añadir
       * @retval true Si se ha añadido
       * @retval false Si no se ha añadido (ya estaba presente)
       */
      bool addEvento(Acontecimiento a) { return ev.second.insert(a).second; }

      /**
       * @brief Mezcla el conjunto de acontecimientos asociado al objeto implícito
       * con otro que se pasa como parámetro.
       * @param a @c Conjunto a mezclar
       */
      void addEvento(const std::set<Acontecimiento>& a);

      /**
       * @brief Elimina un acontecimiento del conjunto @e ev.second
       * @param  a @c Acontecimiento a eliminar
       * @retval true Si se ha eliminado el elemento
       * @retval false Si no se ha eliminado (no estaba presente)
       */
      bool eliminarAcontecimiento(Acontecimiento a) { return ev.second.erase(a); }

      /**
       * @brief Elimina un acontecimiento del conjunto @e ev.second
       * @param it iterador constante al acontecimiento a eliminar
       * @pre El acontecimiento apuntado por @e it está en el conjunto
       * @retval true Si se ha eliminado el elemento
       * @retval false Si no se ha eliminado (no estaba presente)
       */
       void eliminarAcontecimiento(const_iterator it);

      /**
       * @brief Elimina del conjunto @e ev.second todos los acontecimientos que contengan una
       * palabra clave
       * @param  key Palabra clave
       * @return Número de acontecimientos eliminados
       */
      int eliminarPorClave(std::string key);

      /**
       * @brief Busca en el conjunto @e conj un @c Acontecimiento en concreto
       * @param a @c Acontecimiento a buscar
       * @return Devuelve un iterador constante apuntando a la posición del conjunto donde
       *         se ha encontrado el @c Acontecimento, o @e ev.second.end() si no se
       *         ha encontrado.
       */
      const_iterator buscarAcontecimiento(Acontecimiento a) const { return ev.second.find(a); }

      /**
       * @brief Busca en el conjunto @e evento todos los acontecimientos que contengan una
       * palabra clave
       * @param  key Palabra clave
       * @return Conjunto que contiene los acontecimientos encontrados (vacío si no se ha encontrado ninguno)
       */
      std::set<Acontecimiento> buscarPorClave(std::string key) const;

      /**
       * @brief Comprueba si un Acontecimiento está en el evento histórico
       * @param a Acontecimiento a comprobar
       * @retval true Si el acontecimiento está en el evento
       * @retval false Si no lo está
       */
      bool tieneAcontecimiento(const Acontecimiento& a) const { return ev.second.count(a); }

      /**
       * @brief Leer un evento desde un flujo de entrada
       * @param  is Flujo de entrada
       * @post Evento histórico leído en el objeto implícito
       * @pre El formato de lecura es el siguiente, donde 1 repesenta DC, y 0 representa AC:
       *      1/0#Año#acontecimiento_1#acontecimiento_2# ...#acontecimiento_n
       */
      std::istream& cargarEvento(std::istream& is);

      /**
       * @brief Mostrar el objeto implícito (evento histórico) en un flujo de salida
       * @param  os Flujo de salida
       * @post El formato de escritura es el mismo que el de lectura
       *
       * @see cargarEvento
       */
      std::ostream& mostrarEvento(std::ostream& os) const;

      /**
       * Muestra un evento en un flujo de salida en Human Readable Format (HRF)
       * @param  os Flujo de salida. Por defecto es std::cout
       * @post El formato de escritura es el siguiente:
       *       Año: <año> <AC/DC>
       *       - <acontecimiento_1>
       *       - <acontecimiento_2>
       *       - ...
       *       - <acontecimiento_n>
       */
      std::ostream& prettyPrint(std::ostream& os = std::cout) const;

      // ---------------  Iteradores ----------------

      iterator begin() { return ev.second.begin(); }
      const_iterator begin() const { return ev.second.begin(); }

      iterator end() { return ev.second.end(); }
      const_iterator end() const { return ev.second.end(); }
};

/**
 * @brief Sobrecarga del operador >>
 * @param is Flujo de entrada
 * @param e Evento histórico donde leer
 * @retval EventoHistorico leído en @e e
 * @pre El formato de lecura es el siguiente, donde 1 repesenta DC, y 0 representa AC:
 *      1/0#Año#acontecimiento_1#acontecimiento_2# ...#acontecimiento_n
 *
 * @relates EventoHistorico
 */
std::istream& operator>>(std::istream& is, EventoHistorico& e);

/**
 * @brief Sobrecarga del operador <<
 * @param os Flujo de salida
 * @param e Evento histórico a escribir
 * @post El formato de escritura es el mismo que el de lectura
 *
 * @see operator>>
 * @relates EventoHistorico
 */
std::ostream& operator<<(std::ostream& os, const EventoHistorico& e);

#endif

/* Fin fichero: evento_historico.hpp */
