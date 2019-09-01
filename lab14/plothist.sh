set terminal pngcairo enhanced font 'Verdana, 10'
set encoding utf8

# Line styles (colorbrewer Set1)
set style line 1 lc rgb '#E41A1C' pt 7 ps 0.5 lt 1 lw 2 # red
set style line 2 lc rgb '#377EB8' pt 7 ps 0.5 lt 1 lw 2 # blue
set style line 3 lc rgb '#4DAF4A' pt 7 ps 0.5 lt 1 lw 2 # green
set style line 4 lc rgb '#984EA3' pt 3 ps 1 lt 1 lw 2 # purple
set style line 5 lc rgb '#FF7F00' pt 4 ps 1 lt 1 lw 2 # orange
set style line 6 lc rgb '#FFFF33' pt 5 ps 1 lt 1 lw 2 # yellow
set style line 7 lc rgb '#A65628' pt 7 ps 1 lt 1 lw 2 # brown
set style line 8 lc rgb '#F781BF' pt 8 ps 1 lt 1 lw 2 # pink

# Palette
set palette maxcolors 8
set palette defined ( 0 '#E41A1C', 1 '#377EB8', 2 '#4DAF4A', 3 '#984EA3',\
4 '#FF7F00', 5 '#FFFF33', 6 '#A65628', 7 '#F781BF' )

# Standard border
set style line 11 lc rgb '#808080' lt 1 lw 3
set tics out nomirror

# Standard grid
set style line 12 lc rgb '#808080' lt 0 lw 1
set grid back ls 12

set output "hist1.png"
set xlabel "j" 
set ylabel "n_j, g_j"
set key above

plot "nj1.dat" u 1:2 w boxes fs pattern 1 t "n_j", "gj1.dat" u 1:2 w boxes fs fill empty t "g_j"