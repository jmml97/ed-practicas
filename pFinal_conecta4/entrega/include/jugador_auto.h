/**
 * @file jugador_auto.h
 * @brief Fichero de cabecera para el TDA JugadorAuto
 *
 */

#ifndef __JUGADOR_AUTO_H__
#define __JUGADOR_AUTO_H__

#include "arbol_general.h"
#include "tablero.h"

/**
 * @brief T.D.A. JugadorAuto
 *
 * Una instancia @j del T.D.A. JugadorAuto representa un jugador automático
 * en el juego Conecta-4. Este jugador se encarga de decidir la columna donde
 * pondrá su ficha, apoyándose en una @e métrica determinada para hacerlo.
 *
 * Estas métricas se basan en explorar el espacio de soluciones de la partida,
 * representado como un ArbolGeneral. Para aquellas métricas que lo empleen,
 * se define la profundidad máxima @e N que se puede explorar en el árbol.
 *
 */
class JugadorAuto
{
  private:
    ArbolGeneral<Tablero> partida;   ///< Espacio de soluciones
    int metrica;                     ///< Métrica escogida
    const static int N = 5;          ///< Profundidad máxima a explorar

    /// Ver documentación adjunta: memoria.pdf
    int metrica1();
    int metrica2();
    int metrica3();
    int metrica4();

    /**
     * @brief Amplía el espacio de soluciones hasta una profundidad
     * dada.
     * @param profundidad Profundidad hasta la que se explora
     */
    void generarArbolSoluciones(int profundidad);

    /**
     * @brief Actualiza el espacio de soluciones de la partida
     * @param tablero Tablero actual
     */
    void actualizarSoluciones(const Tablero& tablero);

    /**
     * @brief Calcula el número de partidas ganadas por el jugador automático
     * en el subárbol que cuelga de un nodo.
     * @param n Nodo donde mirar.
     * @lvl Nivel del nodo actual en el árbol.
     * @return Número de partidas ganadas por el jugador auto
     */
    int calcularPartidasGanadas(ArbolGeneral<Tablero>::Nodo n, int lvl);

    /**
     * @brief Comprueba si el jugador automático puede ganar la partida
     * introduciendo una ficha.
     * @return Columna donde debe introducir para ganar, o -1 si no se da
     * el caso.
     */
    int gana_inmediato();

    /**
     * @brief Computa los casos en los que el jugador automático no
     * pierde la partida al introducir su ficha
     * @return Un vector de Nodo, con los nodos donde el jugador automático
     * puede insertar ficha sin miedo a perder en el siguiente turno.
     */
    vector<ArbolGeneral<Tablero>::Nodo> evita_perder();

    /**
     * @brief Computa la columna donde se obtendría una mayor puntuación
     * al insertar.
     * @param v Vector de Nodo con los nodos donde buscar
     * @see calcularPartidasGanadas
     */
    int mayorPuntuacion(vector<ArbolGeneral<Tablero>::Nodo> v);

  public:
    /**
     * @brief Constructor por defecto. Crea un árbol vacío,
     * con la métrica por defecto
     */
    JugadorAuto() : metrica(1) { }

    /**
     * @brief Construye un jugador automático, a partir de un tablero inicial
     * y una métrica dados. Genera el árbol de soluciones.
     * @param inicial Tablero inicial de la partida
     * @param metrica Número de métrica elegida (por defecto la mejor)
     */
    JugadorAuto(const Tablero& inicial, int num_metrica = 1);

    /**
     * @brief Devuelve el árbol que representa el espacio de soluciones.
     */
    ArbolGeneral<Tablero> getArbol() { return partida; }

    /**
     * @brief Simula un movimiento del jugador automático según
     * la métrica escogida. Es útil si queremos conocer la columna donde
     * insertaría el jugador, sin necesidad de realizar la inserción.
     * @param num_metrica Métrica elegida (0 significa la métrica asociada al jugador
     * automático)
     * @return Columna donde se insertaría la ficha del jugador automático
     */
    int elegirMovimiento(int num_metrica = 0);

    /**
     * @brief Procesa un turno del jugador automático.
     * @param actual Tablero actual de la partida
     */
    void turnoAutomatico(Tablero& actual);
};

#endif

/* Fin fichero: jugador_auto.h */
