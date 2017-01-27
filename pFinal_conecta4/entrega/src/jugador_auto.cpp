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

  /**
   * @brief Devuelve cuántas alineaciones de nRaya fichas hay en un tablero
   * dado, para el último jugador que insertó ficha.
   * @param tab Tablero donde buscar las alineaciones
   * @param nRaya Número de fichas en línea a buscar
   */
  int cantidadAlineada(const Tablero& tab, int nRaya)
  {
    // Estructura para representar una dirección
    struct Direccion
    {
      int i;
      int j;
    };

    // Almaceno las 8 direcciones posibles
    Direccion direccion[8] = {{-1,-1},{-1, 0},{-1, 1},{0, -1},{0, 1},{1, -1},{1, 0},{1, 1}};
    // Nº de n-lineas encontradas (-1 si ha habido fallos)
    int encontrados = -1;

    if (!tab.estaVacio())
    {
      encontrados = 0;
      int col = tab.GetUltCol();
      int fil;

      // Bajamos hasta llegar a la fila donde se insertó la última ficha
      for (fil = 0; tab.GetElemento(fil,col) == 0; ++fil);

      // Cogemos la ficha para buscar las alineaciones n-raya
      int ficha = tab.GetElemento(fil,col);

      // Recorro cada dirección, si hay n en línea suma 1 al nº de n-lineas que se han dado al poner la ficha en ult_pos
      for (int d = 0; d < 8; d++)
      {
        // La propia ficha cuenta como una ficha alineada
        int alineados = 1;
        bool sigue = true;
        // Fijo la i,j de la última posición
        int i = fil;
        int j = col;
        while (sigue && alineados < nRaya)
        {
          //  Me muevo en la direccion que me dan
          i += direccion[d].i;
          j += direccion[d].j;
          sigue = i >= 0 && i < tab.GetFilas() && j >= 0 && j < tab.GetColumnas()
                  && ficha == tab.GetElemento(i, j);
          if (sigue)
            alineados++;
          }
          if (alineados == nRaya)
            encontrados++;
        }
    }

    return encontrados;
  }
}

/* _________________________________________________________________________ */

int JugadorAuto::metrica1()
{
  int num_cols = partida.etiqueta(partida.raiz()).GetColumnas();

  // Si se puede, insertar en el primer turno en el centro
  if (partida.etiqueta(partida.raiz()).estaVacio())
  {
    return num_cols / 2;
  }

  // Ganar la partida, si es posble
  int gana_IA = gana_inmediato();
  if (gana_IA != -1)
    return gana_IA;

  // Evitar perder, si es posible
  vector<ArbolGeneral<Tablero>::Nodo> posibilidades = evita_perder();
  int num_nodos = posibilidades.size();

  if (num_nodos)
  {
    int max_alineadas = 0;
    int nodo_max = 0;
    int alineadas;
    bool humano_alinea;
    int i;

    // Ver si puedo conseguir el mayor número de 3-en-raya
    for (i = 0; i < num_nodos; i++)
    {
      alineadas = cantidadAlineada(partida.etiqueta(posibilidades[i]), 3);
      if (alineadas > max_alineadas)
      {
        max_alineadas = alineadas;
        nodo_max = i;
      }
    }
    if (max_alineadas > 0)
      return partida.etiqueta(posibilidades[nodo_max]).GetUltCol();

    // Ver si puedo evitar que el jugador humano consiga 3-en-raya
    for (vector<ArbolGeneral<Tablero>::Nodo>::iterator it = posibilidades.begin();
         it != posibilidades.end(); ++it)
    {
      humano_alinea = false;
      for (ArbolGeneral<Tablero>::Nodo n = partida.hijomasizquierda(*it);
           n && !humano_alinea; n = partida.hermanoderecha(n))
      {
        if (cantidadAlineada(partida.etiqueta(*it), 3) > 0)
          humano_alinea = true;
      }
      // Si hemos provocado que el humano alinee 3, eliminamos esa posibilidad
      if (humano_alinea)
        posibilidades.erase(it);
    }

    // Ver si puedo conseguir el mayor número de 2-en-raya
    for (i = 0; i < num_nodos; i++)
    {
      alineadas = cantidadAlineada(partida.etiqueta(posibilidades[i]), 2);
      if (alineadas > max_alineadas)
      {
        max_alineadas = alineadas;
        nodo_max = i;
      }
    }
    if (max_alineadas > 0)
      return partida.etiqueta(posibilidades[nodo_max]).GetUltCol();

    // Ver si puedo evitar que el jugador humano consiga 2-en-raya
    for (vector<ArbolGeneral<Tablero>::Nodo>::iterator it = posibilidades.begin();
         it != posibilidades.end(); ++it)
    {
      humano_alinea = false;
      for (ArbolGeneral<Tablero>::Nodo n = partida.hijomasizquierda(*it);
           n && !humano_alinea; n = partida.hermanoderecha(n))
      {
        if (cantidadAlineada(partida.etiqueta(*it), 2) > 0)
          humano_alinea = true;
      }
      // Si hemos provocado que el humano alinee 2, eliminamos esa posibilidad
      if (humano_alinea)
        posibilidades.erase(it);
    }

    // De las posibilidades restantes, insertar en la columna de mayor puntuación
    return mayorPuntuacion(posibilidades);
  }

  // El jugador automático pierde, elegimos la primera columna libre
  else
  {
    return partida.etiqueta(partida.hijomasizquierda(partida.raiz())).GetUltCol();
  }
}

