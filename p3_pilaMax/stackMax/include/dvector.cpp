/**
 * @file dvector.cpp
 * @brief Implementación del T.D.A. DVector
 *
 */

template <class T>
DVector<T>::DVector(int size, T d)
{
  n = reserved = size;
  data = new T[n];

  for (int i = 0; i < n; i++)
    data[i] = d;
}

/* _________________________________________________________________________ */

template <class T>
DVector<T>::DVector(const DVector<T>& v)
{
  n = reserved = v.n;
  data = new T[n];

  for (int i = 0; i < n; i++)
    data[i] = v.data[i];
}

/* _________________________________________________________________________ */

template <class T>
DVector<T>& DVector<T>::operator=(const DVector<T>& v)
{
  DVector aux(v);
  swap(aux);

  return *this;
}

/* _________________________________________________________________________ */

template <class T>
void DVector<T>::push_back(T d)
{
  if (n == reserved)
  {
    if (n == 0)
      reserve(1);
    else
      reserve(2*n);
  }
  data[n++] = d;
}

/* _________________________________________________________________________ */

template <class T>
void DVector<T>::reserve(int size)
{
  if (size > reserved)
  {
    T* aux = new T[size];

    for (int i = 0; i < n; i++)
      aux[i] = data[i];

    delete[] data;
    data = aux;
    reserved = size;
  }
}

/* _________________________________________________________________________ */

template <class T>
void DVector<T>::shrink()
{
  assert(n <= reserved/2);
  reserved = reserved/2;
  T* ndata = new T[reserved];

  for (int i = 0; i < n; i++)
    ndata[i] = data[i];

  delete[] data;
  data = ndata;
}

/* _________________________________________________________________________ */

template <class T>
void DVector<T>::resize(int nsize)
{
  reserve(nsize);
  n = nsize;
}

/* _________________________________________________________________________ */

template <class T>
void DVector<T>::shrink_to_fit()
{
  DVector aux(*this);
  swap(aux);
}

/* _________________________________________________________________________ */

template <class T>
void DVector<T>::clear()
{
  delete[] data;
  data = 0;
  n = reserved = 0;
}

/* _________________________________________________________________________ */

template <class T>
void DVector<T>::swap(DVector& v)
{
  T* d = data;
  data = v.data;
  v.data = d;

  int i = n;
  n = v.n;
  v.n = i;

  i = reserved;
  reserved = v.reserved;
  v.reserved = i;
}

/* _________________________________________________________________________ */

/* Fin fichero: dvector.cpp */
