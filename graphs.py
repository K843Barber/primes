import numpy as np
import matplotlib.pyplot as plt

with open("data/timetaken.txt", "r") as f:
	lines = f.readlines()

a = [item for sublist in lines for item in sublist.split("\t")]

N = a[::8]
time = a[7::8]
primes = a[2::8]

print(primes)

N = [int(i) for i in N]
time = [float(i.split(" ")[0]) for i in time]
primes = [int(i) for i in primes]

arr = np.linspace(0, 2e6, 1000)
time_curve = [x**2/2e9 for x in arr]
prime_curve = [x/1.35e1 for x in arr]

# The Time Complexity curve O(n**2)
plt.plot(arr, time_curve)
plt.scatter(N, time)
plt.show()
#plt.savefig("images/time_graph.png")

# Graph to show frequency of Prime numbers as N increases
plt.plot(arr, prime_curve)
plt.scatter(N, primes)
plt.show()
#plt.savefig("images/prime_graph.png")