/* _________________________________________________________________________ */

int JugadorAuto::metrica2()
{
  int num_cols = partida.etiqueta(partida.raiz()).GetColumnas();

  // Si se puede, inserto en el primer turno en el centro (o lo más cerca posible)
  if (partida.etiqueta(partida.raiz()).estaVacio())
  {
    return num_cols / 2;
  }

  // Ganar la partida si es posble
  int gana_IA = gana_inmediato();
  if (gana_IA != -1)
    return gana_IA;

  // Evitar perder, si es posible
  vector<ArbolGeneral<Tablero>::Nodo> posibilidades = evita_perder();

  // Calculamos de entre las posibilidades aquella con mayor puntuación
  if (posibilidades.size())
  {
    return mayorPuntuacion(posibilidades);
  }

  // El jugador automático pierde, elegimos la primera columna libre
  else
  {
    return partida.etiqueta(partida.hijomasizquierda(partida.raiz())).GetUltCol();
  }
}

/* _________________________________________________________________________ */

int JugadorAuto::metrica3()
{
  // Ganar la partida si es posble
  int gana_IA = gana_inmediato();
  if (gana_IA != -1)
    return gana_IA;

  // Evitar perder, si es posible
  vector<ArbolGeneral<Tablero>::Nodo> posibilidades = evita_perder();

  if (posibilidades.size())
  {
    // Introducimos aleatoriamente donde el jugador humano no gane
    return partida.etiqueta(posibilidades[GeneraEnteroAleatorio(0, posibilidades.size() - 1)]).GetUltCol();
  }

  else
  {
    // Caso trivial: el jugador automático pierde. Elegimos la primera columna libre
    return partida.etiqueta(partida.hijomasizquierda(partida.raiz())).GetUltCol();
  }
}

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

void JugadorAuto::generarArbolSoluciones(int profundidad)
{
  ArbolGeneral<Tablero>::Nodo raiz = partida.raiz();
  ArbolGeneral<Tablero>::Nodo n = raiz;

  // Bajar hasta el hijo más a la izquierda
  while (partida.hijomasizquierda(n))
    n = partida.hijomasizquierda(n);

  do
  {
    ArbolGeneral<Tablero>::Nodo hoja = n;

    // Nivel relativo al primero
    int i = 0;
    do
    {
      bool creado = true;

      // Crear los hijos del nodo
      while (i < profundidad && creado)
      {
        creado = false;
        Tablero tablero_original(partida.etiqueta(n));
        int num_cols = tablero_original.GetColumnas();

        // Generar todos los tableros posibles
        for (int col = 0; col < num_cols; ++col)
        {
          if ((tablero_original.hayHueco(col) > -1) && !tablero_original.quienGana())
          {
            // Crear tablero, meter ficha, cambiar turno e insertar
            creado = true;
            Tablero tablero_nuevo(tablero_original);
            tablero_nuevo.colocarFicha(col);
            tablero_nuevo.cambiarTurno();
            ArbolGeneral<Tablero> hijo(tablero_nuevo);
            partida.insertar_hijomasizquierda(n, hijo);
          }
        }
        ++i;  // Aumentar el nivel

        // Si ya no hay más que crear
        if (i < profundidad && creado)
          n = partida.hijomasizquierda(n);

      }
      --i;  // Subimos un nivel

      // Nivel profundidad - 1: mirar si hay hermano derecha
      if (n != hoja && partida.hermanoderecha(n))
      {
        n = partida.hermanoderecha(n);
      }
      else
      {
        // Subir hasta que haya hermano derecha o lleguemos a la hoja original
        while (n != hoja && !partida.hermanoderecha(partida.padre(n)))
        {
          --i;  // Disminuye el nivel
          n = partida.padre(n);
        }

        // Si no he llegado al tope
        if (n != hoja)
        {
          // Nos posicionamos en el hermano a la derecha del padre
          n = partida.hermanoderecha(partida.padre(n));
          --i;  // Disminuye el nivel (porque subimos al padre)
        }
      }
    } while (n != hoja);  // Mientras que no llegue a la hoja original

    // Mirar hermanos a la derecha de la hoja original
    if (partida.hermanoderecha(n))
    {
      n = partida.hermanoderecha(n);
      // Bajar hasta el hijo más a la izquierda de todos
      while (partida.hijomasizquierda(n))
        n = partida.hijomasizquierda(n);
    }

    // No hay hermanos a la derecha de la hoja
    else
    {
      // Subir mientras que no llegue a la raíz y no haya hermanos a la derecha
      while (n != raiz && !partida.hermanoderecha(partida.padre(n)))
        n = partida.padre(n);

      // Si no he llegado al tope
      if (n != raiz)
      {
        // Me posiciono en el hermano a la derecha del padre
        n = partida.hermanoderecha(partida.padre(n));
        // Bajo hasta el hijo más a la izquierda de todos
        while (partida.hijomasizquierda(n))
          n = partida.hijomasizquierda(n);
      }
    }
  } while (n != raiz);  // Mientras que no llegue a la raíz
}

