# FYS3150-Project1

Project 1 FYS3150
Tiril Sørum Gransjøen 

The code written to answer the problems in this project, can be viewed and copied in the GitHub repo [link to GitHub repo]. 

Problem 1
We can easily check what the exact solution to our one-dimensional Poisson equation is, by rewriting our expression -(d^2 u)/(dx^2 )=f(x) where f(x)=100e^(-10x), x ϵ [0 ,1] and we have the boundary conditions u(0)=0 and u(1)=0. 
(d^2 u)/(dx^2 )=-f(x)=-100e^(-10x)   →  du/dx=(-100)/(-10) e^(-10x)+C=10e^(-10x)+C
u(x)=∫▒(10e^(-10x)+C)  dx=∫▒〖10e^(-10x) 〗 dx+∫▒C dx=-e^(-10x)+D+Cx
When taking the boundary conditions into consideration, we get the expression:
u(0)=-e^0+D+0=0   
-1+D=0  →  D=1
u(1)=-e^(-10)+D+C
-e^(-10)+1+C=0  →  C=e^(-10)-1
This gives us the exact solution:
u(x)=-e^(-10x)+1+(e^(-10)-1)x
which equates directly to the equation (1) from the assignment text.











Problem 2
We write our program that calculates the exact solutions to a number of x-values, and presents them in a text file in c++ (maketxt function). Thereafter we open a python-file, and write the code that imports this text file, and plots the exact solution for us (filename exact_plot.py). The plot is saved as a .pdf file Problem2plot.pdf by the program. 
 
Figure 1: Plot of the exact solution for x-values in the interval 0-1 with varying amounts of steps in between. Result of code from the python file exact_plot.py. Can be found as filename Problem2plot.pdf if code is run.


Problem 3
We know that the one-dimensional Poisson equation only is defined by our equation within the interval x ϵ [0 ,1]. We discretize this domain into a set amount of points by deciding a step size between each step, for example ∆x=0.01 like we did in our code solving Problem 2. We can, since the interval starts at x=0, express each x-value in this range x ϵ [0 ,1] as x_i=i*∆x. This means we calculate a value u_i for every x_i.
We can approximate the second derivative of u by using the second-order central formula:
v^'' (x)≈(f(x+h)-2f(x)+f(x-h))/h^2 
which can be re-written to fit our specific situation:
(d^2 v)/(dx^2 )=(v_(i+1)-2v_i+v_(i-1))/(∆x)^2 =-f(x_i)
where i has to vary between 0 and the N amounts of steps we wish to divide our x-interval into. We rewrite our equation and get an approximation for u(x); 
v_i=(-f(x_i ) (∆x)^2-v_(i-1)-v_(i+1))/2=(-100e^(-10x_i ) (∆x)^2+v_(i-1)+v_(i+1))/2


Problem 4 
We know that the expression Av ⃗=g ⃗, since A is a tridiagonal matrix with signature (a=-1,b=2,c=-1), can be written as 
Av ⃗=(■(b_1&c_1&…&…&…@a_1&b_2&c_2&…&…@0&a_2&…&…&…@…&…&…&b_(n-1)&c_(n-1)@…&…&…&a_(n-1)&b_n ))(■(v_1@v_2@…@...@v_n ))=(■(g_1@g_2@…@…@g_n ))=Av ⃗=g ⃗
We know from FYS3150 compendium on page 186 that each element of the g-matrix then can be written as 〖g_i=a〗_i v_(i-1)+b_i v_i+c_i v_(i+1) where i=1,2,…,n, and as we know a, b and c, we can rewrite the equation to g_i=-v_(i-1)+2v_i-v_(i+1). This is an expression for g_i we can compare with our previous expression for  (d^2 v)/(dx^2 ); f(x_i )=(-v_(i+1)+2v_i-v_(i-1))/(∆x)^2 . If we now set g_i=f(x_i)(∆x)^2, it is clear that the two equations equate, and we have shown that we can rewrite our discretized equation as the matrix equation Av ⃗=g ⃗.


