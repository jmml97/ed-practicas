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

//TODO Implementar métricas 1,2,3

int JugadorAuto::metrica1()
{
  //TODO implemntar
}

/* _________________________________________________________________________ */

int JugadorAuto::metrica2()
{
  //TODO implementar
}

/* _________________________________________________________________________ */

int JugadorAuto::metrica3()
{
  //TODO implementar
}

/* _________________________________________________________________________ */

int JugadorAuto::metrica4()
{
  int columnas = (partida.etiqueta(partida.raiz())).GetColumnas();
  return GeneraEnteroAleatorio(0, columnas - 1);
}

/* _________________________________________________________________________ */

JugadorAuto::JugadorAuto(const Tablero& inicial, int num_metrica)
  : partida(inicial), metrica(num_metrica)
{
  // Si elegimos la métrica aleatoria, inicializar semilla
  if (metrica == 4)
  {
    static bool seeded = false;
    if (!seeded)  // Solo inicializamos una vez por cada objeto
    {
      srand(time(NULL));
      seeded = true;
    }
  }
}

/* _________________________________________________________________________ */

int JugadorAuto::elegirMovimiento()
{
  int columna;

  switch (metrica) {
    case 2: columna = metrica2();
            break;
    case 3: columna = metrica3();
            break;
    case 4: columna = metrica4();
            break;
    //case 5: columna = metrica5();
              //break;
    default:
    case 1: columna = metrica1();
  }

  return columna;
}

/* _________________________________________________________________________ */

void JugadorAuto::actualizarSoluciones(const Tablero& actual)
{
  if (metrica != 4)
  {
    //TODO implementar: actualizar árbol según el tablero actual
  }
}

/* Fin fichero: jugador_auto.cpp */
