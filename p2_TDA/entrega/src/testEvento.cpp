#include "eventoHistorico.hpp"
#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char * argv[])
{

  if (argc != 2) {
      cout << "Dime el nombre del fichero con el evento histórico: " << endl;
      return 1;
   }

   ifstream f(argv[1]);
   if (!f) {
    cout << "No puedo abrir el fichero " << argv[1] << endl;
    return 1;
   }

   // Leer evento de archivo
   EventoHistorico mi_evento;
   f >> mi_evento;

   /*
    Hacer pruebas, añadiendo código a este archivo, para ver que funciona:
      - Constructor con un parámetro
      - Constructor con dos parámetros
      - addEvento (en sus 2 variantes)
      - eliminarAcontecimiento
      - eliminarPorClave
      - buscarPorClave
   */

   // Mostrar evento en pantalla
   mi_evento.prettyPrint();

   // Escribir evento a archivo 'test.txt'
   ofstream output("test.txt");
   output << mi_evento;

   return 0;
}
