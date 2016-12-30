#ifndef __TABLERO_H__
#define __TABLERO_H__

#include <vector>
#include <iostream>

using namespace std;


/**
 * @brief Imprime un conjunto de tipo T sobre el flujo de salida. 
 * @param s: Flujo de salida. 
 * @param c: Conjunto con los elementos a imprimir.
 * @return Devuelve el flujo de salida.
 **/
template <class T>
ostream & operator<<(ostream & s, const vector<T> & c){

  typename vector<T>::const_iterator i;
  
  for (i=c.begin(); i != c.end(); i++)
        if((*i) == 0)
            s << "  ";
      else if((*i) == 1)
         s << "x ";
       else if((*i) == 2)
           s << "o "; 
      else
         s << " ";
  return s;
}
/**
 * @brief Imprime una matriz de tipo T sobre el flujo de salida.
 * @param s: Flujo de salida.
 * @param c: Vector de vectores (matriz) de tipo T a imprimir. 
 * @return Devuelve el flujo de salida.
 */
template <class T>
ostream & operator<<(ostream & s, const vector<vector<T> > & c){

  typename vector<vector<T> >::const_iterator i;
  s << '\n';    // para que al recorrer en el arbol no bailen las filas
  for (i=c.begin(); i != c.end(); i++)
      s << "|"<< (*i) << "|\n";
  return s;
}


/******************************************************************************/
/**
 * @brief T.D.A. Tablero.
 * 
 */
class Tablero{
private:
    vector<vector<int> > tablero; ///< Matriz que representa un estado del juego. 
    const int filas;              ///< Número de filas que tiene el tablero.
    const int columnas;           ///< Número de columnas que tiene el tablero.
    int turno;                    ///< Indica a qué jugador le toca poner ficha. 1 para el jugador 1, 2 para el jugador 2.

    void reserve();               ///< Crea el tablero de tamaño filas/columnas

public:
    const static int N_FICHAS_GANAR = 4;

    /**
     * @brief Constructor por defecto. Crea un tablero de tamaño predefinido.
     * 
     */
    Tablero();
    /**
     * @brief Constructor. Crea un tablero introduciendo el tamaño del mismo.
     *      El estado inicial del tablero es todo 0, es decir, todo el tablero
     *      está libre. El turno inicial es el del jugador 1.
     * @param filas : Número de filas que tendrá el tablero.
     * @param columnas : Nümero de columnas del tablero.
     */
    Tablero(const int filas, const int columnas);
    /**
     * @brief Constructor de copia. Crea un tablero a partir de otro dado.
     * @param t : Tablero origen que se va a copiar.
     */
    Tablero(const Tablero& t);
    ~Tablero();
    /**
     * @brief Comprueba si hay hueco en una columna 'pos'.
     * @param pos : Columna sobre la que se va a comprobar si hay hueco para introducir
     *              una ficha. 
     * @return Devuelve la fila en la que hay hueco (en esa columna). 
     *      Si no hay hueco devuelve -1.
     */
    int hayHueco(int pos);
    /**
     * @brief Coloca una ficha en la columna especificada del jugador correspondiente.
     *          Si le toca al jugador 1, inserta la ficha en esa posición. 
     *          (Si hay hueco)
     * @param pos : Columna en la que se va a intentar colocar la ficha.
     * @return Devuelve true si se ha introducido la ficha en la posición.
     *          False en otro caso.
     */
    bool colocarFicha(int pos);
    /**
     * @brief Cambia el turno del jugador que toca. 
     * @return Devuelve el turno que toca.
     */
    int cambiarTurno();

    
    //-------------------------------------------------------------------------- 
    /**
     * @brief Devuelve la anchura del tablero.
     * @return Número de columnas del tablero (anchura).
     */
    const int GetColumnas() const { return columnas; }

    /**
     * @brief Devuelve la altura del tablero.
     * @return Número de filas del tablero (altura).
     */
    const int GetFilas() const { return filas; }
    
    /**
     * @brief Función que devuelve el atributo tablero.
     * @return Devuelve un vector de vectores de enteros (una matriz) de enteros
     *      representando un tablero.
     */
    vector<vector<int> > GetTablero() const { return tablero; }

    /**
     * @brief Asigna un tablero introducido como parámetro.
     * @param tablero : Matriz (vector de vectores de enteros) representante de 
     *      un estado del juego.
     */
    void SetTablero(vector<vector<int> > tablero);
    /**
     * @brief Turno del estado actual.
     * @return Devuelve el turno del jugador. {1, 2}
     */
    int GetTurno() { return turno; } 
    
    /**
     * @brief Operador de igualdad. Asigna los valores del tablero de la derecha
     *      al de la izquierda.
     * @param derecha : Tablero origen que se va a copiar.
     * @return Devuelve la referencia al tablero destino que se ha copiado.
     */
    Tablero& operator=(const Tablero& derecha);

    /**
     * @brief Operador flujo de salida. Imprime el tablero por el flujo de salida.
     * @param os : Flujo de salida.
     * @param t : Tablero que se va a imprimir.
     */
    friend ostream& operator<<(ostream& os, const Tablero& t);
    /**
     * @brief Función que calcula en un estado concreto del tablero, quién gana.
     *      En cualquier estado del tablero, se puede decidir por el estado del
     *      juego: gana el jugador 1, empate o gana el jugador 2.
     * @return Devuelve {0, 1, 2} 0 si no ha ganado nadie. 1 si ha ganado el 
     *      jugador 1 y 2 si ha ganado el jugador 2.
     */
    int quienGana();

};

#endif