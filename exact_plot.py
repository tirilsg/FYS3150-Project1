import matplotlib.pyplot as plt
import numpy as np

#we import our file we made of data from our c++ program into our python file
filename="Problem2.txt"
data=np.loadtxt(filename)
x_values=data[:,0] # the data from the left column (our x-values) is saved in a list
ux_values=data[:,1] #the same is done to the ux-values in our right column

#We make a simple plot and save it as a .pdf file Problem2plot.pdf
plt.title('The exact solution of the one-dimentional Poisson equation')
plt.plot(x_values, ux_values,label="exact solution")
plt.xlabel('x')
plt.ylabel('u(x)')
plt.grid()
plt.legend()
plt.savefig("Problem2plot.pdf")
