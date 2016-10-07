#!/bin/bash
gnuplot << EOF

set terminal png size 1280,720 enhanced font 'Arial,10'
set ylabel '{/Arial-RegularItalic tiempo (s)}'
set xlabel '{/Arial-RegularItalic tamaño del vector}'
set output "./gráficos/$1.png"

plot "$1"

f(x) = a*x*x + b*x + c
fit f(x) "$1" via a, b, c
set output "./gráficos/$1_ajustado.png"
plot "$1", f(x)

EOF
