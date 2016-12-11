/**
 * @file test_cronologia.cpp
 * @brief Fichero de prueba para el T.D.A. Cronologia
 *
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include "cronologia.hpp"

using namespace std;

int main(int argc, char * argv[])
{
  if (argc != 2) {
    cerr << "Dime el nombre de un ficheros con una cronología." << endl;
    return 1;
  }
  ifstream f(argv[1]);
  if (!f) {
    cerr << "No puedo abrir el fichero " << argv[1] << endl;
    return 2;
  }

  //Cargamos cronología
  Cronologia cronologia;
  f >> cronologia;

  // Construimos una cronología a partir de un contenedor
  Cronologia cronologia_1(cronologia.getCronologia());

  // Probar métodos getPrimero() y getUltimo()
  Fecha primero = cronologia_1.getPrimero();
  Fecha ultimo = cronologia_1.getUltimo();
  cout << "La cronología está comprendida entre los años "
       << primero.anio << (primero.dc ? " DC" : " AC") << " y "
       << ultimo.anio << (ultimo.dc ? " DC" : " AC") << ".\n";

  // Consultar los acontecimientos de un año en concreto
  cout << "Veamos los acontecimientos que sucedieron en un año en concreto." << endl;
  cout<<"Dime un año a consultar (FORMATO: <DC/AC> <año>): ";
  Fecha aux;
  do {
    cin >> aux.dc;
    cin >> aux.anio;
    if (!cronologia_1.contieneFecha(aux))
      cout << "Ese año no está en la cronología. Prueba otra vez: ";
  } while (!cronologia_1.contieneFecha(aux));

  cout << "Cogemos el Evento Histórico de ese año, y lo escribimos." << endl;
  cronologia_1[aux].prettyPrint();
  cout << endl;

  // Modificar acontecimientos de un evento histórico de la cronología
  cout << "Modifiquemos ese acontecimiento en particular.\n";
  set<Acontecimiento> nuevo;
  nuevo.insert("Aquí no pasó nada interesante.");
  cronologia_1.setEventoHistorico(nuevo, aux);

  // Imprimir una cronología:
  cout << "Veamos la cronología 1, con sus modificaciones en el año "
       << aux.anio << (aux.dc ? " DC." : " AC.") << "\n";
  cronologia_1.prettyPrint();

  // Comprobar la fecha de un acontecimiento
  Fecha f1 = cronologia_1.fechaAcontecimiento("Aquí no pasó nada interesante.");
  cout << "El evento 'Aquí no pasó nada interesante' ocurrió en el año "
       << f1.anio << (f1.dc ? " DC." : " AC.") << endl;

  if (!cronologia_1.contieneAcontecimiento("Aquí sucedieron cosas interesantes"))
    cout << "El evento 'Aquí sucedieron cosas interesantes' no está en la cronología.\n\n";

  // Eliminar un elemento
  cout << "Eliminemos ahora el Evento Histórico completo (año "
       << aux.anio << (aux.dc ? " DC" : " AC") << "), y veamos el resultado:\n";
  cronologia_1.eliminarEvento(aux);
  cronologia_1.prettyPrint();

  // Añadir EventoHistorico
  cout << "Probemos ahora a añadir un EventoHistorico a nuestra cronología:" << endl;
  set<Acontecimiento> acontecimientos1 = {"Constitución Española", "La OMS declara oficialmente que la viruela ha sido erradicada"};
  EventoHistorico mi_evento1(1978, acontecimientos1); // Conversión implícita de entero a Fecha
  cronologia_1.addEventoHistorico(mi_evento1);
  cronologia_1.prettyPrint();

  cout << "Ahora probamos a añadir un conjunto de EventoHistorico (desordenados)." << endl;
  Fecha mi_fecha2(1492);
  set<Acontecimiento> acontecimientos2 = {"Los Reyes Católicos toman Granada", "Cristobal Colón '''descubre''' América"};
  EventoHistorico mi_evento3(mi_fecha2, acontecimientos2);

  Fecha mi_fecha3(492);
  mi_fecha3.dc = 0;
  set<Acontecimiento> acontecimientos3 = {"Mardonio de Persia reconquista Tracia y ocupa Macedonia", "Comienzan las Guerras Médicas entre persas y griegos"};
  EventoHistorico mi_evento2(mi_fecha3, acontecimientos3);

  vector<EventoHistorico> mis_eventos;
  mis_eventos.push_back(mi_evento3);
  mis_eventos.push_back(mi_evento2);

  for (unsigned int i = 0; i < mis_eventos.size(); i++)
    cronologia_1.addEventoHistorico(mis_eventos[i]);

  cout << "Veamos que se han añadido los Eventos en orden correcto:\n";
  cronologia_1.prettyPrint();

  // eliminarPorClave
  cout << "Ahora probamos a eliminar por clave. Eliminamos todos los eventos que "
       << "contengan 'of', y devolvemos el número de eventos eliminados.\n";
  int n = cronologia_1.eliminarPorClave("of");
  cout << "Eliminados: " << n << ".\n";
  cronologia_1.prettyPrint();

  // Imprimir inversa y guardar en fichero una cronología
  cout << "Por último, guardemos la cronología en orden inverso...\n";
  cout << "Cronología 1 guardada en datos/cr1.txt" << endl;
  ofstream out("datos/cr1.txt");
  cronologia_1.mostrarCronologiaInversa(out);

  return 0;
}

/* Fin fichero: test_cronologia.cpp */
