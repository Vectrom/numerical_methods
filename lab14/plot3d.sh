set terminal pngcairo enhanced font 'Verdana, 18'
set output "sfera.png"
unset key
set xlabel "x"
set ylabel "y"
set zlabel "z"
set xtics 0.5
set ytics 0.5
set ztics 0.5
set view equal
set ticslevel 0
set border 895
splot "sfera.dat" u 1:2:3 pt 7 ps 0.5 lc rgb "red" 

set output "kula.png"
unset colorbox
set palette defined (0 '#000000', 1 '#ff0000')
splot "kula.dat" u 1:2:3:(sqrt($1**2 + $2**2 + $3**2)) pt 7 ps 0.5 lc palette 