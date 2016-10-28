/**
  * @file cronologia.hpp
  * @brief Fichero cabecera del TDA Cronologia
  *
  */

#ifndef __CRONOLOGIA_HPP__
#define  __CRONOLOGIA_HPP__

#include <iostream>
#include <vector>
#include "eventoHistorico.hpp"

class Cronologia
{
  private:
    std::vector<EventoHistorico> c;

    std::vector<EventoHistorico>::iterator busquedaBinaria(Fecha f);  // buscar evento en this->c

    // igual, pero devuelve iterador constante (es necesaria)
    std::vector<EventoHistorico>::const_iterator busquedaBinaria(Fecha f) const;
    void merge(int izq, int med, int der);  // mezclar vector
    void mergeSort(int izq, int der); // ordenar subvector
    void ordenar(); // ordenar vector completo por fecha

  public:
    Cronologia(std::vector<EventoHistorico> v); //pre: vector ordenado

    // Get & Set
    std::vector<EventoHistorico> getCronologia() const { return c; }
    EventoHistorico getEventoHistorico(Fecha f) const;  //pre: está en el vector
    void setCronologia(std::vector<EventoHistorico> v) { this->c = v; }
    bool addEventoHistorico(EventoHistorico e); // merge
    void addEventoHistorico(std::vector<EventoHistorico> v);   // merge
    void addCronologia(const Cronologia& cron);

    // Ver si hay un E.H. con la fecha determinada
    bool contieneFecha(Fecha f) const;  // (IMPLEMENTAR)

    // Eliminar
    bool eliminarEvento(Fecha f);  // elimina el que coincida
    int eliminarPorClave (std::string key);  // elimina todos los E.H que contengan 'key'; devuelve num eliminados

    // Buscar
    std::vector<EventoHistorico> buscarPorClave (std::string key) const; // busca los E.H. que contengan 'key'

    // E/S
    std::istream& cargarCronologia(std::istream& is);
    std::ostream& mostrarCronologia(std::ostream& os) const;
    std::ostream& mostrarCronologiaInversa(std::ostream& os) const;
    std::ostream& prettyPrint(std::ostream& os = std::cout) const;
};

// Operadores E/S
std::istream& operator>>(std::istream& is, Cronologia& cro);
std::ostream& operator<<(std::ostream& os, const Cronologia& cro);

#endif

/* Fin fichero: cronologia.hpp */
