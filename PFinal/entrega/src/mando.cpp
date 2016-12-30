/**
 * @file mando.cpp
 * @brief Implementación de funciones del TDA Mando
 */

#include <iostream>
#include "mando.h"

using namespace std;

Mando::Mando(Tablero t)
{
  // Inicializamos el mando, el jugador y la base.
  base = " ";
  for(int i = 0; i < t.GetColumnas()*2; i++) // Es *2 para que visualmente haya más espacio.
  {
    mando = mando + " ";
    jugador = jugador + " ";
    base = base + "-";
  }
  posicion = 0;
  mando.at(posicion+1) = '^';

  if(t.GetTurno() == 1)
    jugador.at(posicion+1) = Tablero::CHAR_J1;
  else
    jugador.at(posicion+1) = Tablero::CHAR_J2;
}

/* _________________________________________________________________________ */

bool Mando::actualizarJuego(char c, Tablero& t)
{
  bool colocada = false;

  // Actualizamos la posición del mando.
  if(c == KB_LEFT)
  {
    if(posicion > 0)
    {
      mando.at(posicion+1) = ' ';
      jugador.at(posicion+1) = ' ';
      posicion -= 2;
    }
  }
  else if(c == KB_RIGHT)
  {
    if(posicion < t.GetColumnas()*2 - 2)
    {
      mando.at(posicion+1) = ' ';
      jugador.at(posicion+1) = ' ';
      posicion += 2;
    }
  }
  else if (c == KB_SPACE)
  {
    // Cambiamos de turno y ponemos la ficha en su sitio si hay hueco.
    colocada = t.colocarFicha(posicion/2);
    if(colocada)
      t.cambiarTurno();
  }
  mando.at(posicion+1) = '^';

  if(t.GetTurno() == 1)
    jugador.at(posicion+1) = Tablero::CHAR_J1;
  else
    jugador.at(posicion+1) = Tablero::CHAR_J2;

  return colocada;
}

/* Fin fichero: mando.cpp */
