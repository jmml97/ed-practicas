/**
 * @file conecta4.cpp
 * @brief Implementa una partida del juego Conecta 4
 *
 * Este programa simula una partida del juego Conecta 4 en un tablero
 * de tamaño variable, ya sea entre dos jugadores humanos, o entre
 * un jugador humano y un jugador automático.
 *
 * Para ver la lista de argumentos que admite, ejecutar el programa
 * con el modificador -h para ver la ayuda.
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
  JugadorAuto j2;
  char c = 1;
  int quienGana = 0;
  bool colocada;

  // Inicializar jugador automático
  if (metrica != 0)
    j2 = JugadorAuto(tablero, metrica);

  // Mientras el tablero no esté lleno ni haya ganador
  while (c != Mando::KB_ESCAPE && !tablero.estaLleno() && quienGana == 0)
  {
    if (metrica != 0 && tablero.GetTurno() == 2)
    {
      j2.turnoAutomatico(tablero);
      system("clear");
      ImprimeTablero(tablero, mando);
      c = 1;
    }

    else
    {
      system("clear");
      colocada = mando.actualizarJuego(c,tablero);
      ImprimeTablero(tablero, mando);
      if (!colocada || metrica == 0)
        c = getch();
      else
        c = 1;
    }

    // Comprobar si hay ganador
    quienGana = tablero.quienGana();
  }

  // Imprimir el tablero final
  c = 1;
  system("clear");
  mando.actualizarJuego(c, tablero);
  ImprimeTablero(tablero, mando);

  return quienGana;
}

int main(int argc, char **argv)
{
  int primerJugador = 1, metrica = 1, filas = 4, cols = 4;
  bool opc_ayuda = false;

  // Argumentos del programa
  if (argc > 9) {
    cout << "Error en los argumentos, utiliza -h para ver la ayuda." << endl;
    return 1;
  }

  for (int i = 1; i < argc; i++)
  {
    if (string(argv[i]) == "-f")
    {
      if (i + 1 < argc)
	      filas = stoi(argv[i+1]);
    }
    else if (string(argv[i]) == "-c")
    {
      if (i + 1 < argc)
	      cols  = stoi(argv[i+1]);
    }
    else if (string(argv[i]) == "-m")
    {
      if (i + 1 < argc)
	      metrica  = stoi(argv[i+1]);
    }
    else if (string(argv[i]) == "-t")
    {
      if (i + 1 < argc)
	      primerJugador = stoi(argv[i+1]);
    }
    else if (string(argv[i]) == "-h")
    {
	    opc_ayuda = true;
    }
  }

  if (opc_ayuda)
  {
    cout << "uso: conecta4 [-f número] [-c número] [-m número] [-t número]" << endl;
    cout << "f : especifica el número de filas" << endl;
    cout << "c : especifica el número de columnas" << endl;
    cout << "m : especifica la métrica a utilizar (0 para jugar sin IA, 1 la más eficiente)" << endl;
    cout << "t : especifica qué jugador tiene el primer turno (1, 2)" << endl;
    return 0;
  }

  // Jugar partida
  Tablero tablero(filas, cols);
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
