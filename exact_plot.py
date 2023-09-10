import matplotlib.pyplot as plt
import numpy as np
from math import*

#Problem 2
#we import our file we made of data from our c++ program into our python file
data=np.loadtxt("Problem2n11.txt");
# the left column (our x-values) is saved in a list. The same is done to the ux-values in our right column
x_val11=data[:,0]; ux_val11=data[:,1]
data=np.loadtxt("Problem2n101.txt"); x_val101=data[:,0] ; ux_val101=data[:,1]
data=np.loadtxt("Problem2n1001.txt"); x_val1001=data[:,0] ; ux_val1001=data[:,1]
data=np.loadtxt("Problem2n10001.txt"); x_val10001=data[:,0] ; ux_val10001=data[:,1]

#We make a simple plot and save it as a .pdf file Problem2plot.pdf
plt.title('The exact solution of the one-dimentional Poisson equation')
plt.plot(x_val11, ux_val11,label="exact solution n=11")
plt.plot(x_val101, ux_val101,label="exact solution n=101")
plt.plot(x_val1001, ux_val1001,label="exact solution n=1001")
plt.plot(x_val10001, ux_val10001,label="exact solution n=10001")
plt.xlabel('x')
plt.ylabel('u(x)')
plt.grid()
plt.legend()
plt.savefig("Problem2plot.pdf")
plt.show()

#Problem 7
data=np.loadtxt("Problem7n11.txt"); x_11=data[:,0]; v_11=data[:,1]
data=np.loadtxt("Problem7n101.txt"); x_101=data[:,0]; v_101=data[:,1]
data=np.loadtxt("Problem7n1001.txt"); x_1001=data[:,0]; v_1001=data[:,1]
data=np.loadtxt("Problem7n10001.txt"); x_10001=data[:,0]; v_10001=data[:,1]

plt.title("Problem 7")
plt.plot(x_11[:-1],v_11[:-1],label="Numeric calculation with n=11")
plt.plot(x_101[:-1],v_101[:-1],label="Numeric calculation with n=101")
plt.plot(x_1001[:-1],v_1001[:-1],label="Numeric calculation with n=1001")
plt.plot(x_10001[:-1],v_10001[:-1],label="Numeric calculation with n=10001")
plt.plot(x_val10001, ux_val10001,label="exact solution n=10001")
plt.xlabel('x')
plt.ylabel('u(x)')
plt.grid()
plt.legend()
plt.savefig("Problem7plot.pdf")
plt.show()

#Problem 8
def errors(u,v):
    u=np.array(u)
    v=np.array(v)
    absolute=np.log10(np.abs(u-v)) #uses formula from code to calculate the absolute error
    relative=np.log10(np.abs((u-v)/(u+1e-15))) # function for relative error from assignment text
    return absolute, relative

#we calculate the different
abserr11=errors(ux_val11,v_11[:-1])[0]; abserr101=errors(ux_val101,v_101[:-1])[0]
abserr1001=errors(ux_val1001,v_1001[:-1])[0]; abserr10001=errors(ux_val10001,v_10001[:-1])[0]
relerr11=errors(ux_val11,v_11[:-1])[1]; relerr101=errors(ux_val101,v_101[:-1])[1]
relerr1001=errors(ux_val1001,v_1001[:-1])[1]; relerr10001=errors(ux_val10001,v_10001[:-1])[1]

fig, (ax1, ax2) = plt.subplots(2)
fig.suptitle("Problem 8")
ax1.set_title("Absolute errors")
ax1.plot(x_11[:-1],abserr11,label="Absolute error n=11")
ax1.plot(x_101[:-1],abserr101,label="Absolute error n=101")
ax1.plot(x_1001[:-1],abserr1001,label="Absolute error n=1001")
ax1.plot(x_10001[:-1],abserr10001,label="Absolute error n=10001")
ax2.set_title("Relative errors")
ax2.plot(x_11[:-2],relerr11[:-1],label="Relative error n=11")
ax2.plot(x_101[:-2],relerr101[:-1],label="Relative error n=101")
ax2.plot(x_1001[:-2],relerr1001[:-1],label="Relative error n=1001")
ax2.plot(x_10001[:-2],relerr10001[:-1],label="Relative error n=10001")
ax1.set(ylabel="log10(∆)") ; ax2.set(xlabel="x", ylabel="log10(ϵ)")
ax1.grid(); ax2.grid()
ax1.legend(); ax2.legend()
plt.savefig("Problem8plot.pdf")
plt.show()

data=np.loadtxt("Problem2n5.txt"); x_val5=data[:,0] ; ux_val5=data[:,1]
data=np.loadtxt("Problem2n6.txt"); x_val6=data[:,0] ; ux_val6=data[:,1]
data=np.loadtxt("Problem2n7.txt"); x_val7=data[:,0] ; ux_val7=data[:,1]
data=np.loadtxt("Problem7n5.txt"); x_5=data[:,0]; v_5=data[:,1]
data=np.loadtxt("Problem7n6.txt"); x_6=data[:,0]; v_6=data[:,1]
data=np.loadtxt("Problem7n7.txt"); x_7=data[:,0]; v_7=data[:,1]
relerr5=errors(ux_val5,v_5[:-1])[1]
relerr6=errors(ux_val6,v_6[:-1])[1]
relerr7=errors(ux_val7,v_7[:-1])[1]

file=open("maxreler.txt","w")
file.writelines(["10", "        ", f"{max(relerr11)} \n"])
file.writelines(["100", "       ", f"{max(relerr101)} \n"])
file.writelines(["1000", "      ", f"{max(relerr1001)} \n"])
file.writelines(["10000", "     ", f"{max(relerr10001)} \n"])
file.writelines(["100000", "    ", f"{max(relerr5)} \n"])
file.writelines(["1000000", "   ", f"{max(relerr6)} \n"])
file.writelines(["10000000", "  ", f"{max(relerr7)} \n"])
file.close()
