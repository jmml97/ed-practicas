/**
 * @file test_dvector.cpp
 * @brief Archivo de pruebas para el T.D.A. DVector
 *
 */

#include <iostream>
#include "dvector.hpp"

using namespace std;

int main()
{
  cout << "Creamos un vector vacío, v1." << endl;
  DVector<int> v1;
  cout << "Tamaño de v1: " << v1.size() << endl;
  cout << "Creamos un vector v2 de tamaño 1 y elemento 4." << endl;
  DVector<int> v2(1, 4);
  cout << "Tamaño de v2: " << v2.size() << endl;
  cout << "Primer elemento de v2: " << v2[0] << endl;
  cout << "Creamos un vector v3 como copia de v2." << endl;
  DVector<int> v3(v2);
  cout << "Tamaño de v3: " << v3.size() << endl;
  cout << "Primer elemento de v3: " << v3.get(0) << endl;
  cout << "Cambiamos el tamaño de v1 a 4." << endl;
  v1.resize(4);
  cout << "El nuevo tamaño de v1 es: " << v1.size() << endl;
  cout << "Cambiamos ahora el tamaño de v1 de 4 a 3." << endl;
  v1.resize(3);
  cout << "El nuevo tamaño de v1 es: " << v1.size() << endl;
  cout << "Añadimos a v1 el elemento 1 en la posición 0." << endl;
  v1.set(0, 1);
  cout << "v1(0): " << v1.get(0) << endl;
  cout << "Añadimos el 13 al final de v1:" << endl;
  v1.push_back(13);
  cout << "v1(3): " << v1.get(3) << endl;
  cout << "Quitamos el último elemento de v1." << endl;
  v1.pop_back();
  cout << "El nuevo tamaño de v1 es: " << v1.size() << endl;
  cout << "Por último, reducimos la capacidad de v1 al mismo número "
       << "que sus elementos." << endl;
  v1.shrink_to_fit();

  v1.clear();
  if (v1.empty())
    cout << "Vector borrado." << endl;

  return 0;
}

/* Fin fichero: test_dvector.cpp */
