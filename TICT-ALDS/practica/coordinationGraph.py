import statistics as stats
from matplotlib import pyplot as plt
import numpy as np
import random
import copy
import queue
import time


class edge:

    def __init__(self, var1, var2, nactionsx, nactionsy):
        """
        Constructor for the edge class
        :param var1: the (index of the) first decision variable
        :param var2: the (index of the) second decision variable
        :param nactionsx: the number of possible values for var1
        :param nactionsy: the number of possible values for var1
        """
        self.rewards = [] #table with the local rewards
        self.x = var1
        self.y = var2
        for i in range(nactionsx):
            rew = []
            for j in range(nactionsy):
                rew.append( random.random() )
            self.rewards.append(rew) #Rewards is an array of arrays 

    def localReward(self, xval, yval):
        """
        Return the local reward for this edge given the values of the connected decision variables
        :param xval: value of the first decision variable
        :param yval: value of the second decision variable
        :return: the local reward
        """
        return self.rewards[xval][yval]


class coordinationGraph:

    def __init__(self, noNodes, pEdge, noActions, seed=42):
        """
        Constructor for the coordination graph class. It generates a random graph based on a seed.

        :param noNodes: The number of vertices(nodes) in the graph. Each vertex represents a decision variable.
        :param pEdge: the probability that an edge will be made
        :param noActions: the number of possible values (integers between 0 and noActions) for the decision variables
        :param seed: the pre-set seed for the random number generator
        """
        random.seed(seed)
        self.nodesAndConnections = dict() #for each node, a list of nodes it is connected to
        self.edges = dict() #A dictionary of tuples (of two decision variables) to an object of the edge class
        for i in range(noNodes): #First make sure that the entire graph is connected (connecting all nodes to the next one)
            if i == 0:
                self.nodesAndConnections[i] = [i + 1]
                self.nodesAndConnections[i+1] = [i]
                eddy = edge(i, i+1, noActions, noActions)
                self.edges[(i,i+1)] = eddy
            elif i <noNodes-1:
                self.nodesAndConnections[i].append(i + 1)
                self.nodesAndConnections[i + 1] = [i]
                eddy = edge(i, i + 1, noActions, noActions)
                self.edges[(i, i + 1)] = eddy
        tuplist = [(x, y) for x in range(noNodes) for y in range(x + 2, noNodes)]
        for t in tuplist: #Then, for each possible edge, randomly select which exist and which do not
            r = random.random()
            if r < pEdge:
                self.nodesAndConnections[t[0]].append(t[1])
                self.nodesAndConnections[t[1]].append(t[0])
                self.edges[t] = edge(t[0], t[1], noActions, noActions)
        #For reasons of structure, finally, let's sort the connection lists for each node
        for connections in self.nodesAndConnections.values():
            connections.sort()

    def evaluateSolution(self, solution):
        """
        Evaluate a solution from scratch; by looping over all edges.

        :param solution: a list of values for all decision variables in the coordination graph
        :return: the reward for the given solution.
        """
        result = 0
        for i in range(len(solution)):
            for j in self.nodesAndConnections[i]:
                if(j>i):
                    # print( "("+str(i)+", "+str(j)+")\t -> "+str(round(self.edges[(i,j)].localReward(solution[i], solution[j]),4))) #Rounded to 4 digits for readability
                    result += self.edges[(i,j)].localReward(solution[i], solution[j])
        return result

    def evaluateChange(self, oldSolution, variableIndex, newValue):
        """
        TODO: a function that evaluates a local change. 
        NB: Make sure NOT to evaluate the entire solution twice (that would be a waste of computation time!!!) 

        :param oldSolution: The original solution
        :param variableIndex: the index of the decision variable that is changing
        :param newValue: the new value for the decision variable
        :return: The difference in reward between the old solution and the new solution (with solution[variableIndex] set to newValue)
        """        
        
        
        # result = self.evaluateSolution(oldSolution)
        # prevIndexValue = oldSolution[variableIndex]
        # oldSolution[variableIndex] = newValue
        # newResult = self.evaluateSolution(oldSolution) #Vervang dit met het verschil van de waardes uit de matrix
        # print(str(self.nodesAndConnections[variableIndex]))
        # oldSolution[variableIndex] = prevIndexValue
        # The code up here is inefficient but works to make sure if the below code actually gives the correct answer.
        
        localDifference = 0;
        for neighbour in self.nodesAndConnections[variableIndex]:
            if neighbour > variableIndex:
                # print("("+str(variableIndex)+", "+str(neighbour)+")")
                ov = self.edges[(variableIndex, neighbour)].rewards[oldSolution[variableIndex]][oldSolution[neighbour]]
                nv = self.edges[(variableIndex, neighbour)].rewards[newValue][oldSolution[neighbour]]
            else:
                # print("("+str(neighbour)+", "+str(variableIndex)+")")
                ov = self.edges[(neighbour, variableIndex)].rewards[oldSolution[variableIndex]][oldSolution[neighbour]]
                nv = self.edges[(neighbour, variableIndex)].rewards[oldSolution[neighbour]][newValue]
            # print("Difference: "+str(nv - ov)+" with neighbour: "+str(neighbour))
            localDifference += (nv - ov)
        # print("The total difference = "+str(localDifference))
        
        newSolution = copy.deepcopy(oldSolution)
        newSolution[variableIndex] = newValue
        return localDifference, newSolution
        # return newResult - result, oldSolution

