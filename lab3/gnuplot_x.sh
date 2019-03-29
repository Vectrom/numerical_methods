set terminal jpeg enhanced font 20 
set output "x.jpg"
set xlabel 'k'
set ylabel '||x_{k}||_{2} = f(k)'
set xrange [1:]
plot 'result.dat' u 1:5 w p t '||x_{k}||_{2}', 'result.dat' u 1:5 w l t ''