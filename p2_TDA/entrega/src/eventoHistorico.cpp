#include <iostream>
#include <sstream>
#include <cassert>
#include "eventoHistorico.hpp"
using namespace std;

namespace {
  const char SEP = '#';
}

// Private
vector<Acontecimiento>::iterator EventoHistorico::buscarAcontecimiento(Acontecimiento a)
{
  bool encontrado = false;
  vector<Acontecimiento>::iterator p = evento.begin();
  while (p != evento.end() && !encontrado) {
    encontrado = *p == a;
    ++p;
  }
  if (encontrado) p--;
  return p;
}

// Constructores
EventoHistorico::EventoHistorico()
{
  f.anio = -1;
  f.dc = 1;
}

EventoHistorico::EventoHistorico(Fecha f)
{
  setFecha(f);
}

EventoHistorico::EventoHistorico(Fecha f, vector<Acontecimiento> a)
  : EventoHistorico(f)
{
  setEvento(a);
}

// Get & Set
void EventoHistorico::setFecha(Fecha f)
{
  assert(f.anio >= 0);
  this->f = f;
}

bool EventoHistorico::addEvento(Acontecimiento a)
{
  vector<Acontecimiento>::const_iterator p = buscarAcontecimiento(a);
  if (p == evento.end()) {
    evento.push_back(a);
    return true;
  }
  return false;
}

void EventoHistorico::addEvento(vector<Acontecimiento> a)
{
  for (vector<Acontecimiento>::iterator p = a.begin(); p != a.end(); ++p)
    addEvento(*p);
}

// Eliminar
bool EventoHistorico::eliminarAcontecimiento(Acontecimiento a)
{
  vector<Acontecimiento>::const_iterator p = buscarAcontecimiento(a);
  if (p != evento.end()) {
    evento.erase(p);
    return true;
  }
  return false;
}

int EventoHistorico::eliminarPorClave (string key)
{
  int n = 0;
  for (vector<Acontecimiento>::iterator p = evento.begin(); p != evento.end(); ++p) {
    if (p->find(key) != string::npos) {
      evento.erase(p);
      n++;
    }
  }
  return n;
}

// Búsqueda
vector<Acontecimiento> EventoHistorico::buscarPorClave (string key) const
{
  vector<Acontecimiento> a;
  for (vector<Acontecimiento>::const_iterator p = evento.begin(); p != evento.end(); ++p) {
    if (p->find(key) != string::npos)
      a.push_back(*p);
  }
  return a;
}

// E/S
istream& EventoHistorico::cargarEvento(istream& is)
{
  Fecha fecha;
  vector<Acontecimiento> a;
  string aux;

  getline(is, aux, SEP);
  fecha.dc = stoi(aux);
  getline(is, aux, SEP);
  fecha.anio = stoi(aux);

  getline(is, aux);   // coger el resto de la línea
  istringstream ss(aux);
  while (getline(ss, aux, SEP)) {
    a.push_back(aux);
  }

  if (is) {
    setFecha(fecha);
    setEvento(a);
  }

  return is;
}

ostream& EventoHistorico::mostrarEvento(ostream& os) const
{
  os << f.dc << SEP;
  os << f.anio << SEP;
  vector<Acontecimiento>::const_iterator p = evento.begin();

  // Escribir un evento
  if (p != evento.end()) {
    os << *p;

    for (++p; p != evento.end(); ++p)
      os << SEP << *p;  // No hay SEP al final
  }
  return os;
}

ostream& EventoHistorico::prettyPrint(ostream& os) const
{
  os << "Año: " << f.anio << (f.dc ? " DC." : " AC.") << endl;
  for (vector<Acontecimiento>::const_iterator p = evento.begin(); p != evento.end(); ++p)
    os << "- " << *p << endl;
  return os;
}

istream& operator>>(istream& is, EventoHistorico& e)
{
  return e.cargarEvento(is);
}

ostream& operator<<(ostream& os, const EventoHistorico& e)
{
  return e.mostrarEvento(os);
}

/* Fin fichero: eventoHistorico.cpp */
