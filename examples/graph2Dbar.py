import numpy as np
import matplotlib.pyplot as plt

# set width of bar
barWidth = 0.25
fig = plt.subplots(figsize =(12, 8))

data = np.genfromtxt('../examples/Results.txt')

# set height of bar
SingleMemTableTime = data[:5,1]
DoubleMemTableTime = data[5:,1]

print(SingleMemTableTime)
# Set position of bar on X axis
br1 = np.arange(len(SingleMemTableTime))
br2 = [x + barWidth for x in br1]

# Make the plot
plt.bar(br1, SingleMemTableTime, color ='r', width = barWidth,
		edgecolor ='grey', label ='Single MemTable')
plt.bar(br2, DoubleMemTableTime, color ='g', width = barWidth,
		edgecolor ='grey', label ='Double MemTable')

# Adding Xticks
plt.xlabel('Number of threads', fontweight ='bold', fontsize = 15)
plt.ylabel('Time in ms', fontweight ='bold', fontsize = 15)
plt.xticks([r + barWidth for r in range(len(SingleMemTableTime))],
		data[:5,0])

plt.title("Performance of Put operation in Single memtable vs Double memtable")

plt.legend()
plt.show()

