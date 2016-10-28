#ifndef __CRONOLOGIA_HPP__
#define  __CRONOLOGIA_HPP__

#include <iostream>
#include <vector>
#include "eventoHistorico.hpp"

class Cronologia
{
  private:
    std::vector<EventoHistorico> c;

    // ordenar por fecha
    std::vector<EventoHistorico>::iterator busquedaBinaria(Fecha f);
    void merge(int izq, int med, int der);
    void mergeSort(int izq, int der);
    void ordenar() {mergeSort(0, c.size() - 1);}

  public:
    Cronologia(std::vector<EventoHistorico> v); //pre: vector ordenado

    // Get & Set

    std::vector<EventoHistorico> getCronologia() const { return c; }
    EventoHistorico getEventoHistorico(Fecha f) const;
    void setCronologia(std::vector<EventoHistorico> v) { this->c = v; }
    bool addEventoHistorico(EventoHistorico e); // merge
    void addEventoHistorico(std::vector<EventoHistorico> v);   // merge

    // Eliminar (CAMBIAR NOMBRES Y PARÁMETROS)
    bool eliminarAcontecimiento(Acontecimiento a);  // elimina el que coincida
    int eliminarPorClave (std::string key);  // elimina todos los que contengan 'key'; devuelve num eliminados

    // Búsqueda (CAMBIAR NOMBRES Y PARÁMETROS)
    std::vector<Acontecimiento> buscarPorClave (std::string key) const; // busca los que contengan 'key'

    std::istream& cargarCronologia(std::istream& is);
    std::ostream& mostrarCronologia(std::ostream& os) const;
    std::ostream& mostrarCronologiaInversa(std::ostream& os) const;
    std::ostream& prettyPrint(std::ostream& os = std::cout) const;
};

// E/S
std::istream& operator>>(std::istream& is, Cronologia& cro);
std::ostream& operator<<(std::ostream& os, const Cronologia& cro);

#endif
