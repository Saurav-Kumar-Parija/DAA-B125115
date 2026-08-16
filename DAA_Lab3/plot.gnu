set datafile separator ','
set title 'Binary Search vs Ternary Search'
set xlabel 'Input Size (N)'
set ylabel 'Number of Key Comparisons'
set grid
set key left top
set terminal pngcairo size 1000,700
set output 'search_comparison.png'
plot 'search_comps.csv' using 1:2 with linespoints title 'Binary Search' lw 2 pt 7, 'search_comps.csv' using 1:3 with linespoints title 'Ternary Search' lw 2 pt 5
