set terminal png
set output 'data/results.png'
plot 'data/original.log' using 0:2 title 'pitch-orig' with lines, 'data/original.log' using 0:3 title 'roll-orig' with lines, 'data/improved.log' using 0:2 title 'pitch-improved-1' with lines, 'data/improved.log' using 0:3 title 'roll-improved-1' with lines
quit