def localSearch4CoG(coordinationGraph, initialSolution):
    """
    TODO: Implement local search
    :param coordinationGraph: the coordination graph to optimise for
    :param initialSolution: an initial solution for the coordination graph
    :return: a new solution (a local optimum)
    """
    nActs = 3
    nodeList = list(coordinationGraph.nodesAndConnections.keys())
    random.shuffle(nodeList)
    while len(nodeList) != 0:
        node = nodeList[0]
        nodeList.remove(nodeList[0])
        for val in range(0, nActs): #nActs is nu hardcoded 3. Hij is geen member variabel van de graph.
            delta, solution = coordinationGraph.evaluateChange(initialSolution, node, val)
            if delta > 0:
                initialSolution = solution #Set the initialSolution to the better solution.    
                random.shuffle(nodeList)
                break
    return initialSolution
            
def nonshuffle_localSearch4CoG(coordinationGraph, initialSolution):
    """
    TODO: Implement local search
    :param coordinationGraph: the coordination graph to optimise for
    :param initialSolution: an initial solution for the coordination graph
    :return: a new solution (a local optimum)
    """
    nActs = 3
    nodeList = list(coordinationGraph.nodesAndConnections.keys())
    _vars = queue.Queue(len(nodeList))
    random.shuffle(nodeList)
    #Add all decision variables to _vars in a random order due to the shuffle.
    for key in nodeList:
        _vars.put(key) 
    while not _vars.empty() :
        node = _vars.get()
        nodeList.remove(nodeList[0])
        for val in range(0, nActs): #nActs is nu hardcoded 3. Hij is geen member variabel van de graph.)
            delta, solution = coordinationGraph.evaluateChange(initialSolution, node, val)
            if delta > 0:
                initialSolution = solution #Set the initialSolution to the better solution.    
                break
    return initialSolution


def multiStartLocalSearch4CoG(coordinationGraph, noIterations):
    """
    TODO: Implement multi-start local search

    :param coordinationGraph: the coordination graph to optimise for
    :param noIterations:  the number of times local search is run
    :return: the best local optimum found and its reward
    """
    
    Amls = None             #Local Optimum
    val = float('-inf')
    for i in range(0, noIterations):
        randomSolution = [random.randint(0, 2)] * 50         #50 = nVars = hardcoded
        randomSolution = localSearch4CoG(coordinationGraph, randomSolution)
        newVal = coordinationGraph.evaluateSolution(randomSolution)
        if newVal > val:
            Amls = randomSolution
            val = newVal
    return Amls, val


def iteratedLocalSearch4CoG(coordinationGraph, pChange, noIterations):
    """
    TODO: Implement iterated local search

    :param coordinationGraph: the coordination graph to optimise for
    :param pChange: the perturbation strength, i.e., when mutating the solution, the probability for the value of a given
                    decision variable to be set to a random value.
    :param noIterations:  the number of iterations
    :return: the best local optimum found and its reward
    """
    
    nodeList = list(coordinationGraph.nodesAndConnections.keys())
    Ails = [random.randint(0,2)] * 50 #50 = nVars = hardcoded = random solution
    val = float('-inf')
    for i in range(0, noIterations):
        a = Ails
        for node in nodeList:
            r = random.randint(0,1)
            if r < pChange:
                a[node] = random.randint(0, 2)
        a = localSearch4CoG(coordinationGraph, a)
        newVal = coordinationGraph.evaluateSolution(a)
        if newVal > val:
            Ails = a
            val = newVal
    return Ails, val


###TODO OPTIONAL: implement genetic local search.

def prettyprint(nodesAndConnections):
    print("Node\tNeighbours")
    for key in nodesAndConnections.keys():
        print(str(key)+"\t:\t"+ str(nodesAndConnections[key]))
    print()
    
nVars = 50
nActs = 3
cog = coordinationGraph( nVars, 1.5/nVars, nActs)#, random.randint(0, 100) )
prettyprint(cog.nodesAndConnections)
# delta, solution = cog.evaluateChange([2]*nVars, 48, 1)
# print(delta)
# Test evaluate change function
print()
print("Default result: \t\t\t\t\t"+str(cog.evaluateSolution([2]*nVars)))
print("Local search result: \t\t\t\t"+str(cog.evaluateSolution(localSearch4CoG(cog, [2]*nVars))))
solution, value = multiStartLocalSearch4CoG(cog, 100)
print("Multi start local search results: \t"+str(value))
solution, value = iteratedLocalSearch4CoG(cog, 0.5, 100)
print("Iterated local search results: \t\t"+str(value))
# print("Local search (non-Shuffle) result: "+str(cog.evaluateSolution(nonshuffle_localSearch4CoG(cog, [2]*nVars))))



''' ==============================Plot code 4 Local Search============================== '''

nVars = 50
nActs = 3
cog = coordinationGraph( nVars, 1.5/nVars, nActs)#, random.randint(0, 100) )

stdev_runtime = []
mean_runtime  = []
meetpunten = list(range(0, 100))
for i in meetpunten:
    std  =[]
    
    for j in range(20): 
        
        t1 = time.time_ns()
        localSearch4CoG(cog, [2]*nVars)
        t2 = time.time_ns()
        
        std.append(t2 - t1)
        
    mean_runtime.append(stats.mean(std))
    stdev_runtime.append(stats.stdev(std))

plt.plot(meetpunten, mean_runtime, 'b-')
plt.fill_between(meetpunten, np.array(mean_runtime)-np.array(stdev_runtime), np.array(mean_runtime)+np.array(stdev_runtime), color='b', alpha=0.3)
plt.xlabel("iteratie")
plt.ylabel("runtime")
plt.legend(["localSearch"])
plt.show()



