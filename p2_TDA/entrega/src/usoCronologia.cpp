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

  // Probar métodos getPrimero() y getUltimo()
  Fecha primero = cronologia_1.getPrimero();
  Fecha ultimo = cronologia_1.getUltimo();
  cout << "La cronología 1 está comprendida entre los años "
       << primero.anio << (primero.dc ? " DC" : " AC") << " y "
       << ultimo.anio << (ultimo.dc ? " DC" : " AC") << ".\n";

  // Consultar los acontecimientos de un año en concreto
  cout << "Veamos los acontecimientos que sucedieron en un año en concreto." << endl;
  cout<<"Dime un año a consultar (<DC/AC> <año>):";
  Fecha aux;
  do {
    cin >> aux.dc;
    cin >> aux.anio;
    if (!cronologia_1.contieneFecha(aux))
      cout << "Ese año no está en la cronología. Prueba otra vez: ";
  } while (!cronologia_1.contieneFecha(aux));

  cout << "Cogemos el Evento Histórico de ese año, y lo escribimos." << endl;
  EventoHistorico e = cronologia_1.getEventoHistorico(aux.anio);
  cout << e;
  cout << endl << endl;

  cout << "También podríamos quedarnos solo con el vector de Acontecimientos, y "
       << "el resultado de la impresión sería el mismo:" << endl;
  vector<Acontecimiento> eventos = cronologia_1.getAcontecimientos(aux.anio);
  for (unsigned int i = 0; i < eventos.size(); ++i)
    cout << "- " << eventos[i] << endl;
  cout << endl;

  // Modificar acontecimientos de un evento histórico de la cronología
  cout << "Modifiquemos ese acontecimiento en particular.\n";
  vector<Acontecimiento> nuevo;
  nuevo.push_back("Aquí no pasó nada interesante.");
  cronologia_1.setEventoHistorico(nuevo, aux);

  // Imprimir una cronología:
  cout << "Veamos la cronología 1, con sus modificaciones en el año "
       << aux.anio << (aux.dc ? " DC." : " AC.") << "\n";
  cronologia_1.prettyPrint();

  // Eliminar un elemento
  cout << "Eliminemos ahora el Evento Histórico completo (año "
       << aux.anio << (aux.dc ? " DC" : " AC") << "), y veamos el resultado:\n";
  cronologia_1.eliminarEvento(aux);
  cronologia_1.prettyPrint();

  // Añadir EventoHistorico
  cout << "Probemos ahora a añadir un EventoHistorico a nuestra cronología:" << endl;
  vector<string> acontecimientos1 = {"Constitución Española", "La OMS declara oficialmente que la viruela ha sido erradicada"};
  EventoHistorico mi_evento1(1978, acontecimientos1); // Conversión implícita de entero a Fecha
  cronologia_1.addEventoHistorico(mi_evento1);
  cronologia_1.prettyPrint();

  cout << "Ahora probamos a añadir un vector de EventoHistorico (desordenados)." << endl;
  Fecha mi_fecha2(1492);
  vector<string> acontecimientos2 = {"Los Reyes Católicos toman Granada", "Cristobal Colón '''descubre''' América"};
  EventoHistorico mi_evento3(mi_fecha2, acontecimientos2);

  Fecha mi_fecha3(492);
  mi_fecha3.dc = 0;
  vector<string> acontecimientos3 = {"Mardonio de Persia reconquista Tracia y ocupa Macedonia", "Comienzan las Guerras Médicas entre persas y griegos"};
  EventoHistorico mi_evento2(mi_fecha3, acontecimientos3);

  vector<EventoHistorico> mis_eventos;
  mis_eventos.push_back(mi_evento3);
  mis_eventos.push_back(mi_evento2);

  cronologia_1.addEventoHistorico(mis_eventos);
  cout << "Veamos que se han añadido los Eventos en orden correcto:\n";
  cronologia_1.prettyPrint();

  // eliminarPorClave
  cout << "Ahora probamos a eliminar por clave. Eliminamos los que contengan 'of' y "
       << "devolvemos el número de eventos eliminados.\n";
  int n = cronologia_1.eliminarPorClave("of");
  cout << "Eliminados: " << n << ".\n";
  cronologia_1.prettyPrint();
  cout << endl;

  // buscarPorClave
  cout << "Probamos ahora a mostrar solo los eventos de cronologia_1 que contengan la "
       << "palabra 'or':" << endl;
  std::vector<EventoHistorico> resultado_busqueda = cronologia_1.buscarPorClave("or");
  Cronologia cron_resultados_busqueda(resultado_busqueda);
  cron_resultados_busqueda.prettyPrint();

// Mezclar e imprimir inversa
  cout << "Mezclemos ambas cronologías, y además veamos la cronología resultante "
       << "invertida (en formato archivo): " << endl;
  cronologia_1.mezclarCronologia(cronologia_2);
  cronologia_1.mostrarCronologiaInversa(cout);
  cout << endl;

  // Guardar en fichero una cronología
  cout << "Cronología 2 guardada en datos/cr2.txt" << endl;
  ofstream o("datos/cr2.txt");
  o << cronologia_2;
}

/* Fin fichero: usoCronologia.cpp */
