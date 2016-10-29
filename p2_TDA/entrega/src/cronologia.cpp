/**
  * @file eventoHistorico.cpp
  * @brief Implementación del TDA EventoHistorico
  *
  */

#include <iostream>
#include <vector>
#include <cassert>
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

// Mezclar vectores
void Cronologia::merge(int izq, int med, int der)
{
    int i, j, k;
    int n1 = med - izq + 1;
    int n2 = der - med;

    // Vectores temporales
    vector<EventoHistorico> v1, v2;
    v1.resize(n1);
    v2.resize(n2);

    // Copia la los datos en vectores temporales
    for (i = 0; i < n1; i++)
        v1[i] = c[izq + i];
    for (j = 0; j < n2; j++)
        v2[i] = c[med + 1 + i];

    // Mezcla los vectores temporales en el array original
    for (i = 0, j = 0, k = 1; i < n1 && j < n2; k++)
    {
        Fecha f1 = v1[i].getFecha();
        Fecha f2 = v2[i].getFecha();
        if ((f1.dc < f2.dc) || (f2.dc && f1.anio <= f2.anio)
                || (f1.dc && f1.anio >= f2.anio))
            c[k] = v1[i++];
        else
            c[k] = v2[j++];
    }

    // Copia los elementos restantes de v1 si quedan
    while (i < n1)
        c[k++] = v1[i++];
    // Copia los elementos restantes de v2 si quedan
    while (j < n2)
        c[k++] = v2[j++];
}

// Ordenar un subvector
void Cronologia::mergeSort(int izq, int der)
{
    if (izq < der)
    {
        int med = izq + (der - 1) / 2;

        mergeSort(izq, med);
        mergeSort(med + 1, der);

        merge(izq, med, der);
    }
}

// Ordenar vector this->c por fecha
void Cronologia::ordenar()
{
  mergeSort(0, c.size() - 1);
}

// Obtener el EventoHistorico correspondiente a la Fecha f
EventoHistorico Cronologia::getEventoHistorico(Fecha f) const
{
  assert(contieneFecha(f));
  vector<EventoHistorico>::const_iterator p = busquedaBinaria(f);
  return *p;
}

bool Cronologia::addEventoHistorico(EventoHistorico e)
{
  c.push_back(e);
  ordenar();
}

void Cronologia::addEventoHistorico(std::vector<EventoHistorico> v)
{
  c.insert(c.end(), v.begin(), v.end());
  ordenar();
}

void Cronologia::addCronologia(const Cronologia& cron)
{
  c.insert(c.end(), cron.c.begin(), cron.c.end());
  ordenar();
}

bool Cronologia::contieneFecha(Fecha f) const
{
  bool encontrado = false;
  for (vector<EventoHistorico>::const_iterator p = c.begin(); p != c.end(); ++p)
  {
    encontrado = p->getFecha().anio == f.anio && p->getFecha().dc == f.dc;
  }

  return encontrado;
}

// Cargar Cronologia desde un flujo de entrada
istream& Cronologia::cargarCronologia(istream& is)
{
  EventoHistorico tmp;
  vector<EventoHistorico> v;
  while(is)
  {
    tmp.cargarEvento(is);
    v.push_back(tmp);
  }

  if (is)
  {
    setCronologia(v);
  }

  ordenar();

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
