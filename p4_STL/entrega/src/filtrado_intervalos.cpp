/**
 * @file filtrado_intervalos.cpp
 * @brief Este programa construye una cronología subconjunto de otra mayor,
 * que incluye únicamente los objetos EventoHistorico acontecidos en un intervalo de
 * tiempo especificado (el intervalo se considera cerrado).
 *
 * Los parámetros son los siguientes:
 *   1.El nombre del fichero con la cronología
 *   2. Límite inferior del intervalo.
 *   3. Límite superior del intervalo.
 *   3. El nombre del fichero para guardar la cronología obtenida. (opcional). Si no se
 *      especifica nombre de fichero, se imprimirá por la salida estándar.
 *
 */

 #include <iostream>
 #include <fstream>
 #include "cronologia.hpp"

 using namespace std;

/**
  * Devuelve una cronología que contiene únicamente aquellos acontecimientos
  * de otra que contienen a su vez una palabra clave.
  */
Cronologia& filtrar (const Cronologia& c, const Fecha& inicio, const Fecha& fin)
{
  // Completar implementación
}

int main(int argc, char * argv[])
{
  // Completar programa
  return 0;
}

/* Fin fichero: filtrado_intervalos.cpp */
