
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <stdio.h>
#include <unistd.h>
#include <termio.h>     // Linux/Windows users
//#include <termios.h>    // Mac OSX users

#include "ArbolGeneral.h"
#include "tablero.h"
#include "mando.h"

using namespace std;

/******************************************************************************/
/**
 * @brief Captura el caracter pulsado por teclado (sin necesidad de pulsar, a continuación, Enter).
 * @return: Caracter pulsado (char).
 */
char getch() {
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
        return (buf);
}

/******************************************************************************/
/**
 * @brief Imprime en pantalla el tablero completo, con el mando y el jugador.
 * @param t : Tablero que se va a imprimir.
 * @param m : Mando indicando la posición del jugador.
 */
void imprimeTablero(Tablero & t, Mando & m){
    cout << m.GetJugador() << endl;
    cout << t ;
    cout << m.GetBase() << endl;
    cout << m.GetMando() << endl;
}

/******************************************************************************/
/**
 * @brief Implementa el desarrollo de una partida de Conecta 4 sobre un tablero 5x7, pidiendo por teclado los movimientos de ambos jugadores según turno.
 * @return : Identificador (int) del jugador que gana la partida (1 o 2).
 */
int jugar_partida() {

    Tablero tablero(5, 7);      //Tablero 5x7
    Mando mando(tablero);       //Mando para controlar E/S de tablero
    char c = 1;
    int quienGana = tablero.quienGana();
    //mientras no haya ganador y no se pulse tecla de terminación
    while(c != Mando::KB_ESCAPE && quienGana == 0) {
        system("clear");
        mando.actualizarJuego(c, tablero);  // actualiza tablero según comando c 
        imprimeTablero(tablero, mando);     // muestra tablero y mando en pantalla
        quienGana = tablero.quienGana();    // hay ganador?
        if(quienGana==0) c = getch();       // Capturamos la tecla pulsada.    
    }

    return tablero.quienGana();
}

int main(int argc, char *argv[]){
    int ganador = jugar_partida();
    cout << "Ha ganado el jugador " << ganador << endl;
}  
  
  