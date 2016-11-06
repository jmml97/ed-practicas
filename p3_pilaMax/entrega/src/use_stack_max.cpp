/**
 * @file use_stack_max.cpp
 * @brief Ejemplo para ilustrar el uso del T.D.A. StackMax
 *
 */

#include <iostream>
#include <fstream>
#include "stack_max.hpp"

using namespace std;

int main(int argc, char * argv[])
{
  if (argc != 2) {
    cerr << "Dime el nombre del fichero con la pila." << endl;
    return 1;
  }
  ifstream f (argv[1]);

  if (!f) {
    cerr << "No puedo abrir el fichero " << argv[1] << endl;
    return 2;
  }
  // Cargamos la pila
  StackMax s1;
  f >> s1;
  cout << "Hemos cargado una pila de tamaño " << s1.size() << ". Veámosla:\n";

  // Creamos otra pila como copia de la primera
  StackMax s2(s1);
  cout << s2;

  // Probamos el operador de asignación
  StackMax s;
  s2 = s;

  // Cargamos elementos en la pila
  cout << "Cargamos otra pila con los números del 0 al 10.\n";
  for (int i = 10; i >= 0; i--)
    s.push(i);

  // Vamos viendo el máximo
  cout << "Veamos cuál es el máximo en cada paso:\n\n";
  while (!s.empty()) {
    Element x = s.top();
    cout << x << endl;
    s.pop();
  }

  // PrettyPrint
  cout << "También podríamos ver directamente el contenido de la pila:\n";
  s.prettyPrint();
  cout << endl;

  // sameMax
  if (s.sameMax(s1))
    cout << "Las dos pilas tienen el mismo máximo.\n";
  else
    cout << "El máximo de las dos pilas es diferente.\n";

  // Guardar en fichero
  cout << "Pila guardada en datos/pila_out.txt";
  ofstream output("datos/pila_out.txt");
  output << s;

  // Borramos la lista
  s.clear();
  if (s.empty())
    cout << "\n\nPila borrada.";

  return 0;
}

/* Fin fichero: use_stack_max.cpp */
