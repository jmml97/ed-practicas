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
  if (argc != 2)
  {
    cerr << "Dime el nombre del fichero con la pila." << endl;
    return 1;
  }
  ifstream f(argv[1]);

  if (!f)
  {
    cerr << "No puedo abrir el fichero " << argv[1] << endl;
    return 2;
  }
  // Cargamos la pila
  StackMax s1;
  f >> s1;
  cout << "Hemos cargado una pila de tamaño " << s1.size() << ". Veámosla:\n";

  // Creamos otra pila como copia de la primera
  StackMax s2(s1);
  cout << s2 << endl;

  // Cargamos elementos en la pila
  StackMax s;
  cout << "Cargamos otra pila con los números del 0 al 10.\n";
  for (int i = 10; i >= 0; i--)
    s.push(i);

  // Salvamos la pila
  s2 = s;

  // Vamos viendo el máximo
  cout << "Veamos cuál es el máximo en cada paso:\n";
  while (!s.empty())
  {
    Element x = s.top();
    cout << x << endl;
    s.pop();
  }
  cout << endl;

  // PrettyPrint
  cout << "También podríamos ver directamente el contenido de la pila:\n";
  s2.prettyPrint();
  cout << endl;

  // sameMax
  if (s2.sameMax(s1))
    cout << "Las dos pilas tienen el mismo máximo.\n";
  else
    cout << "El máximo de las dos pilas es diferente.\n";
  cout << endl;

  // Guardar en fichero
  cout << "Pila guardada en datos/stack_out.txt";
  ofstream output("datos/stack_out.txt");
  output << s2;
  cout << endl;

  // Borramos la lista
  s2.clear();
  if (s2.empty())
    cout << "Pila borrada.\n";

  return 0;
}

/* Fin fichero: use_stack_max.cpp */
