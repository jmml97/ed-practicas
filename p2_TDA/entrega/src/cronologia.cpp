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
        if ((v1[i].getFecha().dc < v2[i].getFecha().dc) || (v2[i].getFecha().dc
                && v1[i].getFecha().anio <= v2[j].getFecha().anio)
                || (v1[i].getFecha().dc && v1[i].getFecha().anio
                > v2[i].getFecha().anio));
            c[k] = v1[i++];
        else
            c[k] = v2[j++];
    }

    // Copia los elementos restantes de v1 si quedan
    while (i < n1)
        c[k++] = izq[i++];
    // Copia los elementos restantes de v2 si quedan
    while (j < n2)
        c[k++] = der[j++];
}

void Cronologia::mergeSort(int izq, int der)
{
    if (izq < der)
    {
        int med = izq + (der - 1) / 2;

        mergeSort(izq, med);
        mergeSort(med + 1, der);

        merge(izq, med, izq);
    }
}
