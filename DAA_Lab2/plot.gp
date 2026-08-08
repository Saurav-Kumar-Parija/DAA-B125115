set terminal png size 1000,800
set output 'merge_comp.png'
set datafile separator ','
set title 'Merge Sort vs Modified Merge Sort'
set xlabel 'Input Size (N)'
set ylabel 'Execution Time (seconds)'
set grid
set key top left
set terminal qt
plot 'output.csv' using 1:2 with linespoints lw 2 pt 7 title 'Merge Sort',\
     'output.csv' using 1:3 with linespoints lw 2 pt 5 title 'Modified Merge Sort'
pause -1