/* _________________________________________________________________________ */

void JugadorAuto::actualizarSoluciones(const Tablero& tablero)
{
  // Si comienza jugando el jugador automático, no hacemos nada
  if (tablero.estaVacio())
    return;

  if (metrica != 4)
  {
    // Localizar tablero actual entre las posibilidades (siempre está)
    ArbolGeneral<Tablero>::Nodo n = partida.hijomasizquierda(partida.raiz());
    while (partida.etiqueta(n).GetUltCol() != tablero.GetUltCol())
    {
      n = partida.hermanoderecha(n);
    }

    // El nodo n, y el subárbol que cuelga de él, se convierte en el nuevo árbol
    partida.asignar_subarbol(n);

    // Explorar siguiente nivel del árbol de soluciones
    generarArbolSoluciones(1);
  }
}

/* _________________________________________________________________________ */

int JugadorAuto::calcularPuntuacion(ArbolGeneral<Tablero>::Nodo n, int lvl)
{
  float puntos;
  Tablero aux = partida.etiqueta(n);
  int ganador = aux.quienGana();

  // Calcular puntuación del nodo
  if (ganador == 1)
    puntos = -2 - (N - lvl);
  else if (ganador == 2)
    puntos = 2 + (N - lvl) ;
  else
    puntos = 1 + (N - lvl);

  // Sistema puntuación métrica 1
  if (metrica == 1)
  {
    puntos += 0.25 * cantidadAlineada(aux, 3) +
              0.0625 * cantidadAlineada(aux, 2) + (N - lvl);
  }

  // Caso base
  if (!partida.hijomasizquierda(n))
    return puntos;

  // Caso general
  for (n = partida.hijomasizquierda(n); n; n = partida.hermanoderecha(n))
    puntos += calcularPuntuacion(n, lvl + 1);

  return puntos;
}

/* _________________________________________________________________________ */

int JugadorAuto::gana_inmediato()
{
  for (ArbolGeneral<Tablero>::Nodo n = partida.hijomasizquierda(partida.raiz());
       n; n = partida.hermanoderecha(n))
  {
    if (partida.etiqueta(n).quienGana() == 2)
      return partida.etiqueta(n).GetUltCol();
  }
  return -1;
}

/* _________________________________________________________________________ */

vector<ArbolGeneral<Tablero>::Nodo> JugadorAuto::evita_perder()
{
  vector<ArbolGeneral<Tablero>::Nodo> posibilidades;

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
      posibilidades.push_back(n1);
  }
  return posibilidades;
}

/* _________________________________________________________________________ */

int JugadorAuto::mayorPuntuacion(vector<ArbolGeneral<Tablero>::Nodo> v)
{
  // Almacenar el número de partidas ganadas (por el jugador auto) de cada nodo
  // en el que podemos meter ficha sin miedo a perder
  vector<int> puntuacion;
  for (int i = 0; i < v.size(); i++)
  {
    puntuacion.push_back(calcularPuntuacion(v[i], 0));
  }

  // Calcular el nodo con mayor número de partidas ganadas
  int max_pos = 0;
  for (int i = 0; i < puntuacion.size(); ++i)
  {
    if (puntuacion[max_pos] < puntuacion[i])
      max_pos = i;
  }

  return partida.etiqueta(v[max_pos]).GetUltCol();
}

/* _________________________________________________________________________ */

JugadorAuto::JugadorAuto(const Tablero& inicial, int num_metrica)
  : partida(inicial), metrica(num_metrica)
{
  // Métricas que exploran hasta una cierta profundidad (excepto aleatoria)
  if (metrica != 4)
  {
    int profundidad = (metrica == 3) ? 2 : N;
    generarArbolSoluciones(profundidad);
  }

  // Métrica aleatoria
  else
  {
    srand(time(0));
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

/* _________________________________________________________________________ */

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
