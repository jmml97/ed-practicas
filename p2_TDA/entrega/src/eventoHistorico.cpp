/**
  * @file eventoHistorico.cpp
  * @brief Implementación del TDA EventoHistorico
  *
  */

#include <iostream>
#include <sstream>
#include <cassert>
#include "eventoHistorico.hpp"

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

// Método privado: buscar un Acontecimiento
vector<Acontecimiento>::iterator EventoHistorico::buscarAcontecimiento(Acontecimiento a)
{
  bool encontrado = false;
  vector<Acontecimiento>::iterator p = evento.begin();
  while (p != evento.end() && !encontrado)
  {
    encontrado = *p == a;
    ++p;
  }
  if (encontrado) p--;
  return p;
}

// Constructor por defecto
EventoHistorico::EventoHistorico() : f(1) {}

// Constructor con un parámetro
EventoHistorico::EventoHistorico(Fecha f)
{
  setFecha(f);
}

// Constructor con dos parámetros
EventoHistorico::EventoHistorico(Fecha f, vector<Acontecimiento> a)
  : EventoHistorico(f)
{
  setEvento(a);
}

// Modificar fecha
void EventoHistorico::setFecha(Fecha f)
{
  assert(f.anio >= 0);
  this->f = f;
}

// Añadir acontecimiento
bool EventoHistorico::addEvento(Acontecimiento a)
{
  vector<Acontecimiento>::const_iterator p = buscarAcontecimiento(a);
  if (p == evento.end())
  {
    evento.push_back(a);
    return true;
  }
  return false;
}

// Mezclar Acontecimientos
void EventoHistorico::addEvento(vector<Acontecimiento> a)
{
  for (vector<Acontecimiento>::iterator p = a.begin(); p != a.end(); ++p)
    addEvento(*p);
}

// Eliminar acoontecimiento
bool EventoHistorico::eliminarAcontecimiento(Acontecimiento a)
{
  vector<Acontecimiento>::const_iterator p = buscarAcontecimiento(a);
  if (p != evento.end())
  {
    evento.erase(p);
    return true;
  }
  return false;
}

// Eliminar todos los acontecimientos que contengan "key"
int EventoHistorico::eliminarPorClave (string key)
{
  int n = 0;
  vector<Acontecimiento>::iterator p = evento.begin();
  while (p != evento.end())
  {
    if ((p->find(key)) != string::npos)
    {
      evento.erase(p);
      n++;
    }
    else
      ++p;
  }
  return n;
}

// Buscar todos los acontecimientos que contengan "key"
vector<Acontecimiento> EventoHistorico::buscarPorClave (string key) const
{

  vector<Acontecimiento> a;
  for (vector<Acontecimiento>::const_iterator p = evento.begin(); p != evento.end(); ++p)
    if (p->find(key) != string::npos)
      a.push_back(*p);
  return a;
}

// Cargar EventoHistorico desde un flujo de entrada
istream& EventoHistorico::cargarEvento(istream& is)
{
  Fecha fecha;
  vector<Acontecimiento> a;
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
    a.push_back(aux);
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
  os << f.dc << SEP;
  os << f.anio << SEP;
  vector<Acontecimiento>::const_iterator p = evento.begin();

  // Escribir un evento
  if (p != evento.end())
  {
    os << *p;

    for (++p; p != evento.end(); ++p)
      os << SEP << *p;  // No hay SEP al final
  }
  return os;
}

// Mostar un EventoHistorico en Human Readable Format
ostream& EventoHistorico::prettyPrint(ostream& os) const
{
  os << "Año: " << f.anio << (f.dc ? " DC." : " AC.") << endl;
  for (vector<Acontecimiento>::const_iterator p = evento.begin(); p != evento.end(); ++p)
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

/* Fin fichero: eventoHistorico.cpp */
