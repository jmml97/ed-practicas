/**
 * @file test_arbol_tablero.cpp
 * @brief Fichero de pruebas para el TDA Tablero y el TDA ArbolGeneral
 *
 */

#include <iostream>
#include <string>
#include "arbol_general.h"
#include "tablero.h"

using namespace std;

int main(int argc, char **argv)
{
  //Tablero vacío 6x7
  Tablero tablero(6, 7);

  //Manualmente se insertan algunos movimientos:
  tablero.colocarFicha(3);	//Jugador 1 inserta ficha en columna 3
  tablero.cambiarTurno();
  tablero.colocarFicha(1);	//Jugador 2 inserta ficha en columna 1
  tablero.cambiarTurno();
  tablero.colocarFicha(3);	//Jugador 1 inserta ficha en columna 3.
  tablero.cambiarTurno();

  //Se muestra el tablero
  cout << "Tablero obtenido tras tres movimientos:\n" << tablero;

  //A partir de la situación actual del tablero, montamos un árbol para estudiar algunas posibilidades.

  // Éste es el árbol que queremos montar:
  // 				  tablero
  //					   |
  //			|-------------|
  //	 tablero1		   tablero2
  //							      |
  //						     tablero3

  //Árbol 'partida', con 'tablero' como nodo raíz
  ArbolGeneral<Tablero> partida(tablero);

  //Estudio opciones a partir de tablero: Jugador 2 coloca ficha en columna 1. (tablero1)
  Tablero tablero1(tablero);					//tablero queda sin modificar
  tablero1.colocarFicha(1);
  ArbolGeneral<Tablero> arbol1 (tablero1);	//creo árbol con un nodo (tablero1)

  //Otra opción: Jugador 2 coloca ficha en columna 2. (tablero2)
  Tablero tablero2(tablero);					//tablero queda sin modificar
  tablero2.colocarFicha(2);
  ArbolGeneral<Tablero> arbol2(tablero2);		//creo árbol con un nodo

  // Sobre la última opción, ahora contemplo la posibilidad de que
  // 	Jugador 1 coloque ficha también en columna 2.
  tablero2.cambiarTurno();					//modifico tablero2 (esta modificación sería tablero3)
  tablero2.colocarFicha(2);
  ArbolGeneral<Tablero> arbol3(tablero2);	//creo árbol con un nodo
  arbol2.insertar_hijomasizquierda(arbol2.raiz(), arbol3);	//añado este árbol como hijo de arbol2

  // Inserto arbol1 y arbol2 como hijos de partida.
  // arbol1 es el hijo más a la izquierda y arbol2 es hermano a la derecha de arbol1

	//	Forma de hacerlo A: inserto varios hijomasizquierda en el orden inverso al deseado
	//	partida.insertar_hijomasizquierda(partida.raiz(), arbol2);
	//  partida.insertar_hijomasizquierda(partida.raiz(), arbol1); //  hijomasizquierda desplaza al anterior a la derecha

	// Forma de hacerlo B: inserto un hijomasizquierda y hermanoderecha
	partida.insertar_hijomasizquierda(partida.raiz(), arbol1);							//inserto un hijomasizquierda
	partida.insertar_hermanoderecha(partida.hijomasizquierda(partida.raiz()), arbol2);	//le inserto un hermanoderecha

  // Recorremos en preorden para comprobar el arbol 'partida' resultante
  cout << "\nÁrbol en preorden:\n" << endl;
  partida.recorrer_preorden();

	// Podamos el hijomasizquierda y recorremos en preorden:
  ArbolGeneral<Tablero> rama_podada;
  partida.podar_hermanoderecha(partida.hijomasizquierda(partida.raiz()), rama_podada);

	cout << "\nRecorrido preorden después de podar arbol2: \n" << endl;
  partida.recorrer_preorden();

  cout << "\nRecorrido preorden de la rama podada: \n" << endl;
  rama_podada.recorrer_preorden();

  // Probamos ArbolGeneral::asignar_subarbol. Asignamos a partida la rama_podada:
  partida.asignar_subarbol(rama_podada, rama_podada.raiz());
  cout << "\nRecorrido preorden después de asignar a la raiz la rama_podada: \n" << endl;
  partida.recorrer_preorden();

  cout << "\nRecorrido postorden después de asignar a la raiz la rama_podada: \n" << endl;
  partida.recorrer_postorden();

  return 0;
}

/* Fin fichero: test_arbol_tablero.cpp */
