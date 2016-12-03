/**
  * @file evento_historico.cpp
  * @brief Implementación del TDA EventoHistorico
  *
  */

#include <iostream>
#include <sstream>
#include <cassert>
#include "evento_historico.hpp"

using namespace std;

// Constantes de archivo
namespace
{
  const char SEP = '#';
}

// Constructor de Fecha
Fecha::Fecha(int n)
{
  assert(n >= 0);
  anio = n;
  dc = true;
}

// Constructor con dos parámetros
EventoHistorico::EventoHistorico(Fecha f, const set<Acontecimiento>& a)
  : EventoHistorico(f)
{
  setEvento(a);
}

// Modificar fecha
void EventoHistorico::setFecha(Fecha f)
{
  assert(f.anio >= 0);
  ev.first = f;
}

// Mezclar Acontecimientos
void EventoHistorico::addEvento(const set<Acontecimiento>& a)
{
  ev.second.insert(a.begin(), a.end());
}

// Eliminar todos los acontecimientos que contengan "key"
int EventoHistorico::eliminarPorClave (string key)
{
  int n = 0;
  iterator p = begin();
  while (p != end())
  {
    if ((p->find(key)) != string::npos)
    {
      ev.second.erase(p);
      n++;
    }
    else
      ++p;
  }
  return n;
}

// Buscar todos los acontecimientos que contengan "key"
set<Acontecimiento> EventoHistorico::buscarPorClave (string key) const
{
  set<Acontecimiento> a;
  for (const_iterator p = begin(); p != end(); ++p)
    if (p->find(key) != string::npos)
      a.insert(*p);
  return a;
}

// Cargar EventoHistorico desde un flujo de entrada
istream& EventoHistorico::cargarEvento(istream& is)
{
  Fecha fecha;
  set<Acontecimiento> a;
  string aux;

  // Leer si es AC o DC
  getline(is, aux, SEP);
  fecha.dc = stoi(aux);
  // Leer el año
  getline(is, aux, SEP);
  fecha.anio = stoi(aux);
  // Leer el resto de la ĺínea
  getline(is, aux);

  // Crear buffer de entrada a partir de un string
  istringstream ss(aux);
  while (getline(ss, aux, SEP))
  {
    a.insert(aux);
  }

  if (is)
  {
    setFecha(fecha);
    setEvento(a);
  }

  return is;
}

// Mostrar EventoHistorico a un flujo de salida
ostream& EventoHistorico::mostrarEvento(ostream& os) const
{
  os << ev.first.dc << SEP;
  os << ev.first.anio << SEP;
  const_iterator p = begin();

  // Escribir un evento
  if (p != end())
  {
    os << *p;

    for (++p; p != end(); ++p)
      os << SEP << *p;  // No hay SEP al final
  }
  return os;
}

// Mostar un EventoHistorico en Human Readable Format
ostream& EventoHistorico::prettyPrint(ostream& os) const
{
  os << "Año: " << ev.first.anio << (ev.first.dc ? " DC." : " AC.") << endl;
  for (const_iterator p = begin(); p != end(); ++p)
    os << "- " << *p << endl;
  return os;
}

// Operator>>
istream& operator>>(istream& is, EventoHistorico& e)
{
  return e.cargarEvento(is);
}

// Operator<<
ostream& operator<<(ostream& os, const EventoHistorico& e)
{
  return e.mostrarEvento(os);
}

// Comprobar si el evento b es más reciente que el evento a
bool eventoMasReciente(const EventoHistorico& a, const EventoHistorico& b)
{
    Fecha f1 = a.getFecha();
    Fecha f2 = b.getFecha();
    return ((f1.dc < f2.dc) || (f2.dc && f1.anio <= f2.anio)
            || !(f1.dc && f1.anio >= f2.anio));
}

/* Fin fichero: evento_historico.cpp */
