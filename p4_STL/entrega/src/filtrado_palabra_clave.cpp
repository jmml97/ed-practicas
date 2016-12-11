/**
 * @file filtrado_palabra_clave.cpp
 * @brief Este programa construye una cronología subconjunto de otra mayor,
 * que incluye únicamente los acontecimientos en los que aparecen la(s) palabra(s)
 * clave(s) indicada(s) como argumento del programa.
 *
 * Los parámetros son los siguientes:
 *   1. El nombre del fichero con la cronología.
 *   2. Palabra clave (opcional). Si no se especifica la palabra clave en línea de comandos,
 *      el  programa la pedirá por teclado.
 *   3. El nombre del fichero para guardar la cronología obtenida (opcional). Si no se
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
Cronologia BuscarPorClave(const Cronologia& c, const string& key)
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

  bool opc_entrada = false, opc_salida = false, opc_palabra = false, opc_ayuda = false;
  string fichero_entrada, fichero_salida, palabra;

  for (int i = 0; i < argc; i++) {

    if (string(argv[i]) == "-i") {
      if (i + 1 < argc) {
        fichero_entrada = argv[i+1];
        opc_entrada = true;
      }
    } else if (string(argv[i]) == "-p") {
      if (i + 1 < argc) {
        palabra = argv[i+1];
        opc_palabra = true;
      }
    } else if (string(argv[i]) == "-o") {
      if (i + 1 < argc) {
        fichero_salida = argv[i+1];
        opc_salida = true;
      }
    } else if (string(argv[i]) == "-h") {
      opc_ayuda = true;
    }

  }

  if (argc > 7)
  {
    cout << "Error en los argumentos, utiliza -h para ver la ayuda." << endl;
    return 1;
  }

  if (opc_ayuda) {
    cout << "uso: filtrado_palabra_clave [-i fichero] [-p palabra] [-o salida]" << endl;
    cout << "i : especifica un fichero de entrada" << endl;
    cout << "p : especifica la palabra clave a buscar" << endl;
    cout << "o : especifica el fichero de salida" << endl;
    return 1;
  }

  if (!opc_entrada) {
    cout << "Introduce la ruta del archivo que quieres leer: ";
    cin >> fichero_entrada;
    cout << endl;
  }

  ifstream f1(fichero_entrada);
  if (!f1)
  {
    cout << "No puedo abrir el fichero " << fichero_entrada << endl;
    return 2;
  }

  Cronologia c1, cFiltrada;
  f1 >> c1;

  if (!opc_palabra)
  {
    cout << "Introduzca la palabra clave: ";
    cin >> palabra;
  }

  cFiltrada = BuscarPorClave(c1, palabra);

  if (!opc_salida)
  {
    cFiltrada.prettyPrint();
  } else {
   ofstream fout(fichero_salida);
   if (!fout)
   {
     cout << "No puedo crear el fichero " << fichero_salida << endl;
     return 0;
   }
   fout << cFiltrada;
  }

  return 0;
}

/* Fin fichero: filtrado_palabra_clave.cpp */
