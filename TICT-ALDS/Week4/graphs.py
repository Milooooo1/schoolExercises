from matplotlib import pyplot as plt
import numpy as np
import time
import statistics as stats

# Een zeer generieke manier om een graaf de implementeren is er 
# daarwerkelijk twee sets van te maken op basis van twee classes: 
class Vertex: 
    def __init__(self, identifier, data_):
        self.id = identifier
        self.data = data_
        
    def __eq__(self, other): #nodig om aan een set toe te voegen
        return self.id == other.id
    
    def __hash__(self): #nodig om aan een set toe te voegen
        return hash(self.id)
    
    def __repr__(self):
        return str(self.id)+":"+str(self.data)
        
class Edge:
    def __init__(self, vertex1, vertex2, data_):
        if(vertex1.id<vertex2.id):
            self.v1 = vertex1
            self.v2 = vertex2
        else:
            self.v1 = vertex2
            self.v2 = vertex1
        self.data = data_
        
    def __eq__(self, other): #nodig om aan een set toe te voegen
        return self.v1.id == other.v1.id and self.v2.id == self.v2.id
    
    def __hash__(self): #nodig om aan een set toe te voegen
        return hash(str(self.v1.id)+","+str(self.v2.id))
    
    def __repr__(self):
        return "("+str(self.v1.id)+","+str(self.v2.id)+"):"+str(self.data)

class CGraph:
    def __init__(self):
        self.V = set()
        self.E = set()
        
    def __str__(self):
        return "V: "+str(self.V)+"\nE: "+str(self.E)
            
        
# So, for a simple shortest path problem: 
gr = CGraph()
v1 = Vertex(1,"start")
v2 = Vertex(2,"")
v3 = Vertex(3,"")
v4 = Vertex(4,"")
v5 = Vertex(5,"goal")
v6 = Vertex(6,"")
gr.V.add(v1)
gr.V.add(v2)
gr.V.add(v3)
gr.V.add(v4)
gr.V.add(v5)
gr.V.add(v6)
e1 = Edge(v1,v2,7)
e2 = Edge(v1,v3,9)
e3 = Edge(v1,v6,14)
e4 = Edge(v2,v3,10)
e5 = Edge(v2,v4,15)
e6 = Edge(v3,v4,11)
e7 = Edge(v3,v6,2)
e8 = Edge(v6,v5,9)
e9 = Edge(v4,v5,6)
gr.E.add(e1)
gr.E.add(e2)
gr.E.add(e3)
gr.E.add(e4)
gr.E.add(e5)
gr.E.add(e6)
gr.E.add(e7)
gr.E.add(e8)
gr.E.add(e9)
print("====================CGraph====================")
print(gr)
print()

def minDistSet(a):
    lowestDist = float('inf')
    vertex = None
    for val in a:
        if val.dist < lowestDist:
            lowestDist = val.dist
            vertex = val
    return vertex

def setDefaultValues(a):
    for n in a:
        n.dist = float('inf')
        n.prev = None
        n.solved = False

def CGraphFindShortestPath(graph, start, finish):
    setDefaultValues(graph.V)
    route = []
    neighbours = []
    start.dist = 0
    N = set()
    N.add(start)
    S = set()
    while len(N) != 0:
        n = minDistSet(N)
        S.add(n)
        N.remove(n)
        n.solved = True
        if n == finish:
            break
        
        #Find neighbours of current node n
        neighbours = []
        for x in graph.E:
            if n == x.v1:
                neighbours.append((x.v2, x)) #(v1, v2):data
            if n == x.v2:
                neighbours.append((x.v1, x))

        #Loop through neighbours
        for neighbour in neighbours:
            if neighbour[0].solved:
                continue
            if neighbour[0] not in N:
                N.add(neighbour[0])
            altDistance = n.dist + neighbour[1].data
            
            if neighbour[0].dist > altDistance:
                neighbour[0].dist = altDistance
                neighbour[0].prev = n
    
    #Reroute your way back 
    nodeptr = finish.prev
    route.append(finish.id)
    while nodeptr != start:
        route.append(nodeptr.id)
        nodeptr = nodeptr.prev
    route.append(start.id)
    return finish.dist, route[::-1] #Reverse the array
            
dist, route = CGraphFindShortestPath(gr, v1, v5)
print("\nThe Results Are: ")
print("Shortest distance = "+str(dist))
print("Shortest route = "+str(route)+"\n\n")

print("====================DGraph====================")
DGraph = dict
gr2 = {1: ["start", {2:7, 3:9, 6:14}],
       2: ["", {1:7, 3:10, 4:15}], 
       3: ["", {1:9, 2:10, 4:11, 6:2}], 
       4: ["", {2:15, 3:11, 5:6}], 
       5: ["goal", {4:6, 6:9}], 
       6: ["", {1:14, 3:2, 5:9}]
      }

def prettyPrint(graph): 
    for key in graph:
        print(str(key)+" has neighbours: "+str(graph[key][1]))
        print("\tDist: "+str(graph[key][2][1]))
        print("\tPrev: "+str(graph[key][3][1]))
        print("\tFinished: "+str(graph[key][4][1]))

def getMinDist(graph, N):
    lowestDist = float('inf')
    nodeWithLowestDist = None
    for node in N:
        # print("Is "+str(graph[node][2][1])+" < "+str(lowestDist))
        if graph[node][2][1] < lowestDist:
            nodeWithLowestDist = node
            lowestDist = graph[node][2][1]
    return nodeWithLowestDist

def setDefaultValues2(a):
    for n in a:
        a[n].append(["Dist", float("inf")]) #On index 2
        a[n].append(["Prev", None])         #On index 3
        a[n].append(["Solved", False])      #On index 4

def DGraphFindShortestPath(graph, start, finish):
    setDefaultValues2(graph)
    route = []
    graph[start][2][1] = 0 #Set start on 0
    N = set()
    N.add(start)
    S = set()
    while len(N) != 0:
        n = getMinDist(graph, N)
        S.add(n)
        N.remove(n)
        graph[n][4][1] = True #Solved = true
        if n == finish:
            break
        
        #Add all neighbours to the list
        neighbours = set() #Clear neighbours
        keys = graph[n][1].keys()
        for key in keys:
            neighbours.add(key)

        #Loop through all neighbours  
        for m in neighbours:
            if graph[m][4][1] == True: #Check solved
                continue
            if m not in N: 
                N.add(m)
            altDistance = graph[n][2][1] + graph[n][1][m] #lengte van edge tussen n,m
            if graph[m][2][1] > altDistance:  
                graph[m][2][1] = altDistance  #Set new distance
                graph[m][3][1] = n            #Set prevn))
        

    #Reroute your way back 
    nodeptr = graph[finish][3][1]
    # print("Ptr: "+str(nodeptr))
    route.append(finish)
    while nodeptr != start:
        route.append(nodeptr)
        nodeptr = graph[nodeptr][3][1] #Gives an error if the path hasnt been completed
    route.append(start)
    return graph[finish][2][1], route[::-1] 
    #return distance           reversed route


print(gr2)
print()
dist, route = DGraphFindShortestPath(gr2, 1, 5)
print("\nThe Results Are: ")
print("Shortest distance = "+str(dist))
print("Shortest route = "+str(route)+"\n\n")


