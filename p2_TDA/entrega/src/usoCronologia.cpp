/**
 * @file usoCronologia.cpp
 * @brief Programa de prueba para ilustrar el uso del TDA Cronologia
 *
 */

#include <iostream>
#include <fstream>
#include "cronologia.hpp"

using namespace std;

  /*
     Quedan por probar estos métodos:

     - void addEventoHistorico(const EventoHistorico& e);
     - void addEventoHistorico(const std::vector<EventoHistorico>& v);
       (PASÁNDOLE UN VECTOR DESORDENADO, QUE INCLUYA AÑOS A.C.)

     - int eliminarPorClave (std::string key);

     - std::vector<EventoHistorico> buscarPorClave (std::string key) const;
  */

int main(int argc, char * argv[])
{
  if (argc != 3) {
    cerr << "Dime el nombre de dos ficheros con una cronología. " << endl;
    return 1;
  }
  ifstream f (argv[1]);
  ifstream g(argv[2]);

  if (!f) {
    cerr << "No puedo abrir el fichero " << argv[1] << endl;
    return 2;
  }
  if (!g) {
    cerr << "No puedo abrir el fichero " << argv[2] << endl;
    return 2;
  }

  //Cargamos cronologías
  Cronologia cronologia_1, precronologia_2;
  f >> cronologia_1;
  g >> precronologia_2;

  // Construimos una cronología a partir de un vector de Eventos
  Cronologia cronologia_2(precronologia_2.getCronologia());

  // Consultar los acontecimientos de un año en concreto
  cout << "Veamos los acontecimientos que sucedieron en un año en concreto." << endl;
  cout<<"Dime un año a consultar:";
  int anio;
  do {
    cin >> anio;
    if (!cronologia_1.contieneFecha(anio))
      cout << "Ese año no está en la cronología. Prueba otra vez: ";
  } while (!cronologia_1.contieneFecha(anio));
  cout << endl;

  cout << "Cogemos el Evento Histórico de ese año, y lo escribimos." << endl;
  EventoHistorico e = cronologia_1.getEventoHistorico(anio);
  cout << e;
  cout << endl;

  cout << "También podríamos quedarnmos solo con el vector de Acontecimientos, y"
       << "el resultado de la impresión sería el mismo." << endl;
  vector<Acontecimiento> eventos = cronologia_1.getAcontecimientos(anio);
  cout << "Escribimos el evento histórico: " << endl;
  for (int i = 0; i < eventos.size(); ++i)
    cout << "- " << eventos[i] << endl;
  cout << endl;

  // Modificar acontecimientos de un evento histórico de la cronología
  // También probamos el struct Fecha
  cout << "Modifiquemos ese acontecimiento en particular.\n";
  vector<Acontecimiento> nuevo;
  Fecha fecha(anio);
  nuevo.push_back("Aquí no pasó nada interesante.");
  cronologia_1.setEventoHistorico(nuevo, fecha);
  cout << endl;

  // Imprimir una cronología:
  cout << "Veamos la cronología 1, con sus modificaciones en el año " << anio << ".\n";
  cronologia_1.prettyPrint();
  cout << endl;

  // Eliminar un elemento
  cout << "Eliminemos ahora el Evento Histórico completo (año " << anio << "), y veamos el resultado: ";
  cronologia_1.eliminarEvento(fecha);
  cronologia_1.prettyPrint();
  cout << endl;






  // Probar el resto de métodos







  cout << "Mezclemos ambas cronologías, y además veamos la cronología resultante "
       << "invertida (en formato archivo): " << endl;
  cronologia_1.mezclarCronologia(cronologia_2);
  cronologia_1.mostrarCronologiaInversa(cout);
  cout << endl;

  // Guardar en fichero una cronología
  cout << "Cronología 2 guardada en ../datos/cr1.txt" << endl;
  ofstream o("../datos/cr1.txt");
  o << cronologia_2;
}

/* Fin fichero: usoCronologia.cpp */