Problem 5
The vector v ⃗^* contains a complete solution for the discretized Poisson equation with the length m. m x-values gives m solutions. We know that A has dimensions n x n. For this to be possible, we need the condition m≤n. 
When we solve the equation Av ⃗=g ⃗ for v ⃗ we find the approximate solution for v ⃗ at each point i in the discretization – v_i. This means each value v_i in our v ⃗ represents a complete solution 〖v ⃗_i〗^*, as well as an included error O(〖∆x〗^2 ). 


Problem 6
We start by defining a function in out c++ code gurl(), that takes x and the step size ∆x as arguments, and returns g_i=f(x_i)(∆x)^2. Thereafter, we define another function solveTriGen() that takes the three vectors a, b and c  - which can contain all different numbers and elements  - as well as an integer n which is the length of these vectors. We call our function gurl() to calculate g ⃗, and then we use forward and backward substitution to solve our equation Av ⃗=g ⃗ for v ⃗. The function returns both the v ⃗ array, as well as the position-array x ⃗. 
FLOPS



Problem 7
We define a function Problem7() that takes array size n, vectors a, b and c, as well as the name of a file as arguments, and implements these into our other function solveTriGen() to solve our equation  Av ⃗=g ⃗. The function then writes the  x ⃗ and v ⃗ vectors into a file with the file name provided as argument. The function Problem7() is called for a=[-1,-1,…,-1], b=[2,2,…,2] and c=[-1,-1,…,-1] vectors for varying n-values in the main-part of our c++ code. The functions create files containing data for each of our instances of n.
The files created by our c++ code is then imported and opened in our python-program. Here the data is read and plotted accordingly. We use the function for our exact solution we coded earlier, and plots these in the same plot. The plot is then saved by the code as a .pdf-file, Problem7plot.pdf. 
We run our code by calling our function Problem7() for n-values 10,100,1000 and 10000, and get the plot:
 
Figure 2: Plot for problem 7 that compares the solution to Poissons’ equation, calculated numerically for varying values of n to the exact solution
We notice that the accuracy of our plot increases by a noticeable amount when we increase n from 11 to 101. We see that the accuracy of the plots become so good that we don’t need to examine plots for increasing n-values.







Problem 8
To study the errors in our data, we define a simple function errors() in python that takes the exact solution u and numerically calculated solution v as arguments, and compute and return both the absolute and relative error at each step along these vectors. The reason we decided to use python for this task, is we already imported all our information to python, and writing a simple code here lets us avoid exporting and importing between c++ and python any further. The python code uses the errors() function to calculate errors as function of position along our x-axis, and creates plots of both the relative errors and the absolute errors at different values of n. The plots are saved by the code as a .pdf file Problem8plot.pdf.
 
Figure 3: Plot visualizing the absolute and relative errors for the numerically calculated v-values with varying n along the x-axis. 
We then call our function maketxt() in c++ for the remaining n-values including n=10^7, and import the data for the exact solution into our python-code. The same is done by calling our function Problem7() for the same remaining n-values, and importing these datafiles to python. We write a bit of code in python, and use the function errors() for these sets of data as well. We then create a file named maxreler.txt, that we fill with the n-values and the corresponding maximum relative errors. Opening this file we see a clear decreasing value of maximum relative error with an increasing n-value. 






Problem 9
We solve Problem 9 by creating a c++ function solveTriSpec() that makes small changes in our function solveTriGen(), to solve the equation where A is specified by the signature (-1,2,-1). This means our function only takes the a, b and c-values as arguments, as well as an integer n, and create their own a, b and c-vectors containing n- amounts of these a,b and c-values. The function then goes about solving for v the same way our function solveTriGen() did, and returns both the solution v and the x-vector. We create another function Problem9() that calls this solveTriGen(), and writes the data into a file we can import into python if we want. 
We call this function Problem9() easily in the main() part of our code, the same way we did for our Problem7() code earlier.

FLOPS


Problem 10
To compare the time it takes calculate v ⃗ by the special and general algorithm, simply call our functions Problem7() and Problem9() in the main() part of our code for varying values of n. We use <chrono> to measure the time it takes each time these functions are called, and save the data in two different vectors timesGen and timesSpes. Then, the we simply write a few lines of code that implements a function runtime() that takes these vectors as arguments, and writes them into a file Times.txt.
