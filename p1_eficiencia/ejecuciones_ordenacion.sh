#!/bin/bash

INICIO=100
FIN=1000000
INCREMENTO=100

I=$INICIO

echo > tiempos_ordenacion.dat
while [[ $I -lt $FIN ]]; do
  echo Ejecución de tamaño $I
  echo `./bin/ordenacion $I 10000` >> tiempos_ordenacion.dat
  I=$(($I+$INCREMENTO))
done
