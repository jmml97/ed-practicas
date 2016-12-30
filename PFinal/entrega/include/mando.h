#ifndef __MANDO_H__
#define __MANDO_H__

#include "tablero.h"


/******************************************************************************/
/**
 * @brief TDA Mando.
 * 
 * Este TDA sirve para representar la parte gráfica del juego.
 */
class Mando{
private:
    string mando;       ///< Señala dónde está colocado el jugador. Representada con '^'
    string jugador;     ///< Indica la ficha del jugador.
    string base;        ///< Base del tablero.
    int posicion;       ///< Indica la posición actual en la que está el jugador.
public:
    // Controles.
    const static char KB_LEFT = 'a';
    const static char KB_RIGHT = 'd';
    const static char KB_SPACE = ' ';
    const static char KB_ESCAPE = 27;

    /**
     * @brief Constructor. Inicializa las variables dado un tablero. 
     *      No se puede generar una Mando sin un tablero. Para que no cause
     *      problemas de incongruencias de tamaño.
     * @param t : Tablero sobre el que se va a inicialiar la parte gráfica.
     *      El mando, el indicador de la ficha del jugador y la base del 
     *      tablero.
     */
    Mando(Tablero t);

    /**
     * @brief Actualiza el tablero del juego: la posición del jugador y si se 
     *      ha introducido alguna pieza en el tablero.
     *      Esta función es la encargada de controlar la entrada del teclado.
     * @param c : Caracter leído por el teclado.
     * @param t : Tablero. Si el caracter leido es el de colocar ficha y hay hueco
     *      modifica el tablero.
     * @return Devuelve true si se ha colocado una ficha en la actualización del 
     *      juego. 
     */
    bool actualizarJuego(char c, Tablero & t);
    
    /**
     * @brief Representación gráfica de la base.
     * @return Devuelve una cadena representado la base del tablero.
     */
    string GetBase() const {
        return base;
    }
    /**
     * @brief Representación gráfica del jugador. 
     * @return Devuelve una cadena representado del jugador.
     */
    string GetJugador() const {
        return jugador;
    }
    /**
     * @brief Representación gráfica del mando.
     * @return Devuelve la representación gráfica del mando.
     */
    string GetMando() const {
        return mando;
    }

};


#endif