/**
 * @file test_list.cpp
 * @brief Archivo de pruebas para el T.D.A. List
 *
 */

#include <iostream>
#include "list.hpp"

using namespace std;

int main()
{
  // Constructor vacío
  List<int> l1,l2;

  // Rellenamos la lista
  cout << "Creamos una lista con los números del 1 al 10.\n\n";
  for(int i = 0; i < 10; i++)
    l1.push_back(i);

  // Probamos operador de asignación y constructor de copia
  l2 = l1;
  List<int> l3(l2);

  if (!l3.empty()) {
    cout << "El primer elemento de la lista es " << l3.first() << ", y el último es"
         << l3.last() << endl;

    l3.pop_back();
    cout << "Quitamos el último elemento, y ahora la lista acaba en " << l3.last() << endl;
  }

  l3.clear();
  if (l3.empty())
    cout << "\nLista borrada, es decir, ahora tiene tamaño " << l3.size() << endl;

  return 0;
}

/* Fin fichero: test_list.cpp */
