import numpy as np
import matplotlib.pyplot as plt


x = np.genfromtxt("proyectil_x.txt")
v = np.genfromtxt("proyectil_v.txt")


plt.figure()
plt.plot(x[:,0], x[:,1])
plt.grid()
plt.ylim([0,5])
plt.xlim([0,5])
plt.savefig('proyectil_x.png')



plt.figure()
plt.imshow(np.genfromtxt("0.txt"), vmin=0, vmax=100)
plt.colorbar()
plt.grid()
plt.savefig('0.png')


plt.figure()
plt.imshow(np.genfromtxt("1.txt"), vmin=0, vmax=100)
plt.colorbar()
plt.grid()
plt.savefig('1.png')


plt.figure()
plt.imshow(np.genfromtxt("2.txt"), vmin=0, vmax=100)
plt.colorbar()
plt.grid()
plt.savefig('2.png')
