plot 'data.dat' every ::0+n*i::n-1+n*i w l title sprintf("u_t+2u_x=0\n n=100, dx = 0.062, dt = 0.0188\n t=%i",i)
i=i+1
if (i<T) reread
