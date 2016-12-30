/**
 * @file test_stack.cpp
 * @brief Archivo de pruebas para el T.D.A. Stack
 *
 */

#include <iostream>
#include "stack.hpp"

using namespace std;

int main()
{
  Stack<int> s1;
  int i;

  cout << "Rellenamos una pila con los números del 0 al 9.\n";
  for (i = 0; i < 10; i++)
    s1.push(i);

  cout << "El tope de la pila es: ";
  cout << s1.top() << endl;
  s1.pop();
  cout << "Quitamos uno, y el nuevo tope es: ";
  cout << s1.top() << endl;
  cout << "El número de elementos de la pila es ahora: ";
  cout << s1.size() << endl << endl;

  Stack<float> s2;
  int j;

  cout << "Rellenamos otra pila, pero esta vez con las fracciones n/10 para n = 0,...,9.\n";
  for (j = 0; j < 10 ;j++)
    s2.push(j/10.0);

  // Constructor de copias
  Stack<float> s(s2);

  cout << "El tope de la pila es: ";
  cout << s.top() << endl;
  s.pop();
  cout << "Quitamos uno, y el nuevo tope es: ";
  cout << s.top() << endl;
  cout << "El número de elementos de la pila es ahora: ";
  cout << s.size() << endl;

  return 0;
}

/* Fin fichero: test_stack.cpp */
