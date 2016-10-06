#!/bin/bash
gnuplot << EOF

set terminal png size 1280,720 enhanced font 'Arial,10'
set ylabel '{/AtlasGrotesk-RegularItalic tiempo (s)}'
set xlabel '{/AtlasGrotesk-RegularItalic tamaño del vector}'
set output "$1.png"

plot "$1"
EOF
