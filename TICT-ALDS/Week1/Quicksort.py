from matplotlib import pyplot as plt
import numpy as np
import statistics as stats

def random_int_array(length):
    array = np.random.randint(0, high=100, size=length, dtype='l')
    return array

def partition(arr, lo, hi):
    pivot = arr[hi]
    i = lo
    for j in range(lo, hi):
        partition.counter += 1
        if arr[j] <= pivot :
            arr[i], arr[j] = arr[j], arr[i]
            i+=1
    arr[i], arr[hi] = arr[hi], arr[i]
    return i

def quicksort(arr, lo, hi):
    
    if lo >= hi:
        return arr
    
    p   = partition(arr, lo, hi)
    arr = quicksort(arr, lo, (p-1))
    arr = quicksort(arr, (p+1), hi)
    return arr

def partition2(arr, lo, hi):
    smallestIndex = 0;
    smallestValue = arr[0];
    for i in range(lo, hi):
        if(arr[i] < smallestValue):
            smallestValue = arr[i]
            smallestIndex = i
    arr[hi], arr[smallestIndex] = arr[smallestIndex], arr[hi] #Switch pivot with hi
    pivot = arr[hi]
    i = lo
    for j in range(lo, hi):
        partition2.counter += 1
        if arr[j] <= pivot :
            arr[i], arr[j] = arr[j], arr[i]
            i+=1
            
    arr[i], arr[hi] = arr[hi], arr[i]
    return i

def quicksort2(arr, lo, hi):
    
    if lo >= hi:
        return arr
    
    p   = partition2(arr, lo, hi)
    arr = quicksort2(arr, lo, (p-1))
    arr = quicksort2(arr, (p+1), hi)
    return arr

def partition3(arr, lo, hi):
    meanIndex = arr[lo]
    meanArray = arr[lo:(hi+1)]
    meanValue = 0
    if(len(meanArray) % 2) == 0: 
        newAppendedArray = np.append(meanArray, arr[hi])    
        meanValue = stats.median(newAppendedArray)
        meanIndex = np.where(newAppendedArray == meanValue)[0][0] + lo
    else:
        meanValue = stats.median(meanArray)
        meanIndex = np.where(meanArray == meanValue)[0][0] + lo
    arr[hi], arr[meanIndex] = arr[meanIndex], arr[hi] #Switch pivot with hi
    pivot = arr[hi]
    i = lo
    for j in range(lo, hi):
        partition3.counter += 1
        if arr[j] <= pivot :
            arr[i], arr[j] = arr[j], arr[i]
            i+=1
            
    arr[i], arr[hi] = arr[hi], arr[i]
    return i

def quicksort3(arr, lo, hi):
    # quicksort3.counter += 1
    
    if lo >= hi:
        return arr
    
    p   = partition3(arr, lo, hi)
    arr = quicksort3(arr, lo, (p-1))
    arr = quicksort3(arr, (p+1), hi)
    return arr

mean_quicksort=[]
stdev_quicksort=[]
mean_quicksort2=[]
stdev_quicksort2=[]
mean_quicksort3=[]
stdev_quicksort3=[]
meetpunten = list(range(5,1006,100))
for i in meetpunten:
    std  =[]
    std2 =[]
    std3 =[]
    
    for j in range(50): 
        partition.counter  = 0
        partition2.counter = 0
        partition3.counter = 0
        
        arr = random_int_array(i)
        res = quicksort(arr, 0, (i-1))
        arr = random_int_array(i)
        res = quicksort2(arr, 0, (i-1))
        arr = random_int_array(i)
        res = quicksort3(arr, 0, (i-1))
        
        std.append(partition.counter)
        std2.append(partition2.counter)
        std3.append(partition3.counter)
        
    mean_quicksort.append(stats.mean(std))
    stdev_quicksort.append(stats.stdev(std))
    mean_quicksort2.append(stats.mean(std2))
    stdev_quicksort2.append(stats.stdev(std2))
    mean_quicksort3.append(stats.mean(std3))
    stdev_quicksort3.append(stats.stdev(std3))
    
plt.plot(meetpunten, mean_quicksort, 'b-')
plt.fill_between(meetpunten, np.array(mean_quicksort)-np.array(stdev_quicksort), np.array(mean_quicksort)+np.array(stdev_quicksort), color='b', alpha=0.3)
plt.plot(meetpunten, mean_quicksort2, 'r-')
plt.fill_between(meetpunten, np.array(mean_quicksort2)-np.array(stdev_quicksort2), np.array(mean_quicksort2)+np.array(stdev_quicksort2), color='r', alpha=0.3)
plt.plot(meetpunten, mean_quicksort3, 'g-')
plt.fill_between(meetpunten, np.array(mean_quicksort3)-np.array(stdev_quicksort3), np.array(mean_quicksort3)+np.array(stdev_quicksort3), color='r', alpha=0.3)
plt.xlabel("number of array elements")
plt.ylabel("Vergelijkingen")
plt.legend(["quicksort", "quicksort2","quicksort3"])
plt.show()
