/**
 * @file use_queue_max.cpp
 * @brief Ejemplo para ilustrar el uso del T.D.A. QueueMax
 *
 */

#include <iostream>
#include <fstream>
#include "queue_max.hpp"

using namespace std;

int main(int argc, char * argv[])
{
  if (argc != 2)
  {
    cerr << "Dime el nombre del fichero con la cola." << endl;
    return 1;
  }
  ifstream f(argv[1]);

  if (!f)
  {
    cerr << "No puedo abrir el fichero " << argv[1] << endl;
    return 2;
  }
  // Cargamos la cola
  QueueMax q1;
  f >> q1;
  cout << "Hemos cargado una cola de tamaño " << q1.size() << ". Veámosla:\n";

  // Creamos otra cola como copia de la primera
  QueueMax q2(q1);
  cout << q2 << endl;

  // Cargamos elementos en la cola
  QueueMax q;
  cout << "Cargamos otra cola con los números del 0 al 10.\n";
  for (int i = 10; i >= 0; i--)
    q.push(i);

  // Salvamos la cola
  q2 = q;

  // Vamos viendo el máximo
  cout << "Veamos cuál es el máximo en cada paso:\n";
  while (!q.empty())
  {
    Element x = q.front();
    cout << x << endl;
    q.pop();
  }
  cout << endl;

  // PrettyPrint
  cout << "También podríamos ver directamente el contenido de la cola:\n";
  q2.prettyPrint();
  cout << endl;

  // sameMax
  if (q2.sameMax(q1))
    cout << "Las dos colas tienen el mismo máximo.\n";
  else
    cout << "El máximo de las dos colas es diferente.\n";
  cout << endl;

  // Guardar en fichero
  cout << "Cola guardada en datos/queue_out.txt";
  ofstream output("datos/queue_out.txt");
  output << q2;
  cout << endl;

  // Borramos la cola
  q2.clear();
  if (q2.empty())
    cout << "Cola borrada.\n";

  return 0;
}

/* Fin fichero: use_queue_max.cpp */
