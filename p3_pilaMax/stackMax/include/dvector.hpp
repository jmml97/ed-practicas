/**
 * @file dvector.hpp
 * @brief Fichero de cabecera del T.D.A. DVector
 *
 * Gestiona un vector dinámico con funciones para la inserción
 * y el borrado de elementos así como para ampliar el vector.
 *
 * Un ejemplo de su uso puede consultarse en:
 * @example test_dvector.cpp
 *
 */

#ifndef __DVECTOR_HPP__
#define __DVECTOR_HPP__

/**
 * @brief T.D.A. DVector
 *
 */

template <class T>
class DVector
{
  private:
    T* data;
    int n;
    int reserved;

  public:
    DVector() : data(0), n(0), reserved(0) {}
    DVector(int size, T d = 0);
    DVector(const DVector& v);
    ~DVector() {delete[] data;}
    DVector& operator= (const DVector& v);
    void set(int i, T d) {data[i] = d;}
    T get(int i) const {return data[i];}
    int size() const {return n;}
    void resize(int nsize);
    void swap(DVector& v);
    void push_back(T d);
    void reserve(int size);
    int capacity() const {return reserved;}

};

#include "dvector.cpp"

#endif

/* Fin fichero: dvector.hpp */
