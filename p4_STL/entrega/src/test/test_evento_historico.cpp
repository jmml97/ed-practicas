/**
 * @file test_evento_historico.cpp
 * @brief Fichero de prueba para el T.D.A. EventoHistorico
 *
 */

#include "evento_historico.hpp"
#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char * argv[])
{
   Fecha mi_fecha(1978);

   cout << "Evento (mi_evento1) construido solo con fecha: " << endl;
   EventoHistorico mi_evento1(mi_fecha);
   mi_evento1.prettyPrint();
   cout << endl;

   cout << "Veamos el cambio de fecha: " << endl;
   mi_evento1.setFecha(2005);
   mi_evento1.prettyPrint();
   cout << endl;

   cout << "Evento (mi_evento2) construido con fecha y conjunto: " << endl;
   set<Acontecimiento> acontecimientos = {"Constitución Española", "Nace el primer ponycornio", "Constitución Española"};
   EventoHistorico mi_evento2(mi_fecha, acontecimientos);
   mi_evento2.prettyPrint();
   cout << endl;

   cout << "Añadimos a mi_evento1 un acontecimiento y un conjunto. Debería tener ahora los mismos que mi_evento2 y otros dos adicionales." << endl;
   mi_evento1.addEvento("La OMS declara oficialmente la erradicación de la viruela");
   mi_evento1.addEvento(acontecimientos);
   mi_evento1.addEvento("Constitución Española");
   mi_evento1.addEvento("El primer caso.");
   mi_evento1.prettyPrint();
   cout << endl;

   cout << "Eliminamos ahora de mi_evento1 los acontecimientos 'Constitución Española' y los que contengan 'er'; debería quedarse vacío." << endl;
   mi_evento1.eliminarAcontecimiento("Constitución Española");
   mi_evento1.eliminarPorClave("er");
   mi_evento1.prettyPrint();
   cout << endl;

   cout << "Imprimimos ahora los acontecimientos de mi_evento2 (hemos añadido uno nuevo) que contengan 'el': " << endl;
   mi_evento2.addEvento("Se crea el mundo");

   EventoHistorico evento_busqueda(mi_evento2.getFecha(), mi_evento2.buscarPorClave("el"));

   if (evento_busqueda.tieneAcontecimiento("Se crea el mundo")) {
     for (EventoHistorico::const_iterator p = evento_busqueda.begin(); p != evento_busqueda.end(); ++p)
      cout << "- " << *p << endl;
   }


   return 0;
}

/* Fin: test_evento_historico.cpp */
