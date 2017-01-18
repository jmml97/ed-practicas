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
  for (ArbolGeneral<Tablero>::Nodo n = partida.hijomasizquierda(partida.raiz());
      n; n = partida.hermanoderecha(n))
  {
    if (partida.etiqueta(n).quienGana() == 2)
      return partida.etiqueta(n).GetUltCol();
  }

  /*
  // Explorar nivel 1
  for (ArbolGeneral<Tablero>::preorden_iterador it = ++(partida.beginpreorden());
       it != it; it = it.hermano())
  {
    // Si se gana con la jugada, elegimos esa
    if ((*it).quienGana() == 2)
      return (*it).GetUltCol();
  }
*/
  for (ArbolGeneral<Tablero>::Nodo n1 = partida.hijomasizquierda(partida.raiz());
      n1; n1 = partida.hermanoderecha(n1))
  {
    bool no_gana = true;
    for (ArbolGeneral<Tablero>::Nodo n2 = partida.hijomasizquierda(n1);
          n2; n2 = partida.hermanoderecha(n2))
    {
      if (partida.etiqueta(n2).quienGana() == 1)
        no_gana = false;
    }

    if (no_gana)
      return partida.etiqueta(n1).GetUltCol();
  }

  return partida.etiqueta(partida.hijomasizquierda(partida.raiz())).GetUltCol();
}
/*
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
}*/

/* _________________________________________________________________________ */

int JugadorAuto::metrica4()
{
  int columnas = (partida.etiqueta(partida.raiz())).GetColumnas();
  int col;
  do
  {
    col = GeneraEnteroAleatorio(0, columnas - 1);
  } while((partida.etiqueta(partida.raiz())).hayHueco(col) < 0);

  return col;
}

/* _________________________________________________________________________ */

void JugadorAuto::generarHijos(ArbolGeneral<Tablero>& padre, int profundidad)
{
  if (profundidad)
  {
    Tablero original = padre.etiqueta(padre.raiz());
    int num_cols = original.GetColumnas();

    for (int col = 0; col < num_cols; ++col)
    {
      if ((original.hayHueco(col) > -1) && !original.quienGana())
      {
        Tablero nuevo(original);
        nuevo.colocarFicha(col);
        nuevo.cambiarTurno();
        ArbolGeneral<Tablero> hijo(nuevo);
        generarHijos(hijo, profundidad - 1);
        padre.insertar_hijomasizquierda(padre.raiz(), hijo);
      }
    }
  }
}

// TODO: forma1 (muy parecida a la recurisva - se puede fusionar con ella ??)
// funciona solo poniendo al padre, que en realidad es la hoja original
void JugadorAuto::funcion1(ArbolGeneral<Tablero>::Nodo padre, int profundidad)
{
  if (profundidad)
  {
    Tablero original = partida.etiqueta(padre);
    int num_cols = original.GetColumnas();

    for (int col = 0; col < num_cols; ++col)
    {
      if ((original.hayHueco(col) > -1) && !original.quienGana())
      {
        Tablero nuevo(original);
        nuevo.colocarFicha(col);
        nuevo.cambiarTurno();
        ArbolGeneral<Tablero> hijo(nuevo);
        generarHijos(hijo, profundidad - 1);
        partida.insertar_hijomasizquierda(padre, hijo);
      }
    }
  }
}

// TODO: forma2 (muy tonto el podar e insertar en el árbol ?)
// funciona con el padre de la hoja, que rellena todos sus hermanos también
/*
void JugadorAuto::funcion2(Nodo padre, int profundidad)
{
  Nodo hijo = padre.hijomasizquierda();

  if (hijo)
  {
    ArbolGeneral<Tablero> nuevo(tablero.etiqueta(hijo));
    generarHijos(nuevo, profundidad);
    ArbolGeneral<Tablero> aux;
    partida.podar_hijomasizquierda(padre, aux);
    partida.insertar_hijomasizquierda(padre, nuevo);

    Nodo hermano = hijo.hermanoderecha();

    while (hermano)
    {
      ArbolGeneral<Tablero> nuevo(tablero.etiqueta(hermano));
      generarHijos(nuevo, profundidad);
      ArbolGeneral<Tablero> aux;
      partida.podar_hermanoderecha(hijo, aux);
      partida.insertar_hermanoderecha(hijo, nuevo);

      hijo = hermano;
      hermano = hijo.hermanoderecha();
    }
  }
  else
    // Si solo está la raiz (sin hijos)
    generarHijos(partida, profundidad);


}*/

