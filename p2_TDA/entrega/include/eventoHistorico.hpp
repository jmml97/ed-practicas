/**
 * @file eventoHistorico.hpp
 * @brief Fichero cabecera del TDA EventoHistorico
 *
 */

#ifndef  __EVENTO_HISTORICO_HPP__
#define  __EVENTO_HISTORICO_HPP__

#include <iostream>
#include <vector>

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

  int anio;   /**< año del calendario*/
  bool dc;    /**< AC ó DC */

  /**
   * @brief Constructor por defecto
   * @post No tiene ningún efecto
   */
  Fecha() {}

  /**
   * @brief Constructor de Fecha. Funciona como conversor implícito de 'int' a 'Fecha'
   * @param n año
   * @post Construye un objeto Fecha @e f con el año indicado, por defecto DC
   */
  Fecha(int n);
};


/**
 * @brief T.D.A. EventoHistorico
 *
 * Una instancia @e e del tipo de datos abstracto @c EventoHistorico es un objeto que
 * representa un evento hisórico sucedido en un año en concreto. Está compuesto por
 * una Fecha @e f y un vector @e evento de n Acontecimientos, que representan, respectivamente, el
 * año en el que sucede el evento histórico, y el conjunto (finito) de acontecimientos
 * sucecidos. Lo representamos:
 *
 * fecha, <acontecimiento_1, acontecimiento_2, ..., acontecimiento_n>
 *
 * @author Miguel Lentisco Ballesteros
 * @author Jose María Martín Luque
 * @author Antonio Coín Castro
 * @date Octubre 2016
 *
 */

class EventoHistorico
{
  private:
      /**
       * @page repConjunto2 Rep del TDA EventoHistorico
       *
       * @section invConjunto2 Invariante de la representación
       *
       * El invariante es \e rep. f.anio >= 0.
       *
       * @section faConjunto2 Función de abstracción
       *
       * Un objeto válido @e rep del TDA EventoHistorico representa al valor
       *
       * (rep.f, rep.evento)
       *
       */

      Fecha f;                              /**< año */
      std::vector<Acontecimiento> evento;   /**< acontecimientos */


      /**
       * @brief Busca en el vector evento un @c Acontecimiento en concreto
       * @param a @c Acontecimiento a buscar
       * @return Devuelve un iterador apuntando a la posición del vector donde
       *         se ha encontrado el @c Acontecimento, o @e evento.end() si no se
       *         ha encontrado.
       */
      std::vector<Acontecimiento>::iterator buscarAcontecimiento(Acontecimiento a);

  public:
      /**
       * @brief Constructor por defecto de la clase.
       * Crea el evento histórico con fecha año 1 DC, y un vector vacío de acontecimientos.
       */
      EventoHistorico();

      /**
       * @brief Constructor de la clase
       * @param f Fecha del evento histórico
       * @return Crea un evento histórico con la fecha determinada, y un vector vacío
       * de acontecimientos.
       * @pre f.anio >= 0
       */
      EventoHistorico(Fecha f);

      /**
       * @brief Constructor de la clase
       * @param f Fecha del evento histórico
       * @param a Vector de acontecimientos
       * @return Crea un evento histórico con la fecha y el vector determinados.
       * @pre f.anio >= 0
       * @pre Los elementos del vector @e a no deben estar repetidos
       */
      EventoHistorico(Fecha f, std::vector<Acontecimiento> a);

      // EventoHistorico(EventoHistorico e);
      // EventoHistorico~() {}
      // EventoHistorico& operator=(EventoHistorico e);

      /**
       * @brief Acceder a la fecha
       * @return La fecha asociada al evento histórico
       */
      Fecha getFecha() const { return f; }

      /**
       * @brief Acceder al vector de acontecimientos
       * @return El vector de acontecimientos asociado al evento histórico
       */
      std::vector<Acontecimiento> getEvento() const { return evento; }

      /**
       * @brief Modificar fecha
       * @param f Nueva fecha
       * @return Sustituye la @c Fecha this->f por f
       * @pre f.anio >= 0
       */
      void setFecha(Fecha f);

      /**
       * @brief Modificar vector de acontecimientos
       * @param a Nuevo vector
       * @return Sustituye el vector this->evento por a
       */
      void setEvento(std::vector<Acontecimiento> a) { this->evento = a; }

      /**
       * @brief Añade un evento al vector de acontecimientos, en caso de que
       * no estuviera ya presente
       * @param  a @c Acontecimiento a añadir
       * @retval true Si se ha añadido
       * @retval false Si no se ha añadido (ya estaba presente)
       */
      bool addEvento(Acontecimiento a);

      /**
       * @brief Mezcla el vector de acontecimientos asociado al objeto implícito
       * con otro que se pasa como parámetro.
       * @param  a @c Vector a mezclar
       * @post this->evento no contiene elementos repetidos
       */
      void addEvento(std::vector<Acontecimiento> a);

      /**
       * @brief Elimina un acontecimiento del vector @e evento
       * @param  a @c Acontecimiento a eliminar
       * @retval true Si se ha eliminado el elemento
       * @retval false Si no se ha eliminado (no estaba presente)
       */
      bool eliminarAcontecimiento(Acontecimiento a);

      /**
       * @brief Elimina del vector @e evento todos los acontecimientos que contengan una
       * palabra clave
       * @param  key Palabra clave
       * @return Número de acontecimientos eliminados
       */
      int eliminarPorClave (std::string key);  // elimina todos los que contengan 'key'; devuelve num eliminados

      /**
       * @brief Busca en el vector @e evento todos los acontecimientos que contengan una
       * palabra clave
       * @param  key Palabra clave
       * @return Vector que contiene los acontecimientos encontrados (vacío si no se ha encontrado ninguno)
       */
      std::vector<Acontecimiento> buscarPorClave (std::string key) const; // busca los que contengan 'key'

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

/* Fin fichero: eventoHistorico.hpp */
