import numpy as np
import matplotlib.pyplot as plt

with open("data/timetaken.txt", "r") as f:
	lines = f.readlines()

a = []
for i in lines:
	z = i.split("\t")
	for j in z:
		a.append(j)

N = a[::8]

time = a[7::8]

N = [int(i) for i in N]
time = [float(i.split(" ")[0]) for i in time]

print(N)
print(time)

#plt.scatter(N, time)
#plt.savefig("images/time_graph.png")


arr = np.linspace(0, 2000000, 1000)
print(arr)
curve = [x**2/2e9 for x in arr]

plt.plot(arr, curve)
plt.scatter(N, time)

plt.show()
#plt.savefig("images/time_graph.png")
