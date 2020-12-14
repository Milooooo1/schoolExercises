# -*- coding: utf-8 -*-
import statistics as stats
import numpy as np

class node:
    def __init__(self, value):
        self.left = None
        self.right = None
        self.value = value
    
    
    def add(self, value):
        if self.value == value:
            return False
        elif value < self.value:
            if self.left:
                return self.left.add(value)
            else:
                self.left = node(value)
                return True
        else:
            if self.right:
                return self.right.add(value)
            else:
                self.right = node(value)
                return True
        
    def printTree(self, prefix=""):
        if self:
            if self.left:
                self.left.printTree(prefix=prefix+"l:")
            print(prefix + " " + str(self.value))
            if self.right:
                self.right.printTree(prefix=prefix+"r:")
        
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
        if arr[j] <= pivot :
            arr[i], arr[j] = arr[j], arr[i]
            i+=1
            
    arr[i], arr[hi] = arr[hi], arr[i]
    return i

def quicksort3(arr, lo, hi):
    
    if lo >= hi:
        return arr
    
    p   = partition3(arr, lo, hi)
    arr = quicksort3(arr, lo, (p-1))
    arr = quicksort3(arr, (p+1), hi)
    return arr

def genSortedArr(arrLength):
    arr = np.random.randint(0, high=100, size=arrLength, dtype='l')
    return quicksort3(arr, 0, arrLength - 1)

def balancedAdd(lst, l, r, element=None):
    if r >= l:
        m = int(l + (r-l)/2)
        if(element is None):
            element = node(lst[m])
        else:
            element.add(lst[m])
        balancedAdd(lst, l, m - 1, element)
        balancedAdd(lst, m + 1, r, element)
    return element

def balancedTree(depth):
    n = pow(2, depth) - 1
    lst = genSortedArr(n)
    tree = balancedAdd(lst, 0, len(lst)-1)
    return tree
    
bst = balancedTree(20)
bst.printTree()


    