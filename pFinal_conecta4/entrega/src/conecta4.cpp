/**
 * @file conecta4.cpp
 * @brief Implementa una partida del juego Conecta 4
 *
 * Este programa simula una partida del juego Conecta 4 en un tablero
 * de tamaño variable.
 *
 * //TODO documentar (argumentos)
 */

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <stdio.h>
#include <unistd.h>
#include "mando.h"
#include "jugador_auto.h"

#ifdef __APPLE__
  #include <termios.h>  // macOS
#else
  #include <termio.h>   // Linux/Windows
#endif

using namespace std;


/**
 * @brief Captura el caracter pulsado por teclado.
 * No hay necesidad de pulsar, a continuación, Enter.
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

/**
 * @brief Imprime en pantalla el tablero completo, con el mando y el jugador.
 * @param t Tablero que se va a imprimir.
 * @param m Mando indicando la posición del jugador.
 */
void ImprimeTablero(Tablero& t, Mando& m)
{
  cout << m.GetJugador() << endl;
  cout << t;
  cout << m.GetBase() << endl;
  cout << m.GetMando() << endl;
}

/**
 * @brief Implementa el desarrollo de una partida de Conecta 4 sobre un tablero de
 *        tamaño variable, pidiendo por teclado los movimientos de el/los jugador(es)
 *        humano(s).
 * @param tablero Tablero inicial de la partida
 * @param metrica Métrica para aplicar al jugador automático (0 si los dos jugadores son
 *                humanos).
 * @return Identificador (int) del jugador que gana la partida (1 o 2), o 0 en
 *         caso de empate o partida sin finalizar.
 */
int JugarPartida(Tablero& tablero, int metrica)
{
  Mando mando(tablero);
  char c = 1;
  int quienGana = 0;
  bool colocada;

  // mientras el tablero no esté lleno ni haya ganador
  while (c != Mando::KB_ESCAPE && !tablero.estaLleno() && quienGana == 0)
  {
    if (metrica != 0 && tablero.GetTurno() == 2)
    {
      JugadorAuto j2(tablero, metrica);
      while(!tablero.colocarFicha(j2.elegirMovimiento()));
      tablero.cambiarTurno();
      j2.actualizarSoluciones(tablero);
      system("clear");
      ImprimeTablero(tablero, mando);
      c = 1;
    }

    else
    {
      colocada = mando.actualizarJuego(c,tablero);
      system("clear");
      ImprimeTablero(tablero, mando);
      if (!colocada)
        c = getch();
    }

    // Comprobar si hay ganador
    quienGana = tablero.quienGana();
  }

  // Imprimir el tablero final
  c = 1;
  system("clear");
  mando.actualizarJuego(c, tablero);
  ImprimeTablero(tablero, mando);

  return tablero.quienGana();
}

int main(int argc, char **argv)
{
  int primerJugador, metrica, filas, cols;

  // Presentación y tamaño del tablero
  cout << "Bienvenido a Conecta4.\n";

  //TODO cambiar para que sean argumentos del programa (pág 7 guión.pdf)

  do
  {
    cout << "Introduce las filas: ";
    cin >> filas;
  } while (filas < 0);

  do
  {
    cout << "Introduce las columnas: ";
    cin >> cols;
  } while (cols < 0);

  // Elegir primer turno
  cout << "¿Quién empieza primero?:\n1.Tú.\n2.Jugador automático.\n";
  do {
    cout << "Elección: ";
    cin >> primerJugador;
  } while (primerJugador != 1 && primerJugador != 2);

  // Métrica
  metrica = stoi(argv[1]);

  // Jugar partida
  Tablero tablero(filas,cols);
  if (primerJugador == 2)
    tablero.cambiarTurno();
  int ganador = JugarPartida(tablero, metrica);

  // Mostrar ganador
  if (ganador == 0)
    cout << "\nSe ha producido un empate.\n";
  else
    cout << "\nHa ganado el jugador " << ganador << ".\n";
}

/* Fin fichero: conecta4.cpp */
