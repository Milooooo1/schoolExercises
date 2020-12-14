# -*- coding: utf-8 -*-
import numpy as np
import random as rand
import time
import warnings
import statistics as stats
from matplotlib import pyplot as plt
warnings.simplefilter(action='ignore', category=FutureWarning)

class myStack(): #Stack class from previous exercise
    max_capacity = 0
    current_pos  = 0
    
    def __init__(self, max_capacity):
        self.max_capacity = (max_capacity)
        self.array = np.zeros(self.max_capacity, dtype='i')
    
    def push(self, item):
        if self.current_pos == self.max_capacity:
            return False
        else:
            self.array[self.current_pos] = item
            self.current_pos += 1
            return True
        
    def pop(self):
        self.current_pos -= 1
        answer = self.array[self.current_pos]
        self.array[self.current_pos] = -1
        return answer
    
    def peek(self):
        return self.array[self.current_pos - 1]
    
    def isEmpty(self):
        if(self.current_pos == 0):
            return True
        else:
            return False
        
    def isFull(self):
        if(self.current_pos == self.max_capacity):
            return True
        else:
            return False
        
    def doubleCapacity(self):
        newArray = np.zeros((self.max_capacity * 2))

        for i in range(self.max_capacity):
            newArray[i] = self.array[i]
        
        self.array = newArray
        self.max_capacity = (self.max_capacity * 2)
    
    def print_stack(self): # Debugging purposes only
        print("\nStack content: ", self.array)

                            #End of Stack class
            
                           #PriorityQueue Class
        
class pqueue():
        
    def __init__(self, max_capacity=11):
        self.max_capacity = (max_capacity)
        self.array =  np.zeros((max_capacity,),dtype='i,i')
        self.available_indexes = myStack(max_capacity + 1)
        for i in range(-1, max_capacity, 1):
            self.available_indexes.push(i)
    
    #Deze functie heeft een tijd complexiteit van O(1), dit komt omdat hij 
    #niet door de array hoeft te loopen aangezien we een stack hebben
    #van beschikbare plekken. 
    def queue(self, v, p): 
        if self.available_indexes.peek() == -1:
            return "Queue is full..."
        else:
            self.array[self.available_indexes.pop()] = (v, p)

    #Deze funcite heeft een tijd complexiteit van O(n), je moet namelijk door
    #de array loopen om de laagste index te vinden. Je kan niet tot de 
    #nieuwste beschikbare index van onze beschikbare index array loopen 
    #omdet het zo kan zijn dat er een eental gaten nog niet gevuld zijn
    #met nieuwe items.     
    def dequeue(self):
        lowest_priority = 1000
        index_of_lowest_priority = -1 
        for i in range(self.max_capacity):
            if self.array[i][1] < lowest_priority and self.array[i][1] != 0:
                lowest_priority = self.array[i][1]
                index_of_lowest_priority = i
        self.array[index_of_lowest_priority] = (0,0)
        self.available_indexes.push(index_of_lowest_priority)
    
    #Voor deze functie geld eigenlijk hetzelfde als de dequeue functie
    #Hij heeft een tijdscomplexiteit van O(n), al hoeft deze functie niet
    #altijd over de hele lijst te loopen als hij als de waarde niet achteraan 
    #de lijst staat.
    def contains(self, v):
        for i in range(self.max_capacity):
            if self.array[i][0] == v:
                return True
        return False
     
    #Ook voor deze functie geld hetzelfde als voor contains en dequeue.
    #Hij heeft een tijdscomplexiteit van O(n) 
    def remove(self, v):
        for i in range(self.max_capacity):
            if self.array[i][0] == v:
                self.array[i] = (0,0)
                self.available_indexes.push(i)
    
    def print_queue(self): #For debugging purposes 
        print("Queue: ", self.array)
        
                        #End of PriorityQueue Class
                        
                          #Lucas's implementatie
