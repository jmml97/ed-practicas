#!/bin/bash

filename=$(basename "$1")
filename="${filename%.*}"
match='\documentclass{minimal}'
insert='\usepackage[utf8]{inputenc}'

cp $1 ./gnuplot/

cd ./gnuplot

gnuplot << EOF

set terminal epslatex standalone color colortext
set ylabel '{tiempo (s)}'
set xlabel '{tamaño del vector (elementos)}'
set output "$filename.tex"

plot "$filename.dat" title 'eficiencia empírica'

f(x) = (19/2)*x*x - (9/2)*x - 5

set output "$filename\_teorica_superpuesta.tex"
plot "$filename.dat" title 'eficiencia empírica', f(x) title 'eficiencia teórica'

f(x) = a*x*x + b*x + c
fit f(x) "$filename.dat" via a, b, c
set output "$filename\_ajustado.tex"
plot "$filename.dat" title 'eficiencia empírica', f(x) title 'curva ajustada'

EOF

gsed -i '/\documentclass{minimal}/a\\\usepackage[utf8]{inputenc}' $filename.tex
gsed -i '/\documentclass{minimal}/a\\\usepackage[utf8]{inputenc}' $filename\_teorica_superpuesta.tex
gsed -i '/\documentclass{minimal}/a\\\usepackage[utf8]{inputenc}' $filename\_ajustado.tex

latex $filename.tex
latex $filename\_teorica_superpuesta.tex
latex $filename\_ajustado.tex
dvipdf $filename.dvi
dvipdf $filename\_teorica_superpuesta.dvi
dvipdf $filename\_ajustado.dvi

cp *.pdf ./../entrega/img
rm ./*