void JugadorAuto::generarArbolSoluciones(int profundidad)
{
  ArbolGeneral<Tablero>::Nodo n = partida.raiz();
  while (n)
  {
    if (partida.hijomasizquierda(n))
    {
      n = partida.hijomasizquierda(n);
    }
    else if(partida.hermanoderecha(n))
    {
      funcion1(n, profundidad);
      n = partida.hermanoderecha(n);
    }
    else
    {
        funcion1(n, profundidad);
        while((partida.padre(n)) && (partida.hermanoderecha(partida.padre(n)) == 0))
            n = partida.padre(n);
        if (partida.padre(n) == 0)
            n = 0;
        else
            n = partida.hermanoderecha(partida.padre(n));
    }
  }
}
/*
void JugadorAuto::generarArbolSoluciones(ArbolGeneral<Tablero>& padre,
                                         int prof, int prof_max)
{
  //TODO: rehacer. Falla porque llamamos en la recursividad con un objeto local (hijo)
  // y la función espera una referencia.
  if (prof < prof_max)
  {
    int num_cols = partida.etiqueta(partida.raiz()).GetColumnas();
    Tablero original = padre.etiqueta(padre.raiz());
    ArbolGeneral<Tablero> hijo;
    for (int col = 0; col < num_cols; col++)
    {
      if (original.hayHueco(col) && !original.quienGana())
      {
        Tablero nuevo(original);
        nuevo.colocarFicha(col);
        nuevo.cambiarTurno();
        hijo = ArbolGeneral<Tablero>(nuevo);
        generarArbolSoluciones(hijo, prof + 1, prof_max);
        padre.insertar_hijomasizquierda(padre.raiz(), hijo);
      }
    }
  }
}*/

/* _________________________________________________________________________ */

void JugadorAuto::actualizarSoluciones(const Tablero& tablero)
{
  if (metrica != 4)
  {
    // Localizar tablero actual entre las posibilidades (siempre está)
    ArbolGeneral<Tablero>::Nodo n = partida.hijomasizquierda(partida.raiz());
    while (partida.etiqueta(n).GetUltCol() != tablero.GetUltCol())
    {
      n = partida.hermanoderecha(n);
    }

    // Asignar subárbol que cuelga de n a partida
    ArbolGeneral<Tablero> nuevo;
    ArbolGeneral<Tablero>::Nodo aux = partida.raiz();
    if (partida.hijomasizquierda(aux) == n)
      partida.podar_hijomasizquierda(aux, nuevo);
    else
    {
      aux = partida.hijomasizquierda(aux);
      while (partida.hermanoderecha(aux) != n)
        aux = partida.hermanoderecha(aux);
      partida.podar_hermanoderecha(aux, nuevo);
    }
    partida.AsignaRaiz(nuevo.etiqueta(nuevo.raiz()));
    while (nuevo.hijomasizquierda(nuevo.raiz()))
    {
      ArbolGeneral<Tablero> arbol;
      nuevo.podar_hijomasizquierda(nuevo.raiz(), arbol);
      partida.insertar_hijomasizquierda(partida.raiz(), arbol);
    }

    generarArbolSoluciones(1);
  }
  else
  {
    partida = tablero;
  }
}

/* _________________________________________________________________________ */

JugadorAuto::JugadorAuto(const Tablero& inicial, int num_metrica)
  : partida(inicial), metrica(num_metrica)
{
  // Métricas que exploran hasta una cierta profundidad (excepto aleatoria)
  if (metrica != 4)
  {
    int num_niveles = ((metrica == 3) ? 2 : N);
    generarArbolSoluciones(num_niveles);
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
