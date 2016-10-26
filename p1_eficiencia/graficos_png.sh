#!/bin/bash

input=$1
path=$(pwd)/$input

cd ./gnuplot

gnuplot << EOF

set terminal png enhanced linewidth 2
set ylabel '{tiempo (s)}'
set xlabel '{tamaño del vector (elementos)}'
set output "tiempos_burbuja.png"

plot "$path/tiempos_burbuja.dat" title 'Eficiencia empírica'

f(x) = (19/2)*x*x - (9/2)*x - 5

set output "tiempos_burbuja_teorica_superpuesta.png"
plot "$path/tiempos_burbuja.dat" title 'Eficiencia empírica', f(x) title 'Eficiencia teórica'

f(x) = a*x*x + b*x + c
fit f(x) "$path/tiempos_burbuja.dat" via a, b, c
set output "tiempos_burbuja_ajustado.png"
plot "$path/tiempos_burbuja.dat" title 'Eficiencia empírica', f(x) title 'Curva ajustada'

f(x) = a*x**b
fit f(x) "$path/tiempos_binaria.dat" via a, b
set output "tiempos_binaria.png"
plot "$path/tiempos_binaria.dat" title 'Eficiencia empírica', f(x) title 'Eficiencia teórica'

set output "tiempos_burbuja_mejor_caso.png"
plot "$path/tiempos_burbuja_mejor_caso.dat" title 'Mejor caso', "$path/tiempos_burbuja.dat" title 'Vector aleatorio'

set output "tiempos_burbuja_peor_caso.png"
plot "$path/tiempos_burbuja_peor_caso.dat" title 'Peor caso', "$path/tiempos_burbuja.dat" title 'Vector aleatorio'

f(x) = a*x + b
fit f(x) "$path/tiempos_burbuja_optimizado.dat" via a, b
set output "tiempos_burbuja_optimizado.png"
plot "$path/tiempos_burbuja_optimizado.dat" title 'Eficiencia empírica', f(x) title 'Eficiencia teórica'

set output "tiempos_burbuja_opt_compilador.png"
plot "$path/tiempos_burbuja.dat" title 'Burbuja sin optimizar', "$path/tiempos_burbuja_opt_compilador.dat" title 'Burbuja con optimizaciones'

EOF
