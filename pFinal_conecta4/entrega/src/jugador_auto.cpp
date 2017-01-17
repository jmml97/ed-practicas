/**
 * @file jugador_auto.cpp
 * @brief Implementación de funciones del TDA JugadorAuto
 *
 */

#include <ctime>
#include <cstdlib>
#include "jugador_auto.h"

// Funciones auxiliares
namespace
{
  /**
   * Genera un entero aleatorio en el rango [min,max]
   */
  int GeneraEnteroAleatorio(int min, int max)
  {
    int tam = max - min + 1;
    return ((rand() % tam) + min);
  }
}

/* _________________________________________________________________________ */

int JugadorAuto::metrica1()
{
  int turno = partida.etiqueta(partida.raiz()).GetTurno();
  int num_cols = partida.etiqueta(partida.raiz()).GetColumnas();

  // Si se puede, inserto en el primer turno en el centro
  if (turno == 2 && partida.etiqueta(partida.raiz()).estaVacio()
      && num_cols % 2 != 0)
  {
    return num_cols / 2;
  }

  // TODO implementar
}

/* _________________________________________________________________________ */

int JugadorAuto::metrica2()
{
  int turno = partida.etiqueta(partida.raiz()).GetTurno();
  int num_cols = partida.etiqueta(partida.raiz()).GetColumnas();

  // Si se puede, inserto en el primer turno en el centro
  if (turno == 2 && partida.etiqueta(partida.raiz()).estaVacio()
      && num_cols % 2 != 0)
  {
    return num_cols / 2;
  }

  //TODO implementar
}

/* _________________________________________________________________________ */

int JugadorAuto::metrica3()
{
  // Explorar nivel 1
  for (ArbolGeneral<Tablero>::preorden_iterador it = ++(partida.beginpreorden());
       it != it; it = it.hermano())
  {
    // Si se gana con la jugada, elegimos esa
    if ((*it).quienGana() == 2)
      return (*it).GetUltCol();
  }

  // Explorar nivel 2
  for (ArbolGeneral<Tablero>::preorden_iterador nivel1 = ++(partida.beginpreorden());
        nivel1 != nivel1; nivel1 = nivel1.hermano())
  {
    bool no_gana = true;
    for (ArbolGeneral<Tablero>::preorden_iterador it = ++nivel1;
          it != it && no_gana; it = it.hermano())
    {
      if ((*it).quienGana() == 1)
        no_gana = false;
    }

    if (no_gana)
        return (*nivel1).GetUltCol();
  }

  // Caso trivial: el jugador automático pierde. Elegimos la primera columna
  return (*(++(partida.beginpreorden()))).GetUltCol();
}

/* _________________________________________________________________________ */

int JugadorAuto::metrica4()
{
  int columnas = (partida.etiqueta(partida.raiz())).GetColumnas();
  int col;
  do
  {
    col = GeneraEnteroAleatorio(0, columnas - 1);
  } while(!(partida.etiqueta(partida.raiz())).hayHueco(col));

  return col;
}

/* _________________________________________________________________________ */

void JugadorAuto::generarArbolSoluciones(int profundidad)
{
  //TODO implementar (recursivo?)
}

/* _________________________________________________________________________ */

void JugadorAuto::actualizarSoluciones(const Tablero& tablero)
{
  if (metrica != 4)
  {
    //TODO implementar:
    /*
     * 1. Podar ramas innecesarias (movimientos no realizados)
     * 2. raiz = raiz->hijo, donde hijo=movimiento_realizado
     * 3. Explorar un nivel siguiente al que estamos
     *
     * Restricciones para explorar:
     * - que no sea hoja
     * - ver si una columna está ya llena.
     *
     * //POSFIX método a parte para generar los tableros??
     */
  }
}

/* _________________________________________________________________________ */

//TODO tener en cuenta el jugador al que le toca el primer turno????
JugadorAuto::JugadorAuto(const Tablero& inicial, int num_metrica)
  : partida(inicial), metrica(num_metrica)
{
  // Métricas que exploran hasta profundidad N
  if (metrica != 4)
  {
    int profundidad = metrica == 3 ? 2 : N;
    generarArbolSoluciones(profundidad);
  }
}

/* _________________________________________________________________________ */

int JugadorAuto::elegirMovimiento(int num_metrica)
{
  int columna;

  // Usar dato miembro 'metrica'
  if (num_metrica == 0)
    num_metrica = metrica;

  switch (num_metrica) {
    case 2: columna = metrica2();
            break;
    case 3: columna = metrica3();
            break;
    case 4: columna = metrica4();
            break;
    default:
    case 1: columna = metrica1();
  }

  return columna;
}

void JugadorAuto::turnoAutomatico(Tablero& actual)
{
  int columna;

  // Actualizamos espacio de soluciones
  actualizarSoluciones(actual);

  // Elegimos jugada según la métrica
  columna = elegirMovimiento();

  // Insertamos ficha
  actual.colocarFicha(columna);

  // Cambiamos el turno
  actual.cambiarTurno();

  // Actualizamos de nuevo espacio de soluciones
  actualizarSoluciones(actual);
}

/* Fin fichero: jugador_auto.cpp */
