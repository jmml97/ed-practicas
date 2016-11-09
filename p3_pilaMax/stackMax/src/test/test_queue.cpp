/**
 * @file test_queue.cpp
 * @brief Archivo de pruebas para el T.D.A. Queue
 *
 */

#include <iostream>
#include "queue.hpp"

using namespace std;

int main()
{
  Queue<int> q1;
  int i;

  cout << "Rellenamos una cola con los números del 0 al 9.\n";
  for (i = 0; i < 10; i++)
    q1.push(i);

  cout << "El frente de la cola es: ";
  cout << q1.front() << endl;
  q1.pop();
  cout << "Quitamos uno, y el nuevo frente es: ";
  cout << q1.front() << endl;
  cout << "El número de elementos de la cola es ahora: ";
  cout << q1.size() << endl << endl;

  Queue<float> q2;
  int j;

  cout << "Rellenamos otra cola, pero esta vez con las fracciones n/10 para n = 0,...,9.\n";
  for (j = 0; j < 10 ;j++)
    q2.push(j/10.0);

  // Constructor de copias
  Queue<float> q(q2);

  cout << "El frente de la cola es: ";
  cout << q.front() << endl;
  q.pop();
  cout << "Quitamos uno, y el nuevo frente es: ";
  cout << q.front() << endl;
  cout << "El número de elementos de la cola es ahora: ";
  cout << q.size() << endl;

  return 0;
}

/* Fin fichero: test_queue.cpp */
