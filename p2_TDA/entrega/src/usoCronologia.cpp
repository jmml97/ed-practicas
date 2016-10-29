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


  // Añadir EventoHistorico

  cout << "Probemos ahora a añadir un EventoHistorico a nuestra cronología:" << endl;

  Fecha mi_fecha1(1978);
  vector<string> acontecimientos1 = {"Constitución Española", "La OMS declara oficialmente que la viruela ha sido erradicada"};
  EventoHistorico mi_evento1(mi_fecha1, acontecimientos1);

  cronologia_1.addEventoHistorico(mi_evento1);
  cronologia_1.prettyPrint();

  cout << "Ahora probamos a añadir un vector de EventoHistorico (desordenados)" << endl;

  Fecha mi_fecha2(1492);
  vector<string> acontecimientos2 = {"Los Reyes Católicos toman Granada", "Cristobal Colón '''descubre''' América"};
  EventoHistorico mi_evento3(mi_fecha2, acontecimientos2);

  Fecha mi_fecha3(492);
  mi_fecha3.dc=0;
  vector<string> acontecimientos3 = {"Mardonio de Persia reconquista Tracia y ocupa Macedonia", "Comienzan las Guerras Médicas entre persas y griegos"};
  EventoHistorico mi_evento2(mi_fecha3, acontecimientos3);

  vector<EventoHistorico> mis_eventos;
  mis_eventos.push_back(mi_evento2);
  mis_eventos.push_back(mi_evento3);

  cronologia_1.addEventoHistorico(mis_eventos);

  // eliminarPorClave

  cout << "Ahora pronamos a eliminar por clave. Probamos a eliminar los que contengan 'of' y devolvemos el número de elementos eliminados." << cronologia_1.eliminarPorClave("of") << endl;

  // buscarPorClave

  cout << "Probamos ahora a mostrar solo los eventos de cronologia_1 que contengan la palabra 'Grecia' (debería salir solo uno):" << endl;
  std::vector<EventoHistorico> resultado_busqueda = cronologia_1.buscarPorClave("Grecia");

  Cronologia cron_resultados_busqueda(resultado_busqueda);
  cron_resultados_busqueda.prettyPrint();

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
