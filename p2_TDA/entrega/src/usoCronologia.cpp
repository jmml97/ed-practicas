/**
 * @file usoCronologia.cpp
 * @brief Programa de prueba para ilustrar el uso del TDA Cronologia
 *
 */

#include <iostream>
#include <fstream>
#include "cronologia.hpp"

using namespace std;

int main(int argc, char * argv[])
{
  if (argc != 2) {
    cout << "Dime el nombre del fichero con la cronología. " << endl;
    return 1;
  }
  ifstream f (argv[1]);

  if (!f) {
    cout << "No puedo abrir el fichero " << argv[1] << endl;
    return 2;
  }

  Cronologia mi_cronologia;
  f >> mi_cronologia; //Cargamos cronología

  int anio;
  cout<<"Dime un año a consultar:";
  cin >> anio;

  // Cogemos el Evento histórico asociado a ese año
  EventoHistorico e = mi_cronologia.getEventoHistorico(anio);

  // Nos quedamos solo con el vector de Acontecimientos
  vector<Acontecimiento> eventos = mi_cronologia.getAcontecimientos(anio);
  cout << "Escribimos el evento histórico: " << endl;
}

/* Fin fichero: usoCronologia.cpp */
