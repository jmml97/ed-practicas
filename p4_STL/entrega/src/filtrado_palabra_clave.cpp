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
Cronologia buscarPorClave (const Cronologia& c, const string& key)
{

  Cronologia res;
  EventoHistorico tmp;

  for (Cronologia::const_iterator p = c.begin(); p != c.end(); ++p)
  {
    std::set<Acontecimiento> s;
    s = p->second.buscarPorClave(key);
    if (s.size() != 0)
    {
      tmp.setFecha(p->second.getFecha());
      tmp.setEvento(s);
      res.addEventoHistorico(tmp);
    }
  }

  return res;
}

int main(int argc, char * argv[])
{
  if (argc != 3 && argc != 4)
  {
    cout << "Error: debe dar al menos el nombre de la cronología en la que quieres buscar y la palabra clave " << endl;
    cout << "[Opcional]: un tercer nombre de fichero para guardar la cronología resultante." << endl;
    return 1;
   }

   ifstream f1(argv[1]);
   if (!f1)
   {
     cout << "No puedo abrir el fichero " << argv[1] << endl;
     return 2;
   }

   Cronologia c1, cFiltrada;
   f1 >> c1;

   cFiltrada = buscarPorClave(c1, argv[2]);

   //No se dio fichero de salida, imprimimos en salida estándar
   if (argc == 3)
     cout << cFiltrada;
   else
   {
     ofstream fout(argv[3]);
     if (!fout)
     {
       cout << "No puedo crear el fichero " << argv[3] << endl;
       return 0;
     }
     fout << cFiltrada;
   }

   return 0;
}

/* Fin fichero: filtrado_palabra_clave.cpp */
