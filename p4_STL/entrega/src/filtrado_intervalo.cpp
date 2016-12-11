/**
 * @file filtrado_intervalo.cpp
 * @brief Este programa construye una cronología subconjunto de otra mayor,
 * que incluye únicamente los objetos EventoHistorico acontecidos en un intervalo de
 * tiempo especificado (el intervalo se considera cerrado).
 *
 * Los parámetros son los siguientes:
 *   1.El nombre del fichero con la cronología
 *   2. Límite inferior del intervalo (Fecha).
 *   3. Límite superior del intervalo (Fecha).
 *   4. El nombre del fichero para guardar la cronología obtenida. (opcional). Si no se
 *      especifica nombre de fichero, se imprimirá por la salida estándar.
 *
 */

#include <iostream>
#include <fstream>
#include "cronologia.hpp"

using namespace std;

/**
  * @brief Devuelve una Cronologia que contiene únicamente aquellos acontecimientos
  * de otra que contienen a su vez una palabra clave.
  * @param c Cronologia donde buscar los EventoHistorico
  * @param inicio Fecha de inicio
  * @param fin Fecha de finalización
  * @param res Cronologia donde se guarda el resultado
  * @pre res debe ser vacía.
  */
void Filtrar(const Cronologia& c, const Fecha& inicio, const Fecha& fin,
             Cronologia& res)
{
  Cronologia::const_iterator p = c.begin();
  compEventos comp;

  while (p != c.end() && p->first <= fin)
  {
    if (!comp(p->second,inicio))
    {
      res.addEventoHistorico(p->second);
    }
    ++p;
  }
}

int main(int argc, char * argv[])
{
  if (argc != 6 && argc != 7)
  {
    cout << "Error: debe dar al menos el nombre de un fichero con una cronología, "
         << "y los límites inferior y superior, en formato <AC/DC> <Año>.\n";
    cout << "[Opcional]: un tercer nombre de fichero para guardar la cronología "
         << "resultante.\n";
    return 1;
   }

   ifstream f(argv[1]);
   if (!f)
   {
     cout << "No puedo abrir el fichero " << argv[1] << endl;
     return 2;
   }

   Fecha fecha_min(stoi(argv[3]),stoi(argv[2]));
   Fecha fecha_max(stoi(argv[5]),stoi(argv[4]));

   // f1 debe ser menor o igual que f2
   if (fecha_min <= fecha_max)
   {
     Cronologia c1, cIntervalo;;
     f >> c1;

     Filtrar(c1, fecha_min, fecha_max, cIntervalo);

     //No se dio fichero de salida, imprimimos en salida estándar
     if (argc == 6)
       cIntervalo.prettyPrint();
     else
     {
       ofstream fout(argv[6]);
       if (!fout)
       {
         cout << "No puedo crear el fichero " << argv[6] << endl;
         return 0;
       }
       fout << cIntervalo;
     }
   }
   else
   {
     cout << "Error: la primera fecha debe ser menor o igual que la segunda.\n";
     return 1;
   }

   return 0;
}

/* Fin fichero: filtrado_intervalo.cpp */
