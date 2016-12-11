/**
  * @file evento_historico.cpp
  * @brief Implementación del T.D.A. EventoHistorico
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

/* _________________________________________________________________________ */

Fecha::Fecha(int n, bool dc)
{
  assert(n >= 0);
  anio = n;
  this->dc = true;
}

/* _________________________________________________________________________ */

bool Fecha::operator<=(const Fecha& f) const
{
  return ((dc < f.dc) || (f.dc && anio <= f.anio)
           || !(dc && anio > f.anio));
}

/* _________________________________________________________________________ */

EventoHistorico::EventoHistorico(const Fecha& f, const set<Acontecimiento>& a)
  : EventoHistorico(f)
{
  setEvento(a);
}

/* _________________________________________________________________________ */

void EventoHistorico::setFecha(const Fecha& f)
{
  assert(f.anio >= 0);
  ev.first = f;
}

/* _________________________________________________________________________ */

void EventoHistorico::addEvento(const set<Acontecimiento>& a)
{
  ev.second.insert(a.begin(), a.end());
}

/* _________________________________________________________________________ */

void EventoHistorico::eliminarAcontecimiento(const_iterator it)
{
  assert(ev.second.count(*it));
  ev.second.erase(it);
}

/* _________________________________________________________________________ */

int EventoHistorico::eliminarPorClave (const string& key)
{
  int n = 0;
  for (const_iterator p = begin(); p != end(); ++p)
  {
    if ((p->find(key)) != string::npos)
    {
      ev.second.erase(p);
      n++;
    }
  }
  return n;
}

/* _________________________________________________________________________ */

set<Acontecimiento> EventoHistorico::buscarPorClave (const string& key) const
{
  set<Acontecimiento> a;
  for (const_iterator p = begin(); p != end(); ++p)
    if (p->find(key) != string::npos)
      a.insert(*p);
  return a;
}

/* _________________________________________________________________________ */

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

/* _________________________________________________________________________ */

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

/* _________________________________________________________________________ */

ostream& EventoHistorico::prettyPrint(ostream& os) const
{
  os << "Año: " << ev.first.anio << (ev.first.dc ? " DC." : " AC.") << endl;
  for (const_iterator p = begin(); p != end(); ++p)
    os << "- " << *p << endl;
  return os;
}

/* _________________________________________________________________________ */

istream& operator>>(istream& is, EventoHistorico& e)
{
  return e.cargarEvento(is);
}

/* _________________________________________________________________________ */

ostream& operator<<(ostream& os, const EventoHistorico& e)
{
  return e.mostrarEvento(os);
}

/* Fin fichero: evento_historico.cpp */
