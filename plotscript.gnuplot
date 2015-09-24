#plot data in data.dat, each 1000 lines denote one frame
reset
set term gif animate
set output "animate.gif"
T = 200 #number of frames
n = 100 #resolution of x-axis
dt = 2*pi/T
set xrange [0:2*pi]
set yrange [-1:1]
i=0
load "animate.gnuplot"
set output
