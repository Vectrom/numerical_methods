set terminal jpeg enhanced font 20 solid 
set output "x_t.jpg"
set title "Wychylenie x(t)" 
set xlabel "t" 
set ylabel "x(t)"
set grid
plot "result.dat" w p t "x(t), dt = 0.1", cos(x) w l t "cos(t)"
