set terminal png enhanced
set encoding utf8
set output  "result.png"
set ylabel 'ω(α)'
set xlabel 'α'
set yrange [0:0.2]
plot 'result.dat' u 1:2 w l t 'ω_{1}' ,\
			 '' u 1:3 w l t 'ω_{2}' ,\
		     '' u 1:4 w l t 'ω_{3}' ,\
			 '' u 1:5 w l t 'ω_{4}' ,\
			 '' u 1:6 w l t 'ω_{5}' ,\
			 '' u 1:7 w l t 'ω_{6}'
