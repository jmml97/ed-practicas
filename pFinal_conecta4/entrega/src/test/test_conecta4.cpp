/**
 * @file test_conecta4.cpp
 * @brief Simula una partida de Conecta4 entre dos jugadores humanos
 *
 */

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <stdio.h>
#include <unistd.h>
#include <termio.h>      // Linux/Windows users
//#include <termios.h>   // Mac OSX users
#include "tablero.h"
#include "mando.h"

using namespace std;

/******************************************************************************/
/**
 * @brief Captura el caracter pulsado por teclado (sin necesidad de pulsar, a continuación, Enter).
 * @return: Caracter pulsado (char).
 */
char getch()
{
  char buf = 0;
  struct termios old = {0};

  if (tcgetattr(0, &old) < 0)
    perror("tcsetattr()");

  old.c_lflag &= ~ICANON;
  old.c_lflag &= ~ECHO;
  old.c_cc[VMIN] = 1;
  old.c_cc[VTIME] = 0;

  if (tcsetattr(0, TCSANOW, &old) < 0)
    perror("tcsetattr ICANON");
  if (read(0, &buf, 1) < 0)
    perror ("read()");

  old.c_lflag |= ICANON;
  old.c_lflag |= ECHO;

  if (tcsetattr(0, TCSADRAIN, &old) < 0)
    perror ("tcsetattr ~ICANON");

  return buf;
}

/******************************************************************************/
/**
 * @brief Imprime en pantalla el tablero completo, con el mando y el jugador.
 * @param t : Tablero que se va a imprimir.
 * @param m : Mando indicando la posición del jugador.
 */
void imprimeTablero(Tablero& t, Mando& m)
{
  cout << m.GetJugador() << endl;
  cout << t;
  cout << m.GetBase() << endl;
  cout << m.GetMando() << endl;
}

/******************************************************************************/
/**
 * @brief Implementa el desarrollo de una partida de Conecta 4 sobre un tablero 5x7,
 *        pidiendo por teclado los movimientos de ambos jugadores según turno.
 *
 * @return : Identificador (int) del jugador que gana la partida (1 o 2).
 */
int jugar_partida(int primerJugador)
{
  Tablero tablero(5, 7);      //Tablero 5x7
  Mando mando(tablero);       //Mando para controlar E/S de tablero
  char c = 1;
  int quienGana = 0;
  bool colocada = false;
  bool juegaIA = primerJugador == 2;


  // mientras el tablero no esté lleno ni haya ganador
  while (c != Mando::KB_ESCAPE && !tablero.estaLleno() && quienGana == 0)
  {
    if (juegaIA)
    {
      // POSFIX: implementar en IA para pasarle un tablero y que lo haga por dentro?
      //tablero.colocarFicha(IA.elegirMovimiento());
      tablero.cambiarTurno();
      c = 1;
      juegaIA = false;
    }
    else
    {
      colocada = mando.actualizarJuego(c,tablero);
      system("clear");
      imprimeTablero(tablero, mando);
      if (!colocada)
        c = getch();
      else
        juegaIA = true;
    }

    quienGana = tablero.quienGana();      // hay ganador?
  }

  // Imprimer el tablero final
  c = 1;
  system("clear");
  mando.actualizarJuego(c, tablero);
  imprimeTablero(tablero, mando);

  return tablero.quienGana();
}

int main(int argc, char **argv)
{
  int primerJugador = 1;
  // POSFIX 1: falta filtrado
  // POSFIX 2A: implementar si se quiere IA o sin IA ¿?
  cout << "Bienvenido al Conecta4. Quién empieza primero:\n1.Tú.\n2.IA\n";
  cin >> primerJugador;

  int ganador = jugar_partida(primerJugador);

  if (ganador == 0)
    cout << "\nSe ha producido un empate.\n";
  else
    cout << "\nHa ganado el jugador " << ganador << ".\n";
}

/* Fin fichero: test_conecta4.cpp */
