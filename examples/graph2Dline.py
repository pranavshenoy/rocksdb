
import numpy as np
import matplotlib.pyplot as plt

data = np.genfromtxt('../examples/Results.txt')

x1 = data[:5,0]
y1 = data[:5,1]
x2 = data[5:,0]
y2 = data[5:,1]

fig=plt.figure()
ax=fig.add_subplot(111, label="1")
ax2=fig.add_subplot(111, label="2", frame_on=False)

ax.plot(x1, y1, color="C0")
ax.set_xlabel("Number of threads", color="C0")
ax.set_ylabel("Time in ms", color="C0")
# ax.tick_params(axis='x', colors="C0")
# ax.tick_params(axis='y', colors="C0")

ax2.plot(x2, y2, color="C1")
ax2.set_xticks([])
ax2.set_yticks([])

plt.xticks(x1,[1,2,4,8,16])

plt.title("Performance of Put operation in Single memtable vs Double memtable")

plt.show()