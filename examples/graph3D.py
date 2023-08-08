
import matplotlib.pyplot as plt
import mpl_toolkits
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm
from scipy.interpolate import griddata
# from matplotlib.mlab import griddata
import numpy as np
from math import log

data = np.genfromtxt('../examples/Get_1m.txt')

x = data[:,0]

y = data[:,1]

z = data[:,2]

fig = plt.figure()

ax = fig.add_subplot(111, projection='3d')

ax.set_title("Performance of Get operation in single memtable")

ax.set_xlabel("Number of active memtables")

ax.set_ylabel("Number of threads")

ax.set_zlabel("Time in ms")


ax.plot(x,y,z)

plt.show()