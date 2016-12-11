/**
 * @file estadistica_eventos.cpp
 * @brief El objetivo de este programa es obtener descriptores estadísticos
 * básicos relacionados con el volumen y distribución de EventoHistorico en el periodo de
 * tiempo abarcado por una Cronología. Para ello, calcula el número total de años para
 * los que se especifican EventoHistóricos en la cronología, el número total de acontecimientos,
 * y el máximo y promedio de estos acontecimientos por año.
 *
 * Recibe como parámetro el nombre de un fichero con una cronología, e imprime el
 * resultado en la salida estándar.
 */

#include <iostream>
#include <fstream>
#include "cronologia.hpp"

using namespace std;

/**
 * @brief Devuelve el número total de EventoHistorico y de Acontecimiento
 * de una Cronología.
 * @return Una pareja, cuyo primer elemento es el número total de EventoHistorico,
 * y el segundo el número total de Acontecimiento
 */
pair<int,int> CantidadAcontecimientos(const Cronologia& c)
{
  pair<int,int> res(0,0);

  for (Cronologia::const_iterator p = c.begin(); p != c.end(); ++p)
  {
    for (EventoHistorico::const_iterator it = p->second.begin();
         it != p->second.end(); ++it)
    {
      res.second++;
    }
    res.first++;
  }

  return res;
}

/// Devuelve el número máximo de Acontecimientos en un año.
int MaxAcontecimientos(const Cronologia& c)
{
  int max = 0;
  for (Cronologia::const_iterator p = c.begin(); p != c.end(); ++p)
  {
    int num_acontecimientos = 0;
    for (EventoHistorico::const_iterator it = p->second.begin();
         it != p->second.end(); ++it)
    {
      num_acontecimientos++;
    }
    if (num_acontecimientos > max)
      max = num_acontecimientos;
  }
  return max;
}

int main(int argc, char * argv[])
{
  if (argc < 2)
  {
    cout << "Error: debe dar el nombre de un fichero con una cronología.\n";
    return 1;
  }

  ifstream f(argv[1]);
  if (!f)
  {
    cout << "No puedo abrir el fichero " << argv[1] << endl;
    return 2;
  }

  // Cargar cronología
  Cronologia c1;
  f >> c1;

  pair<int,int> total = CantidadAcontecimientos(c1);
  int media = total.second / total.first;
  int max = MaxAcontecimientos(c1);

  cout << "Hay " << total.first << " años en la cronología para los que se especifica un "
       << "EventoHistorico, y hay " << total.second << " acontecimientos en total.\n";

  cout << "El máximo de estos acontecimientos en un año es " << max << ", y el promedio"
       << " por año es " << media << ".\n";

  return 0;
}

/* Fin fichero: estadistica_eventos.cpp */
