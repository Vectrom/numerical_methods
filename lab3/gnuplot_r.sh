set terminal jpeg enhanced font 20 
set output "r.jpg"
set xlabel "k"
set ylabel "||r_{k}||_{2} = f(k)"
set logscale y
plot 'result.dat' u 1:2 w p t '||r_{k}||_{2}','' u 1:2 w l t ''