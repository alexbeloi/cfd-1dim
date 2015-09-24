/*
 * C program to numerically simulate the time evolution of a solution to
 * advection differential equation u_t = k*u_x with initial conditions
 * u(x,0) = fun(x)
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * Define constants
 */
static double const k = -2; //fix k to be a constant for now
static double const rangex=2*M_PI; //domain of variable x
static int const n=100; //sets resolution for discretizing domain of x
static int const T=2000; //sets number of time step evolutions to perform (set 0 for infinite)
static double const L = 0.3; //stability constant, equal to k*dt/dx, we use this to define dt. For stability, require this to be (strictly?) less than 1

/*
 * Define linked list node, this will store cell value and also store how to
 * get to previous and next cell. *tracker will be used to keep track of
 * where we are in the list and *temp is a temporary node to shuffle data
 * with.
 */
struct node
{
  double value;
  struct node *prev;
  struct node *next;
}*temp,*tracker;

int i,j; //indexes
int x; //space variable
double store1,store2; //temporary storage
FILE *fp;

/* define initial condition u(x,0)=f(x); */
double fun(double x)
{
  return sin(x);
}

/* define time evolution function for entire list given root node */
void tevol(struct node *cell, double dx, double dt)
{
  tracker = cell;
  store1 = tracker->prev->value;
  for(j=0;j<n;j++)
  {
    store2 = tracker->value;
    /* update accordintg to u_x^{i+1} = u_x^i + k*(dt/dx)(u_x^i-u_{x-1}^i) */
    tracker->value = tracker->value + k*(dt/dx)*(tracker->value - store1);

    store1 = store2; //store cell value for future cells
    tracker = tracker->next;
  }
  cell->value=tracker->value; //hard enforce periodicity boundary condition
}

void dataout(struct node *cell, FILE *fp, double dx)
{
  tracker = cell; //set tracker to start node
  for(j=0;j<n;j++)
  {
    fprintf(fp,"%f  %f\n", (j+0.5)*dx,tracker->value);
    tracker = tracker->next;
  }
}


void main()
{
  double dx = rangex/n; //step size for x variable
  double dt = dx*L; //step size for t variable defined as a function of L & dx

  struct node *start;
  start = (struct node *) malloc(sizeof(struct node));
  tracker = start; //set tracker to keep initial node

  /* SETUP INITIAL CONDITIONS */

  start->value = fun(dx/2); //set value at first cell as value of initial condition at dx/2 (middle of first cell).

  for(i=1;i<n;i++)
  {
    /* create new node and attach it to (next) of previous node */
    tracker->next = (struct node *) malloc(sizeof(struct node));
    /* attach new node's prev to previous node */
    tracker->next->prev = tracker;
    /* give the appropriate value to cell */
    tracker->next->value = fun((i+0.5)*dx);
    /* update tracker to new node */
    tracker = tracker->next;
  }

  /* for periodic boundary conditions, usefull to have list wrap around */
  tracker->next = start;
  start->prev = tracker;

  // tracker = start;
  // for(i=0;i<n;i++)
  // {
  //   printf("node:%d \n value: %f \n prev: %p \n current: %p \n next: %p \n\n", i, tracker->value, tracker->prev, tracker, tracker->next);
  //   tracker=tracker->next;
  // }


  /* write data and evolve data until program is killed */
  fp = fopen("data.dat", "w");

  for(i=0;i<T;i++)
  {
    dataout(start,fp,dx);
    tevol(start,dx,dt);
  }
}
