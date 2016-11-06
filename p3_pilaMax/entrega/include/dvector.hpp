/**
 * @file dvector.hpp
 * @brief Fichero de cabecera del T.D.A. DVector
 *
 */

#ifndef __DVECTOR_HPP__
#define __DVECTOR_HPP__

/**
 * @brief T.D.A. DVector
 *
 */

template <class T>
class DVector {
  private:
    T* data;
    int n;
    int reserved;
  public:
    DVector() : data(0), n(0), reserved(0) {}
    // ...
};

#include "dvector.cpp"

#endif

/* Fin fichero: dvector.hpp */
