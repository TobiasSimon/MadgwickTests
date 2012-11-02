#!/bin/sh

./test 0 > data/original.log
./test 1 > data/improved.log
gnuplot < eval.gnuplot
echo "wrote results to data directory"
