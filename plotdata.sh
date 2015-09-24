#!/bin/bash
gcc cfd1.c -lm
./a.out
for i in {1..1000}
do
	gnuplot -persist -e "set terminal jpeg; set xrange [0:2*3.14159]; set yrange [-1:1]; plot 'data.dat' every ::0+1000*$i::999+1000*$i w l" > ./frames/pic$i.jpeg
done

yes | ffmpeg -i ./frames/pic%d.jpeg -r 60 -b:v 512k movie.mpeg 
