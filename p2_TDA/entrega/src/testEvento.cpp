#include "eventoHistorico.hpp"
#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char * argv[])
{

  if (argc != 2) {
      cout << "Dime el nombre del fichero con el evento histórico: " << endl;
      // return 1;
   }

   /*
   ifstream f(argv[1]);
   if (!f) {
    cout << "No puedo abrir el fichero " << argv[1] << endl;
    // return 1;
   }
   */

   // Leer evento de archivo
   // EventoHistorico mi_evento;
   // f >> mi_evento;

   /*
    Hacer pruebas, añadiendo código a este archivo, para ver que funciona:
      - Constructor con un parámetro
      - Constructor con dos parámetros
      - addEvento (en sus 2)
      - eliminarAcontecimiento
      - eliminarPorClave
      - buscarPorClave
   */

   Fecha mi_fecha;
   mi_fecha.anio = 1978;
   mi_fecha.dc = true;

   cout << "Evento (mi_evento1) construido solo con fecha: " << endl;
   EventoHistorico mi_evento1(mi_fecha);
   mi_evento1.prettyPrint();
   cout << endl;

   cout << "Evento (mi_evento2) construido con fecha y vector: " << endl;
   vector<string> acontecimientos = {"Constitución Española", "Nace el primer ponycornio", "Constitución Española"};
   EventoHistorico mi_evento2(mi_fecha, acontecimientos);
   mi_evento2.prettyPrint();
   cout << endl;

   cout << "Añadimos a mi_evento1 un acontecimiento y un vector. Debería tener ahora los mismos que mi_evento2 y otro adicional." << endl;
   mi_evento1.addEvento("La OMS declara oficialmente la erradicación de la viruela");
   mi_evento1.addEvento(acontecimientos);
   mi_evento1.addEvento("Constitución Española");
   mi_evento1.prettyPrint();
   cout << endl;

   cout << "Eliminamos ahora de mi_evento1 los acontecimientos 'Constitución Española' y los que contengan 'er'; debería quedarse vacío." << endl;
   mi_evento1.eliminarAcontecimiento("Constitución Española");
   mi_evento1.eliminarPorClave("er");
   mi_evento1.prettyPrint();
   cout << endl;

   cout << "Imprimimos ahora los acontecimientos de mi_evento2 que contengan 'el': " << endl;
   cout << mi_evento2.buscarPorClave("el").front() << endl;

   // Mostrar evento en pantalla
   // mi_evento.prettyPrint();

   // Escribir evento a archivo 'test.txt'
   // ofstream output("test.txt");
   // output << mi_evento;

   return 0;
}
