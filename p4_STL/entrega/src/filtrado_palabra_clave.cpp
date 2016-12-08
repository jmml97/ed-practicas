/**
 * @file filtrado_palabra_clave.cpp
 * @brief Este programa construye una cronología subconjunto de otra mayor,
 * que incluye únicamente los acontecimientos en los que aparecen la(s) palabra(s)
 * clave(s) indicada(s) como argumento del programa.
 *
 * Los parámetros son los siguientes:
 *   1.El nombre del fichero con la cronología
 *   2. Palabra clave (opcional). Si no se especifica la palabra clave en línea de comandos,
 *      el  programa la pedirá por teclado.
 *   3. El nombre del fichero para guardar la cronología obtenida. (opcional). Si no se
 *      especifica nombre de fichero, se imprimirá por la salida estándar.
 *
 */

 #include <iostream>
 #include <fstream>
 #include "cronologia.hpp"

 using namespace std;

/**
  * Devuelve una cronología que contiene únicamente aquellos acontecimientos
  * de otra que contienen a su vez una palabra clave.
  */
Cronologia& buscarPorClave (const Cronologia& c, const string& key)
{
  //// ANTIGUA IMPLEMENTACIÓN; MEJORAR (CAMBIAR vector POR set)
  /*  IMPORTANTE:
     Si varios acontecimientos concurren el mismo año, sólo se devolverían como resultado del
     filtrado por palabra clave aquellos relacionados con la palabra clave.
  */

  Cronologia res;
  EventoHistorico tmp;

  for (Cronologia::const_iterator p = c.begin(); p != c.end(); ++p)
  {
    vector<Acontecimiento> v;
    v = p->buscarPorClave(key);
    if (v.size() != 0)
    {
      tmp.setFecha(p->getFecha());
      tmp.setEvento(v);
      res.push_back(tmp);
    }
  }

  return res;
}

int main(int argc, char * argv[])
{
  // Completar programa
  return 0;
}

/* Fin fichero: filtrado_palabra_clave.cpp */
