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

   EventoHistorico mi_evento;
   f >> mi_evento;

   int anio;
   cout << "Dime un año a consultar: ";
   cin >> anio;

   cout << mi_evento << endl;

   return 0;
}
