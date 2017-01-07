/**
 * @file jugador_auto.h
 * @brief Fichero de cabecera para el TDA JugadorAuto
 *
 */

#ifndef __JUGADOR_AUTO_H__
#define __JUGADOR_AUTO_H__

#include "arbol_general.h"
#include "tablero.h"

//TODO documentar

/**
 * @brief T.D.A. JugadorAuto
 *
 */
class JugadorAuto
{
  //TODO: definir métodos
  private:
    ArbolGeneral<Tablero> partida;

  public:
    JugadorAuto();
    ElegirMovimiento();
};

#endif

/* Fin fichero: jugador_auto.h */
