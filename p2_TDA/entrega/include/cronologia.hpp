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


/**
 * @brief T.D.A. Cronología
 *
 * blablabla
 *
 * Un ejemplo de su uso:
 * @include usoCronologia.cpp
 *
 * @author Miguel Lentisco Ballesteros
 * @author Jose María Martín Luque
 * @author Antonio Coín Castro
 * @date Octubre 2016
 *
 */
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
    Cronologia() {} // constructor vacío: no tiene ningún efecto
    Cronologia(const std::vector<EventoHistorico>& v);

    // Get & Set
    std::vector<EventoHistorico> getCronologia() const { return c; }
    EventoHistorico getEventoHistorico(Fecha f) const;  //pre: está en el vector
    std::vector<Acontecimiento> getAcontecimientos(Fecha f) const;  // pre: está en el vector
    void setCronologia(const std::vector<EventoHistorico>& v);
    void setEventoHistorico(const std::vector<Acontecimiento>& v, Fecha f); // pre: está en el vector
    void addEventoHistorico(const EventoHistorico& e); // mezcla; no quedan repetidos
    void addEventoHistorico(const std::vector<EventoHistorico>& v);   // mezcla; no quedan repetidos
    void mezclarCronologia(const Cronologia& cron);

    // Ver si hay un E.H. con la fecha determinada
    bool contieneFecha(Fecha f) const;

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
