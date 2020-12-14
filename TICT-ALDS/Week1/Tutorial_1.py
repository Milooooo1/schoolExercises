#schrijf hier je code voor opgave 3
from matplotlib import pyplot as plt
import numpy as np
import time
import statistics as stats

def random_int_array(length):
    array = np.random.randint(0, high=100, size=length, dtype='l')
    return array

def recFib(n):
    recFib.counter += 1
    
    if n == 0:
        return 0
    if n <= 2:
        return 1
    return recFib(n - 2) + recFib(n - 1)

def recFibMem(n, answers):
    recFibMem.counter += 1
    
    if answers == []:
        answers = [-1] * (n + 1)
        answers[0] = 0
        answers[1] = 1
    if answers[n] == -1:
        answers[n] = recFibMem(n - 2, answers) + recFibMem(n - 1, answers)
    return answers[n]


mean_recFib=[]
stdev_recFib=[]
mean_recFibMem=[]
stdev_recFibMem=[]

mean_recFibTime=[]
stdev_recFibTime=[]
mean_recFibMemTime=[]
stdev_recFibMemTime=[]
meetpunten = list(range(5,30,2))

for i in meetpunten: 
    Fib=[]
    FibTime=[]
    FibMem=[]
    FibMemTime=[]
    
    for j in range(0,10):
        recFib.counter = 0
        t1 = time.time()
        res = recFib(i)
        t2 = time.time()
        Fib.append(recFib.counter)
        FibTime.append(t2 - t1)
        
        arr = []
        recFibMem.counter = 0
        t1 = time.time()
        res = recFibMem(i, arr)
        t2 = time.time()
        FibMem.append(recFibMem.counter)
        FibMemTime.append(t2 - t1)

    mean_recFib.append(stats.mean(Fib))
    stdev_recFib.append(stats.stdev(Fib))
    mean_recFibMem.append(stats.mean(FibMem))
    stdev_recFibMem.append(stats.stdev(FibMem))
    
    mean_recFibTime.append(stats.mean(FibTime))
    stdev_recFibTime.append(stats.stdev(FibTime))
    mean_recFibMemTime.append(stats.mean(FibMemTime))
    stdev_recFibMemTime.append(stats.stdev(FibMemTime))
    
plt.plot(meetpunten, mean_recFib, 'b-')
plt.fill_between(meetpunten, np.array(mean_recFib)-np.array(stdev_recFib), np.array(mean_recFib)+np.array(stdev_recFib), color='b', alpha=0.3)
plt.plot(meetpunten, mean_recFibMem, 'r-')
plt.fill_between(meetpunten, np.array(mean_recFibMem)-np.array(stdev_recFibMem), np.array(mean_recFibMem)+np.array(stdev_recFibMem), color='r', alpha=0.3)
plt.xlabel("number of array elements")
plt.ylabel("function calls")
plt.legend(["recFib", "recFibMem"], loc='upper left')
plt.show()

plt.plot(meetpunten, mean_recFibTime, 'b-')
plt.fill_between(meetpunten, np.array(mean_recFibTime)-np.array(stdev_recFibTime), np.array(mean_recFibTime)+np.array(stdev_recFibTime), color='b', alpha=0.3)
plt.plot(meetpunten, mean_recFibMemTime, 'r-')
plt.fill_between(meetpunten, np.array(mean_recFibMemTime)-np.array(stdev_recFibMemTime), np.array(mean_recFibMemTime)+np.array(stdev_recFibMemTime), color='r', alpha=0.3)
plt.xlabel("number of array elements")
plt.ylabel("runtime")
plt.legend(["recFibRuntime", "recFibRuntime"], loc='upper left')
plt.show()