#!/bin/bash

INICIO=100
FIN=30000
INCREMENTO=500

I=$INICIO

filename=$(basename "$1")
filename="${filename%.*}"

echo > ./datos/tiempos_$filename.dat
while [[ $I -lt $FIN ]]; do
  echo Ejecución de tamaño $I
  echo `./$1 $I 30000` >> ./datos/tiempos_$filename.dat
  I=$(($I+$INCREMENTO))
done
