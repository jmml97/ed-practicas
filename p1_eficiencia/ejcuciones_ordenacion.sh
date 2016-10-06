#!/bin/bash

INICIO=100
FIN=1000000
INCREMENTO=100

I=$INICIO

echo > tiempos.dat
while [[ $I -lt $FIN ]]; do
  echo Ejecución de tamaño $I
  echo `./busqueda_lineal $I 10000` >> tiempos.dat
  I=$(($I+$INCREMENTO))
done
