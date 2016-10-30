/**
  * @file cronologia.cpp
  * @brief Implementación del TDA Cronologia
  *
  */

#include <iostream>
#include <vector>
#include <sstream>
#include <cassert>
#include <algorithm>
#include "cronologia.hpp"

using namespace std;

// Buscar un EventoHistorico por fecha
vector<EventoHistorico>::iterator Cronologia::busquedaBinaria(Fecha f)
{
    int med;
    int inf = 0;
    int sup = c.size() - 1;
    bool enc = false;

    while ((inf<sup) && (!enc))
    {
        med = (inf + sup) / 2;
        Fecha aux = c[med].getFecha();
        if (aux.anio == f.anio && aux.dc == f.dc)
            enc = true;
        else if ((aux.dc < f.dc) || (f.dc && aux.anio < f.anio)
                    || (!aux.dc && aux.anio > f.anio))
            inf = med + 1;
        else
            sup = med - 1;
    }

    if (enc)
        return c.begin() + med;
    else
        return c.end();
}

// Buscar un EventoHistorico por fecha, y devolver iterador constante
vector<EventoHistorico>::const_iterator Cronologia::busquedaBinaria(Fecha f) const
{
    int med;
    int inf = 0;
    int sup = c.size() - 1;
    bool enc = false;

    while ((inf<sup) && (!enc))
    {
        med = (inf + sup) / 2;
        Fecha aux = c[med].getFecha();
        if (aux.anio == f.anio && aux.dc == f.dc)
            enc = true;
        else if ((aux.dc < f.dc) || (f.dc && aux.anio < f.anio)
                    || (!aux.dc && aux.anio > f.anio))
            inf = med + 1;
        else
            sup = med - 1;
    }

    if (enc)
        return c.begin() + med;
    else
        return c.end();
}


// Ordenar vector this->c por fecha
void Cronologia::ordenar()
{
  std::sort(c.begin(), c.end(), eventoMasReciente);
}

// Constructor de clase
Cronologia::Cronologia(const vector<EventoHistorico>& v)
{
  setCronologia(v);
}

// Obtener el EventoHistorico correspondiente a la Fecha f
EventoHistorico Cronologia::getEventoHistorico(Fecha f) const
{
  assert(contieneFecha(f));
  vector<EventoHistorico>::const_iterator p = busquedaBinaria(f);
  return *p;
}

// Obtener los acontecimientos correspondientes a la fecha f
std::vector<Acontecimiento> Cronologia::getAcontecimientos(Fecha f) const
{
  return getEventoHistorico(f).getEvento();
}

// Modificar el vector this->c
void Cronologia::setCronologia(const std::vector<EventoHistorico>& v)
{
  this->c = v;
  ordenar();
}

// Modificar el evento histórico asociado a la fecha f
void Cronologia::setEventoHistorico(const vector<Acontecimiento>& v, Fecha f)
{
  getEventoHistorico(f).setEvento(v);
}

// Añadir un evento histórico a la cronología
void Cronologia::addEventoHistorico(const EventoHistorico& e)
{
  if (contieneFecha(e.getFecha()))
  {
    vector<EventoHistorico>::iterator p = busquedaBinaria(e.getFecha());
    p->addEvento(e.getEvento());
  }
  else
  {
    c.push_back(e);
    ordenar();
  }
}

// Añadir varios eventos históricos a la cronología
void Cronologia::addEventoHistorico(const std::vector<EventoHistorico>& v)
{
  for (vector<EventoHistorico>::const_iterator p = v.begin(); p != v.end(); ++p)
    addEventoHistorico(*p);
}

// Meclar la cronología con una dada
void Cronologia::mezclarCronologia(const Cronologia& cron)
{
  addEventoHistorico(cron.getCronologia());
}

// Ver si hay un evento histórico con la fecha dada
bool Cronologia::contieneFecha(Fecha f) const
{
  return busquedaBinaria(f) != c.end();
}

// Eliminar un EventoHistorico
bool Cronologia::eliminarEvento(Fecha f)
{
  vector<EventoHistorico>::iterator p = busquedaBinaria(f);
  if (p != c.end())
  {
    c.erase(p);
    return true;
  }
  return false;
}

// Eliminar todos los eventos históricos cuyos acontecimientos contengan 'key'
int Cronologia::eliminarPorClave (string key)
{
  int n = 0;
  vector<EventoHistorico>::const_iterator p = c.begin();
  while (p != c.end())
  {
    if (p->buscarPorClave(key).size() != 0)
    {
      c.erase(p);
      n++;
    }
    else
      ++p;
  }
  return n;
}

// Buscar todos los eventos históricos que contengan acontecimientos que contengan 'key'
vector<EventoHistorico> Cronologia::buscarPorClave (string key) const
{
  vector<EventoHistorico> e;
  EventoHistorico tmp;
  for (vector<EventoHistorico>::const_iterator p = c.begin(); p != c.end(); ++p)
  {
    vector<Acontecimiento> v;
    v = p->buscarPorClave(key);
    if (v.size() != 0)
    {
      tmp.setFecha(p->getFecha());
      tmp.setEvento(v);
      e.push_back(tmp);
    }
  }
  return e;
}

// Cargar Cronologia desde un flujo de entrada
istream& Cronologia::cargarCronologia(istream& is)
{
  EventoHistorico tmp;
  vector<EventoHistorico> v;
  string s;
  while(getline(is,s))
  {
    istringstream ss(s);
    tmp.cargarEvento(ss);
    v.push_back(tmp);
  }

  if (is.eof())
  {
    setCronologia(v);
    ordenar();
  }
  return is;
}

// Mostrar una Cronologia a un flujo de salida
ostream& Cronologia::mostrarCronologia(ostream& os) const
{
  for (vector<EventoHistorico>::const_iterator p = c.begin(); p != c.end(); ++p)
  {
    p->mostrarEvento(os);
    os << '\n';
  }
  return os;
}

// Mostrar una Cronologia en orden inverso a un flujo de salida
ostream& Cronologia::mostrarCronologiaInversa(ostream& os) const
{

  for (vector<EventoHistorico>::const_reverse_iterator p = c.rbegin(); p != c.rend(); ++p)
  {
    p->mostrarEvento(os);
    os << '\n';
  }
  return os;
}

// Mostrar una Cronologia en Human Readable Format
ostream& Cronologia::prettyPrint(ostream& os) const
{
  for (vector<EventoHistorico>::const_iterator p = c.begin(); p != c.end(); ++p)
  {
    p->prettyPrint();
    os << '\n';
  }
  return os;
}

// Operator>>
istream& operator>>(istream& is, Cronologia& cron)
{
  return cron.cargarCronologia(is);
}

// Operator<<
ostream& operator<<(ostream& os, const Cronologia& cron)
{
  return cron.mostrarCronologia(os);
}

/* Fin fichero: cronologia.cpp */
