set terminal pngcairo enhanced colour solid font '25'
 
g(x, y) = x**2 - 4.*x + y**2 -4.*y + x*y

set xrange [-10:10]
set yrange [-10:10]
set isosample 250, 250
set table "mapa.dat"
splot g(x,y)
unset table
reset

set xrange [-10:10]
set yrange [-10:10]
set table "kontur.dat"
set contour
unset surface
set view map
set isosamples 100
set cntrparam levels 50
splot g(x,y) 
unset table
reset

set output "g.png"
set key outside top center
set xlabel "x"
set ylabel "y"
set cblabel "g(x,y)" rotate by -90
set cbtics offset -0.6, 0
set xrange [-10:10]
set yrange [-10:10]
set xtics out
set ytics out
set size ratio -1
set palette rgbformulae 33,13,10
plot "mapa.dat" with image notitle,  "kontur.dat" u 1:2 w l lt -1 notitle, \
"-" w points lc rgb "red" lw 2 pt 1 ps 3 t "x_{min}, y_{min}"
1.333 1.333 
e