class pQueue:
    
    def __init__(self):
            self.array = []
            self.numElements = 0
    
    # O(log(N))
    def verify(self, aIndex):
        if((aIndex+1) >= self.numElements // 2):
            return
        
        right = (aIndex+1) * 2
        left = right - 1
        toSwap = aIndex

        if(self.array[left][0] > self.array[toSwap][0]):
            toSwap = left

        if(self.array[right][0] > self.array[toSwap][0]):
            toSwap = right
        
        if(toSwap != aIndex):
            self.array[aIndex], self.array[toSwap] = self.array[toSwap], self.array[aIndex]
            self.verify(toSwap)
            
    # O(log(N))
    def queue(self, aVal, aPriority):
        self.array.append([aPriority, aVal])
        self.numElements += 1
                
        currElement = self.numElements
        currIndex = currElement - 1
        nodeAbove = (currElement // 2) - 1
        
        while (self.array[currIndex][0] > self.array[nodeAbove][0] and currElement != 1):
            self.array[currIndex], self.array[nodeAbove] = self.array[nodeAbove], self.array[currIndex]
            currElement = currElement // 2
            currIndex = currElement - 1
            nodeAbove = (currElement // 2) - 1
     
    # O(log(N))
    def dequeue(self):
        retVal = self.array[0]
        self._remove(0)
    
        return retVal
    
    # O(N)
    def contains(self, aVal):

        for i in range(self.numElements):
            if (self.array[i][1] == aVal):
                return True
                
        return False
    
    # O(N)
    def remove(self, aVal):
        i = 0
        while( i < self.numElements ):
            if (self.array[i][1] == aVal):
                self._remove(i)
                
            i += 1
     
    # O(1)
    def _remove(self, aIndex):
        self.array[aIndex], self.array[self.numElements-1] = self.array[self.numElements-1], self.array[aIndex]
        self.numElements -= 1
        self.array.pop()
        self.verify(aIndex)
        
    
    def __repr__(self):
        return self.array.__str__()
                    #Einde van lucas's implementatie
            
                                #Test cases
'''
myqueue = pqueue()
print("\nQueue created")
myqueue.print_queue()
for i in range(0, 10):
    myqueue.queue(random.randint(1, 40), random.randint(1, 10))
myqueue.queue(20, 4) #Test case for contains/ remove functions
print(myqueue.queue(20, 4)) #Testing to queue an item to a full queue 
print("\nQueue has been filled") #Prints something when the queue is full.
myqueue.print_queue()
myqueue.dequeue()
print("\nLowest priority removed")
myqueue.print_queue()
if myqueue.contains(20) == True:
    print("Contains function found the value.")
else:
    print("Contains function did not find the value.")
myqueue.remove(20)
print("\nAll items with value 20 removed")
myqueue.print_queue()
myqueue.queue(42, 42) #Testing with an easy number to find
print("\nAn item has been added in the spot of a previously removed item")
myqueue.print_queue()
'''
                            #End of Test cases
    
    
                                #Plot code
def test_queue(dataPoints, c, M=True):
    result = [[],[],[],[]]
    for i in dataPoints:
        
        if(M):
            q = c(i)
        else:
            q = c()
        startTime = time.time()

        for j in range(i):
            q.queue(rand.randint(0,500), rand.randint(0,500))
            
        result[0].append(time.time() - startTime)
        
        startTime = time.time()
        for j in range(i):
            q.dequeue()
        result[1].append(time.time() - startTime)
        
        if(M):
            q = c(i)
        else:
            q = c()
        for j in range(i):
            q.queue(rand.randint(0,500), rand.randint(0,500))
            
        startTime = time.time()
        for j in range(i):
            q.contains(rand.randint(0,500))
       
        result[2].append(time.time() - startTime)
    
    
        startTime = time.time()
        for j in range(i):
            q.remove(rand.randint(0,500))
   
        result[3].append(time.time() - startTime)

    return result                                
    

data = range(1, 2000, 100)

results2 = test_queue(data, pqueue, True)
results = test_queue(data, pQueue, False)

plt.plot(data, results[0], 'b-')
plt.plot(data, results[1], 'y-')
plt.plot(data, results[2], 'r-')
plt.plot(data, results[3], 'g-')

plt.plot(data, results2[0], 'm-')
plt.plot(data, results2[1], 'coral')
plt.plot(data, results2[2], 'k-')
plt.plot(data, results2[3], 'c-')
plt.xlabel("number of array elements")
plt.ylabel("time (seconds)")
plt.legend(["queueL","dequeueL", "containsL", "removeL", "queueM","dequeueM", "containsM", "removeM"], loc='upper left')

plt.show()
                            
'''                             
mean_queue=[]
stdev_queue=[]
mean_dequeue=[]
stdev_dequeue=[]
mean_contains=[]
stdev_contains=[]
mean_remove=[]
stdev_remove=[]

mean_lucasQueue=[]
stdev_lucasQueue=[]
mean_lucasDequeue=[]
stdev_lucasDequeue=[]
mean_lucasContains=[]
stdev_lucasContains=[]
mean_lucasRemove=[]
stdev_lucasRemove=[]

meetpunten = list(range(1, 1000, 100))
for i in meetpunten:
    std  =[] 
    std2 =[] 
    std3 =[]  
    std4 =[] 
    
    std5 =[] 
    std6 =[] 
    std7 =[]  
    std8 =[]
    
    for x in range(2):
        #Queue test
        myqueue = pqueue(i)
        t1 = time.time()
        for j in range(i): 
            myqueue.queue(random.randint(1, 100), random.randint(1, 10))
        t2 = time.time()
        std.append(t2 - t1)
        
        #Contains test
        t1 = time.time()
        for j in range(i):
            myqueue.contains(random.randint(1, 100))
        t2 = time.time()
        std3.append(t2 - t1)
            
        #Remove test
        t1 = time.time()
        for j in range(i):
            myqueue.remove(random.randint(1, 100))
        t2 = time.time()
        std4.append(t2 - t1)
        
        myqueue = pqueue(i) # refill array
        for j in range(i): 
            myqueue.queue(random.randint(1, 100), random.randint(1, 10))
        
        #Dequeue test
        t1 = time.time()
        for j in range(i):
            myqueue.dequeue()
        t2 = time.time()
        std2.append(t2 - t1)
        
        #TEST FUNCTIES ANDERE IMPLEMENTATIE
        
        #Queue test (Lucas)
        lucasqueue = pQueue()
        t1 = time.time()
        for j in range(i):
            lucasqueue.queue(random.randint(1, 100), random.randint(1, 10))
        t2 = time.time()
        std5.append(t2 - t1)
        
        #Contains test (Lucas)
        t1 = time.time()
        for j in range(i):
            lucasqueue.contains(random.randint(1, 100))
        t2 = time.time()
        std6.append(t2 - t1)
        
        #Remove test (Lucas)
        t1 = time.time()
        for j in range(i):
            lucasqueue.remove(random.randint(1, 100))
        t2 = time.time()
        std7.append(t2 - t1)        
        
        lucasqueue = pQueue() # refill array
        for j in range(i): 
            lucasqueue.queue(random.randint(1, 100), random.randint(1, 10))
        
        #Dequeue test
        t1 = time.time()
        for j in range(i):
            lucasqueue.dequeue()
        t2 = time.time()
        std8.append(t2 - t1)

    
    mean_queue.append(stats.mean(std))
    stdev_queue.append(stats.stdev(std))
    mean_dequeue.append(stats.mean(std2))
    stdev_dequeue.append(stats.stdev(std2))
    mean_contains.append(stats.mean(std3))
    stdev_contains.append(stats.stdev(std3))
    mean_remove.append(stats.mean(std4))
    stdev_remove.append(stats.stdev(std4))
    
    mean_lucasQueue.append(stats.mean(std5))
    stdev_lucasQueue.append(stats.stdev(std5))
    mean_lucasContains.append(stats.mean(std6))
    stdev_lucasContains.append(stats.stdev(std6))
    mean_lucasRemove.append(stats.mean(std7))
    stdev_lucasRemove.append(stats.stdev(std7))
    mean_lucasDequeue.append(stats.mean(std8))
    stdev_lucasDequeue.append(stats.stdev(std8))    
    
plt.plot(meetpunten, mean_queue, 'b-')      #Blue
plt.fill_between(meetpunten, np.array(mean_queue)-np.array(stdev_queue), np.array(mean_queue)+np.array(stdev_queue), color='b', alpha=0.3)
plt.plot(meetpunten, mean_dequeue, 'r-')    #Red
plt.fill_between(meetpunten, np.array(mean_dequeue)-np.array(stdev_dequeue), np.array(mean_dequeue)+np.array(stdev_dequeue), color='r', alpha=0.3)
plt.plot(meetpunten, mean_contains, 'g-')   #Green
plt.fill_between(meetpunten, np.array(mean_contains)-np.array(stdev_contains), np.array(mean_contains)+np.array(stdev_contains), color='g', alpha=0.3)
plt.plot(meetpunten, mean_remove, 'y-')     #Yellow
plt.fill_between(meetpunten, np.array(mean_remove)-np.array(stdev_remove), np.array(mean_remove)+np.array(stdev_remove), color='y', alpha=0.3)

plt.plot(meetpunten, mean_lucasQueue, 'c-')      #Cyan
plt.fill_between(meetpunten, np.array(mean_lucasQueue)-np.array(stdev_lucasQueue), np.array(mean_lucasQueue)+np.array(stdev_lucasQueue), color='c', alpha=0.3)
plt.plot(meetpunten, mean_lucasDequeue, 'm-')    #Magenta
plt.fill_between(meetpunten, np.array(mean_lucasDequeue)-np.array(stdev_lucasDequeue), np.array(mean_lucasDequeue)+np.array(stdev_lucasDequeue), color='m', alpha=0.3)
plt.plot(meetpunten, mean_lucasContains, 'k-')   #Black
plt.fill_between(meetpunten, np.array(mean_lucasContains)-np.array(stdev_lucasContains), np.array(mean_lucasContains)+np.array(stdev_lucasContains), color='k', alpha=0.3)
plt.plot(meetpunten, mean_lucasRemove, 'tab:purple')     #Purple
plt.fill_between(meetpunten, np.array(mean_lucasRemove)-np.array(stdev_lucasRemove), np.array(mean_lucasRemove)+np.array(stdev_lucasRemove), color='tab:purple', alpha=0.3)


plt.xlabel("Number of array elements")
plt.ylabel("Runtime")
plt.legend(["queue", "dequeue", "contains", "remove", "lucasQueue", "lucasDequeue", "lucasContains", "lucasRemove"], loc='upper left')
plt.show()                               
                                
                            #End of Plot code
'''