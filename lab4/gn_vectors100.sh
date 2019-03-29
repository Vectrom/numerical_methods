set term png 
set out "vectors100.png"
set xlabel "x"
set ylabel "u(x)"

plot 'vectors100.dat' u 1:2 w l t 'u_1(x)' ,\
			 '' u 1:3 w l t 'u_2(x)' ,\
		     '' u 1:4 w l t 'u_3(x)' ,\
			 '' u 1:5 w l t 'u_4(x)' ,\
			 '' u 1:6 w l t 'u_5(x)' ,\
			 '' u 1:7 w l t 'u_6(x)'

