##ifndef __EVENTO_HISTORICO_HPP__
#define  __EVENTO_HISTORICO_HPP__

typedef int Fecha;
typedef Acontecimiento Acontecimiento;

class EventoHistorico
{
   private:
      Fecha f;
      std::vector<Acontecimiento> acontecimientos;

   public:
      EventoHistorico(): f(-1) {}
      EventoHistorico(Fecha f);
      EventoHistorico(Fecha f, std::vector<Acontecimiento> a);
   // EventoHistorico(EventoHistorico e);
   // EventoHistorico~() {}

   //   EventoHistorico& operator =(EventoHistorico e);

      Fecha getFecha() { return f; }
      Acontecimiento getEvento(int pos);
      std::vector<Acontecimiento> getEvento();
      void setFecha(Fecha f);
      void setEvento(std::vector<Acontecimiento> a);

      void addEvento(Acontecimiento a);
      void eliminarEvento(int pos);

      std::ostream& mostrarEvento(std::ostream& os);
      std::istream& cargarEvento(std::istream& is);
};

std::istream& operator >>(std::istream& is, EventoHistorico e);
std::ostream& operator <<(std::ostream& os, EventoHistorico e);

#endif
