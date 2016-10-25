#ifndef  __EVENTO_HISTORICO_HPP__
#define  __EVENTO_HISTORICO_HPP__

#include <iostream>
#include <vector>

struct Fecha {
  int anio;
  bool dc;  // AC / DC
};

typedef std::string Acontecimiento;

class EventoHistorico {
   private:
      Fecha f;
      std::vector<Acontecimiento> evento;

      std::vector<Acontecimiento>::const_iterator buscarAcontecimiento(Acontecimiento a) const;
   public:
      // Constructores
      EventoHistorico();
      EventoHistorico(Fecha f);
      EventoHistorico(Fecha f, std::vector<Acontecimiento> a);

      // EventoHistorico(EventoHistorico e);
      // EventoHistorico~() {}
      // EventoHistorico& operator=(EventoHistorico e);

      // Get & Set
      Fecha getFecha() const { return f; }
      std::vector<Acontecimiento> getEvento() const { return evento; }
      void setFecha(Fecha f); // machaca fecha
      void setEvento(std::vector<Acontecimiento> a) { this->evento = a; }
      bool addEvento(Acontecimiento a); //devuelve si se ha añadido
      void addEvento(std::vector<Acontecimiento> a);  // unión de eventos

      // Eliminar
      bool eliminarAcontecimiento(Acontecimiento a);  // elimina el que coincida
      int eliminarPorClave (std::string key);  // elimina todos los que contengan 'key'; devuelve num eliminados

      // Búsqueda
      std::vector<Acontecimiento> buscarPorClave (std::string key) const; // busca los que contengan 'key'

      // E/S
      std::istream& cargarEvento(std::istream& is);
      std::ostream& mostrarEvento(std::ostream& os) const;
      std::ostream& prettyPrint(std::ostream& os = std::cout) const;
};

std::istream& operator>>(std::istream& is, EventoHistorico& e);
std::ostream& operator<<(std::ostream& os, const EventoHistorico& e);

#endif

/* Fin fichero: eventoHistorico.hpp */
