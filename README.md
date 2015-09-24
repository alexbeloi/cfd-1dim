# cfd-1dim
Code to play around with and test different computational fluid dynamics schemes on the one dimensional advection equation.

The fluid dynamics computations are written in C. The visualization is done using gnuplot to generate either a gif or mpeg animation.

### Current Status
Project has achieved all that was set out for it. There are no plans to expand on the current implementation. A related project ([distributed-cfd](https://github.com/alexbeloi/distributed-cfd)) was started to parrallelize the fluid dynamics computation across a networked cluster.

### Usage
Complie the C
```
$ gcc cfd1.c -lm

```
The above line will compute and write the plot data to `data.dat`, seen below.
```
$ cat data.dat | tail
5.686283  -0.207060
5.749115  -0.186059
5.811946  -0.164324
5.874778  -0.141941
5.937610  -0.118997
6.000442  -0.095584
6.063274  -0.071793
6.126106  -0.047719
6.188938  -0.023457
6.251769  0.000898
```
Now you may use the data however you like. We've included a couple of methods of visualizing the data using gnuplot.

To generated an animated gif of the plotted data run
```
$ gnuplot plotscript.gnuplot
End of animation sequence
```
This will creat the following file `animate.gif`
![animate.gif](http://i.imgur.com/VwUWzsQ.gif 'animate.gif')

Alternatively, if you wish to generate an mpeg file then you can running the included script (note that the script will compile and run the C code again). This requires ffmpeg to be installed.
```
$ ./plotdata.sh
```
### Notes

The C code uses a linked list implementation and the differential equation has periodic boundary conditions by default. This allows for a uniform treatment of each computational cell.
