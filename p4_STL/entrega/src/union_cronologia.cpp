/**
 * @file union_cronologia.cpp
 * @brief Este programa realiza la unión de dos cronologías en otra
 * cronología resultante.
 *
 * Recibe como parámetros dos archivos con cronologías, y un tercero opcional
 * para ser el archivo de destino. Si no se proporciona este último, la cronología
 * resultante se imprime en la salida estándar.
 *
 */

#include <iostream>
#include <fstream>
#include "cronologia.hpp"

using namespace std;

/// Unir dos cronologías en una tercera
Cronologia Union(const Cronologia& c1, const Cronologia& c2)
{
  Cronologia crono_union(c1);

  for (Cronologia::const_iterator p = c2.begin(); p != c2.end(); ++p)
    crono_union.addEventoHistorico(p->second);

  return crono_union;
}

int main(int argc, char * argv[])
{
  if (argc != 3 && argc != 4)
  {
    cout << "Error: debe dar al menos los nombres de dos ficheros con cronologías. " << endl;
    cout << "[Opcional]: un tercer nombre de fichero para guardar la cronología resultante."
         << endl;
    return 1;
   }

   ifstream f1(argv[1]);
   if (!f1)
   {
     cout << "No puedo abrir el fichero " << argv[1] << endl;
     return 2;
   }
   ifstream f2(argv[2]);
   if (!f2)
   {
     cout << "No puedo abrir el fichero " << argv[2] << endl;
     return 2;
   }

   Cronologia c1, c2, cUnion;
   f1 >> c1;
   f2 >> c2;

   cUnion = Union(c1, c2);

   //No se dio fichero de salida, imprimimos en salida estándar
   if (argc == 3)
     cout << cUnion;
   else
   {
     ofstream fout(argv[3]);
     if (!fout)
     {
       cout << "No puedo crear el fichero " << argv[3] << endl;
       return 0;
     }
     fout << cUnion;
   }

   return 0;
}

/* Fin fichero: union_cronologia.cpp */
