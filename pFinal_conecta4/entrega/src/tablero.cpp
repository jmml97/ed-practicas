/**
 * @file tablero.cpp
 * @brief Implementación de funciones del TDA Tablero
 *
 */

#include <iostream>
#include "tablero.h"

using namespace std;

const string Tablero::COLOR_J1 = "\033[0;31m";  // Rojo
const string Tablero::COLOR_J2 = "\033[0;33m";  // Amarillo

void Tablero::reserve()
{
  this->tablero.resize(filas);
  for(int i = 0; i < filas ; i ++)
  {
    this->tablero[i].resize(columnas);
    for(int j = 0; j < columnas; j++)
      this->tablero[i][j] = 0;
  }
}

/* _________________________________________________________________________ */

Tablero::Tablero()
  : filas(0), columnas(0), turno(1), ult_col(-1)
{
}

/* _________________________________________________________________________ */

Tablero::Tablero(const int filas, const int columnas)
  : filas(filas), columnas(columnas),
    turno(1), ult_col(-1)
{
  reserve();
}

/* _________________________________________________________________________ */

Tablero::Tablero(const Tablero& t)
  : tablero(t.tablero), filas(t.filas),
    columnas(t.columnas), turno(t.turno),
    ult_col(t.ult_col)
{
}

/* _________________________________________________________________________ */

bool Tablero::estaLleno()
{
  bool sinHuecos = true;
  for (int i = 0; i < filas && sinHuecos; i++)
    for (int j = 0; j < columnas && sinHuecos; j++)
      sinHuecos = this->tablero[i][j] != 0;
  return sinHuecos;
}

/* _________________________________________________________________________ */

int Tablero::hayHueco(int pos)
{
  int i = 0;               // Recorremos la matriz de arriba hacia abajo.
  bool encontrado = false;

  // Comprobamos si la posición no está dentro del tablero.
  if (pos < 0 || pos >= columnas)
    return -1;

  while (i < filas && !encontrado)
  {
    if (this->tablero[i][pos] != 0)
      encontrado = true;
    else
      i++;
  }

  // Si no hay piezas.
  if (!encontrado && i == filas)
    return filas-1;
  else if (i < filas && i >= 0)
    return i-1;
  else
    return -1;
}

/* _________________________________________________________________________ */

bool Tablero::colocarFicha(int pos)
{
  int fila;

  // Comprobamos que hay espacio en la columna.
  fila = hayHueco(pos);
  if (fila != -1)
  {
    this->tablero[fila][pos] = turno;
    ult_col = pos;
    return true;
  }
  return false;
}

/* _________________________________________________________________________ */

int Tablero::cambiarTurno()
{
  if (turno == 1)
    turno = 2;
  else
    turno = 1;
  return turno;
}

/* _________________________________________________________________________ */

void Tablero::SetTablero(vector<vector<int> > tablero, int ult_col)
{
  int filas1, filas2, columnas1, columnas2;
  filas1 = GetFilas();
  filas2 = tablero.size();
  columnas1 = GetColumnas();
  columnas2 = tablero[1].size();

  if (filas1 == 0 || columnas1 == 0)
  {
    this->tablero = tablero;
    this->ult_col = ult_col;
  }

  else
  {
    // Si tiene la misma dimensión.
    if (filas1 == filas2 && columnas1 == columnas2)
    {
      this->tablero = tablero;
      this->ult_col = ult_col;
    }
    else
    {
      cout << "Se han intentado igualar tableros de distintas dimensiones." << endl;
    }
  }
}

/* _________________________________________________________________________ */

Tablero& Tablero::operator=(const Tablero& derecha)
{
  // Comprobamos que no se está copiando el mismo objeto.
  if (this == &derecha)
    return *this;
  // Asignamos el tablero de la derecha en la igualdad.
  SetTablero(derecha.GetTablero(), derecha.GetUltCol());
  return *this;
}

/* _________________________________________________________________________ */

ostream& operator<<(ostream& os, const Tablero& t)
{
  os << t.GetTablero();
  return os;
}

/* _________________________________________________________________________ */

int Tablero::quienGana()
{
  int ganador = 0;
  int count = 0;
  int i, j;

  for (i = 0; i < filas; i++)
  {
    for (j = 0; j < columnas; j++)
    {
      // comprobar columnas
      count = 0;
      for (int k = 0; k < N_FICHAS_GANAR
           && i + k < filas; k++)
      {
        if (tablero[i + k][j] != 0)
        {
          if (count == 0)
          {
            ganador = tablero[i + k][j];
            count++;
          }
          else
          {
            if (ganador == tablero[i + k][j])
            {
              count++;
            }
            else
            {
              count = 0;
              break;
            }
          }

          if (count == N_FICHAS_GANAR)
            return ganador;
        }
        else
        {
          break;
        }
      }

      // comprobar filas
      count = 0;
      for (int k = 0; k < N_FICHAS_GANAR
           && j + k < columnas; k++)
      {
        if (tablero[i][j + k] != 0)
        {
          if (count == 0)
          {
            ganador = tablero[i][j + k];
            count++;
          }
          else
          {
            if (ganador == tablero[i][j + k])
            {
              count++;
            }
            else
            {
              count = 0;
              break;
            }
          }

          if (count == N_FICHAS_GANAR)
            return ganador;
        }
        else
        {
          break;
        }
      }

      // comprobar diagonal 1
      count = 0;
      for (int k = 0; k < N_FICHAS_GANAR
           && i + k < filas
           && j + k < columnas; k++)
      {
        if (tablero[i + k][j + k] != 0)
        {
          if (count == 0)
          {
            ganador = tablero[i + k][j + k];
            count++;
          }
          else
          {
            if (ganador == tablero[i + k][j + k])
            {
              count++;
            }
            else
            {
              count = 0;
              break;
            }
          }

          if (count == N_FICHAS_GANAR)
            return ganador;
        }
        else
        {
          break;
        }
      }

      // comprobar diagonal 2
      count = 0;
      for (int k = 0; k < N_FICHAS_GANAR
           && i - k >= 0
           && j + k < columnas; k++)
      {
        if (tablero[i - k][j + k] != 0)
        {
          if (count == 0)
          {
            ganador = tablero[i - k][j + k];
            count++;
          }
          else
          {
            if (ganador == tablero[i - k][j + k])
            {
              count++;
            }
            else
            {
              count = 0;
              break;
            }
          }

          if (count == N_FICHAS_GANAR)
            return ganador;
        }
        else
        {
          break;
        }
      }
    }
  }
  return 0;
}

/* _________________________________________________________________________ */

template <class T>
ostream& operator<<(ostream& s, const vector<vector<T> >& c)
{
  typename vector<vector<T> >::const_iterator i;
  s << '\n';    // para que al recorrer en el arbol no bailen las filas
  for (i = c.begin(); i != c.end(); i++)
      s << "|" << (*i) << "|\n";
  return s;
}

/* _________________________________________________________________________ */

template <class T>
ostream& operator<<(ostream& s, const vector<T>& c)
{
  typename vector<T>::const_iterator i;
  const string DEFAULT_COLOR = "\033[0m";

  for (i = c.begin(); i != c.end(); i++)
  {
    if ((*i) == 0)
      s << "  ";
    else if ((*i) == 1)
      s << Tablero::COLOR_J1 << Tablero::CHAR_J1 << DEFAULT_COLOR << ' ';
    else if ((*i) == 2)
      s << Tablero::COLOR_J2 << Tablero::CHAR_J2 << DEFAULT_COLOR << ' ';
    else
      s << ' ';
  }
  return s;
}

/* Fin fichero: tablero.cpp */
