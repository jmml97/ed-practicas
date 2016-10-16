#!/bin/bash


match='\documentclass{minimal}'
insert='\usepackage[utf8]{inputenc}'
input=$1
path=$(pwd)/$input

cd ./gnuplot

gnuplot << EOF

set terminal epslatex standalone color colortext
set ylabel '{tiempo (s)}'
set xlabel '{tamaño del vector (elementos)}'
set output "tiempos_burbuja.tex"

plot "$path/tiempos_burbuja.dat" title 'Eficiencia empírica'

f(x) = (19/2)*x*x - (9/2)*x - 5

set output "tiempos_burbuja_teorica_superpuesta.tex"
plot "$path/tiempos_burbuja.dat" title 'Eficiencia empírica', f(x) title 'Eficiencia teórica'

f(x) = a*x*x + b*x + c
fit f(x) "$path/tiempos_burbuja.dat" via a, b, c
set output "tiempos_burbuja_ajustado.tex"
plot "$path/tiempos_burbuja.dat" title 'Eficiencia empírica', f(x) title 'Curva ajustada'

f(x) = a*x**b
fit f(x) "$path/tiempos_binaria.dat" via a, b
set output "tiempos_binaria.tex"
plot "$path/tiempos_binaria.dat" title 'Eficiencia empírica', f(x) title 'Eficiencia teórica'

set output "tiempos_burbuja_mejor_caso.tex"
plot "$path/tiempos_burbuja_mejor_caso.dat" title 'Mejor caso', "$path/tiempos_burbuja.dat" title 'Vector aleatorio'

set output "tiempos_burbuja_peor_caso.tex"
plot "$path/tiempos_burbuja_peor_caso.dat" title 'Peor caso', "$path/tiempos_burbuja.dat" title 'Vector aleatorio'

f(x) = a*x + b
fit f(x) "$path/tiempos_burbuja_optimizado.dat" via a, b
set output "tiempos_burbuja_optimizado.tex"
plot "$path/tiempos_burbuja_optimizado.dat" title 'Eficiencia empírica', f(x) title 'Eficiencia teórica'

EOF

gsed -i '/\documentclass{minimal}/a\\\usepackage[utf8]{inputenc}' tiempos_burbuja.tex
gsed -i '/\documentclass{minimal}/a\\\usepackage[utf8]{inputenc}' tiempos_burbuja_teorica_superpuesta.tex
gsed -i '/\documentclass{minimal}/a\\\usepackage[utf8]{inputenc}' tiempos_burbuja_ajustado.tex
gsed -i '/\documentclass{minimal}/a\\\usepackage[utf8]{inputenc}' tiempos_binaria.tex
gsed -i '/\documentclass{minimal}/a\\\usepackage[utf8]{inputenc}' tiempos_burbuja_mejor_caso.tex
gsed -i '/\documentclass{minimal}/a\\\usepackage[utf8]{inputenc}' tiempos_burbuja_peor_caso.tex
gsed -i '/\documentclass{minimal}/a\\\usepackage[utf8]{inputenc}' tiempos_burbuja_optimizado.tex

latex tiempos_burbuja.tex
latex tiempos_burbuja_teorica_superpuesta.tex
latex tiempos_burbuja_ajustado.tex
latex tiempos_binaria.tex
latex tiempos_burbuja_mejor_caso.tex
latex tiempos_burbuja_peor_caso.tex
latex tiempos_burbuja_optimizado.tex
dvipdf tiempos_burbuja.dvi
dvipdf tiempos_burbuja_teorica_superpuesta.dvi
dvipdf tiempos_burbuja_ajustado.dvi
dvipdf tiempos_binaria.dvi
dvipdf tiempos_burbuja_mejor_caso.dvi
dvipdf tiempos_burbuja_peor_caso.dvi
dvipdf tiempos_burbuja_optimizado.dvi

cp *.pdf ./../entrega/img
rm ./* .??*
