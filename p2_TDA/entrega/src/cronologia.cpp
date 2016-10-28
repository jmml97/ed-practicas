#include <iostream>
#include <vector>
#include "cronologia.hpp"
using namespace std;

vector<EventoHistorico>::iterator busquedaBinaria(Fecha f)
{
    int med;
    int inf = 0;
    int sup = c.size() - 1;
    bool enc = false;

    while ((inf<sup) && (!enc))
    {
        med = (inf + sup) / 2;
        Fecha aux = v[med].getFecha();
        if (aux.anio == f.anio && aux.dc == f.dc)
            enc = true;
        else if ((aux.dc < f.dc) || (f.dc && aux.anio < f.anio)
                    || (!aux.dc && aux.anio > f.anio))
            inf = med + 1;
        else
            sup = med - 1;
    }

    if (enc)
        return v.at(med);
    else
        return c.end();
}

void Cronologia::merge(int izq, int med, int der)
{
    int i, j, k;
    int n1 = med - izq + 1;
    int n2 = der - med;

    // Vectores temporales
    vector<EventoHistorico> v1, v2;
    v1.resize(n1);
    v2.resize(n2);

    // Copia la los datos en vectores temporales
    for (i = 0; i < n1; i++)
        v1[i] = c[izq + i];
    for (i = 0; j < n2; j++)
        v2[i] = c[med + 1 + i];

    // Mezcla los vectores temporales en el array original
    for (i = 0, j = 0, k = 1; i < n1 && j < n2; k++)
    {
        Fecha f1 = v1[i].getFecha();
        Fecha f2 = v2[i].getFecha();
        if ((f1.dc < f2.dc) || (f2.dc && f1.anio <= f2.anio)
                || (f1.dc && f1.anio >= f2.anio));
            c[k] = v1[i++];
        else
            c[k] = v2[j++];
    }

    // Copia los elementos restantes de v1 si quedan
    while (i < n1)
        c[k++] = v1[i++];
    // Copia los elementos restantes de v2 si quedan
    while (j < n2)
        c[k++] = v2[j++];
}

void Cronologia::mergeSort(int izq = 0, int der = c.size() - 1)
{
    if (izq < der)
    {
        int med = izq + (der - 1) / 2;

        mergeSort(izq, med);
        mergeSort(med + 1, der);

        merge(izq, med, der);
    }
}
