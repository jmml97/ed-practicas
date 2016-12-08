

//// ANTIGUA IMPLEMENTACIÓN; MEJORAR Y PONER COMO FUNCIÓN EXTERNA
container_type Cronologia::buscarPorClave (const string& key) const
{
  container_type e;
  EventoHistorico tmp;
  for (container_type::const_iterator p = datos.begin(); p != datos.end(); ++p)
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
