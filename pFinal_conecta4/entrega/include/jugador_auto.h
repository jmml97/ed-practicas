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
 */
class JugadorAuto
{
  private:
    ArbolGeneral<Tablero> partida;

  public:
    JugadorAuto();
};

#endif

/* Fin fichero: jugador_auto.h */
