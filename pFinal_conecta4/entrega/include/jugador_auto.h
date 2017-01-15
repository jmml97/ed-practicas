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
  //TODO función de abstracción + representación
  private:
    ArbolGeneral<Tablero> partida;   ///< Espacio de soluciones
    int metrica;                     ///< Métrica escogida
    const static int N = 5;          ///< Profundidad máxima a explorar

    int metrica1(); // la mejor (?): explorar hasta profundidad N y asignar ponderaciones a jugadas
    int metrica2(); // comprobar jugadas con 3 o 2 fichas en línea de IA // evitar las del humano
    int metrica3(); // comprobar unicamente si se gana o se pierde; si no, insertar aleatoriamente
    int metrica4(); // la peor (?): elegir columna aleatoria

    /**
     * @brief Genera el espacio de soluciones para un tablero vacío,
     * explorando hasta una profundidad variable según la métrica.
     * @param profundidad Profundidad hasta la que se explora
     */
    void generarArbolSoluciones(int profundidad);

    /**
     * @brief Actualiza el espacio de soluciones de la partida
     * @param tablero Tablero actual
     */
    void actualizarSoluciones(const Tablero& tablero);

  public:
    /**
     * @brief Construye un jugador automático, a partir de un tablero inicial
     * y una métrica dados.
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
    int elegirMovimiento(int num_metrica);

    /**
     * @brief Procesa un turno del jugador automático.
     * @param actual Tablero actual de la partida
     */
    void turnoAutomatico(Tablero& actual);
};

#endif

/* Fin fichero: jugador_auto.h */
