/**
 * @file conecta4.cpp
 * @brief Implementa una partida del juego Conecta 4
 *
 * Este programa simula una partida del juego Conecta 4 en un tablero
 * de tamaño variable. Se trata de un juego de un único jugador, pues
 * se juega contra un jugador automático.
 *
 * El programa recibe como argumento el identificador del jugador que
 * iniciará la partida:
 *
 *   - 1. El jugador humano comienza.
 *   - 2. EL jugador automático comienza.
 *
 * Si no se proporciona ningún argumento, la partida la iniciará el
 * jugador definido por defecto.
 *
 * Además, también se pregunta por la entrada estándar el tamaño del
 * tablero deseado.
 */

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <stdio.h>
#include <unistd.h>
#include "tablero.h"
#include "mando.h"

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
 *        tamaño variable, pidiendo por teclado los movimientos de ambos jugadores
 *        según el turno.
 * @param primerJugador Jugador que empieza la partida.
 * @param f Número de filas del tablero
 * @param c Número de columnas del tablero
 * @return Identificador (int) del jugador que gana la partida (1 o 2), o 0 en
 *         caso de empate o partida sin finalizar.
 */
int JugarPartida(int primerJugador, int filas, int cols)
{
  Tablero tablero(filas, cols);
  Mando mando(tablero);
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
      ImprimeTablero(tablero, mando);
      if (!colocada)
        c = getch();
      else
        juegaIA = true;
    }

    // Comprobar si hay ganador
    quienGana = tablero.quienGana();
  }

  // Imprimer el tablero final
  c = 1;
  system("clear");
  mando.actualizarJuego(c, tablero);
  ImprimeTablero(tablero, mando);

  return tablero.quienGana();
}

/// Jugador que empieza la partida por defecto
const int PRIMER_JUGADOR_DEFAULT = 1;

int main(int argc, char **argv)
{
  int primerJugador, filas, cols;

  // Presentación y tamaño del tablero
  cout << "Bienvenido a Conecta4.\n";

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
  if (argc < 2)
  {
    primerJugador = PRIMER_JUGADOR_DEFAULT;
  }
  else
  {
    cout << "¿Quién empieza primero?:\n1.Tú.\n2.IA\n";
    do {
      cout << "Elección: ";
      cin >> primerJugador;
    } while(primerJugador != 1 && primerJugador != 2);
  }

  // Jugar partida
  int ganador = JugarPartida(primerJugador, filas, cols);

  // Mostrar ganador
  if (ganador == 0)
    cout << "\nSe ha producido un empate.\n";
  else
    cout << "\nHa ganado el jugador " << ganador << ".\n";
}

/* Fin fichero: conecta4.cpp */
