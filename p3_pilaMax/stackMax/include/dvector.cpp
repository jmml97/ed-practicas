/**
 * @file dvector.cpp
 * @brief Implementación del T.D.A. DVector
 *
 */

// No se incluye el .hpp
#include <iostream>
using namespace std;

template <class T>
DVector<T>::DVector(int size, T d)
{
  n = reserved = size;

  data = new T[size];

  for (int i = 0; i < n; i++)
    data[i] = d;
}

template <class T>
DVector<T>::DVector(const DVector& v)
{
  data = new T[v.n];
  n = reserved = v.n;

  for (int i = 0; i < n; i++)
    data[i] = v.data[i];
}

template <class T>
void DVector<T>::swap(DVector& v)
{
  T *d = data;
  data = v.data;
  v.data = d;

  int i = n;
  n = v.n;
  v.n = i;

  i = reserved;
  reserved = v.reserved;
  v.reserved = i;

}

template <class T>
DVector<T>& DVector<T>::operator=(const DVector& v)
{
  DVector tmp(v);
  swap(tmp);

  return *this;
}

template <class T>
void DVector<T>::clear()
{
  delete[] data;
  n = reserved = 0;
}

template <class T>
void DVector<T>::reserve(int size)
{
  if (size > reserved) {
    T *aux = new T[size];

    for (int i = 0; i < n; i++)
      aux[i] = data[i];

    delete[] data;
    data = aux;
    reserved = size;
  }
}

template <class T>
void DVector<T>::resize(int nsize)
{
  reserve(nsize);
  n = nsize;
}

template <class T>
void DVector<T>::push_back(T d)
{
  if (n == reserved) {
    if (n == 0)
      reserve(1);
    else
      reserve(2*n);
  }

  data[n] = d;
  n++;
}

template <class T>
void DVector<T>::shrink_to_fit()
{
  DVector tmp(*this);
  swap(aux);
}

/* Fin fichero: dvector.cpp */
