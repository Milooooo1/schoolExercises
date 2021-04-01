# -*- coding: utf-8 -*-
"""
Created on Mon Feb 15 14:04:34 2021

@author: Milo
"""

import numpy as np
import matplotlib.pyplot as plt
from IPython.display import Image

def plotPointsOnly(vlist):
    for v in vlist:
        plt.plot(v[0], v[1], 'ro')
    axes = plt.gca()
    axes.set_xlim([0,10])
    axes.set_ylim([0,10])
    fig = plt.gcf()
    fig.set_size_inches(5,5)
    plt.show()
    
    
def translateAllBy(vlist, vec):
    return [v+vec for v in vlist]

def scaleAllBy(vlist, c):
    return [c*v for v in vlist]

def rotationMatrix2D(angle):
    return np.array([[np.cos(angle), -np.sin(angle)],
                     [np.sin(angle),  np.cos(angle)]])

def applyTransformationToAll(matrix, vlist):
    return [np.dot(matrix,v) for v in vlist]

def makeMeHomogenous(vec):
    return np.array([vec[0],vec[1],1])

def makeUsHomogenous(vlist):
    result = []
    for v in vlist:
        result.append(makeMeHomogenous(v))
    return result

def translationMatrix(v):
    return np.array([[1.0,0.0,v[0]],[0.0,1.0,v[1]],[0.0,0.0,1.0]])

def computeCentre(vlist):
    result = np.array([0.0,0.0,0.0]) #oh ja, even floatjes gebruiken inplaats van integers (typecasting, meh, details)
    for v in vlist: 
        result += v
    result /= len(vlist)
    return result

def plotOnlyPointsAndMiddle(vlist,middle):
    for v in vlist:
        plt.plot(v[0], v[1], 'ro')
    plt.plot(middle[0], middle[1], 'ro', color='b')
    axes = plt.gca()
    axes.set_xlim([0,10])
    axes.set_ylim([0,10])
    fig = plt.gcf()
    fig.set_size_inches(5,5)
    plt.show()

    
'''original'''
v1 = np.array([1,1]) #Voor vectoren gebruiken we numpy's array objecten. 
vlist = [v1, np.array([2,1]), np.array([1.5,2])] #laten we drie puntjes gebruiken
# plotPointsOnly(vlist) #...en ze even laten zien:

# '''translate'''
# translatedPoints = translateAllBy(vlist,np.array([5,0]))
# # plotPointsOnly( translatedPoints )

# '''rotate'''
# vlist2 = translatedPoints
# rot = rotationMatrix2D(np.pi/16)
# plotPointsOnly( vlist2 )
# vlist3 = applyTransformationToAll(rot, vlist2) #laten we gaan draaien:
# plotPointsOnly(vlist3)

# # rot4 = np.dot(rot, np.dot(rot, np.dot(rot,rot)))
# rot4 = rotationMatrix2D(45)
# plotPointsOnly(applyTransformationToAll(rot4, vlist2)) #dit is hetzelfde resultaat als vier keer los de rotatie toepassen.
# rot4

# '''rotate + scale //opdracht 3'''
# vlist4 = [[1,1], [2,1], [1.5,2]] #Test Case 1
# vlist5 = [[1,1], [2,1], [1.5,2]] #Test Case 1
# # vlist4 = [[2,3], [3,3], [4,5]] #Test Case 2

# plotPointsOnly(vlist4)
# rotationMatrix = np.array([[np.cos(np.pi/6), -np.sin(np.pi/6)],
#                            [np.sin(np.pi/6),  np.cos(np.pi/6)]])

# scaleMatrix    = np.array([[2, 0 ],
#                            [0, 1 ]])

# finalMatrix = np.dot(rotationMatrix, scaleMatrix)

# vlist4 = applyTransformationToAll(finalMatrix, vlist4)
# plotPointsOnly(vlist4)


# scaled4 = applyTransformationToAll(scaleMatrix, vlist5)
# # vlist5 = translateAllBy(scaled4, np.array(-(scaled4[0] - vlist5[0])))
# plotPointsOnly(scaled4)
# vlist5 = applyTransformationToAll(rotationMatrix, scaled4)
# plotPointsOnly(vlist5)

# '''Scale'''
# enlargedPoints = scaleAllBy(vlist,5)
# plotPointsOnly( enlargedPoints )

# '''set back to origin //opdracht 1'''
# diff = enlargedPoints[0] - vlist[0]
# print(diff)

# orgPosPoints = translateAllBy(enlargedPoints, np.array(-diff))
# plotPointsOnly(orgPosPoints)


# '''homogene coordinaten'''
# hvList = makeUsHomogenous(vlist)
# plotPointsOnly(hvList)
# print(hvList)
# print(translationMatrix([3,3]))
# # hvList = applyTransformationToAll(translationMatrix([3,3]), hvList)
# print(hvList)
# plotPointsOnly(hvList)

# '''rotate around middlepoint'''
# T33= np.array([[1,0,3],
#                [0,1,3],
#                [0,0,1]])

# hv2 = applyTransformationToAll(T33, hvList)
# computeCentre(hv2)
# plotPointsOnly(hv2)

# #dan kunnen we de stap1 matrix bouwen:
# mp = computeCentre(hv2)
# stap1 = translationMatrix(-mp)
# #maar ook gelijk de stap3 matrix:
# stap3 = translationMatrix(mp)

# #voor stap2 moeten we eerst de rotatiematrix even in homogene coordinaten krijgen: 
def rotationMatrix(angle):
    return np.array([[np.cos(angle), -np.sin(angle),0],[np.sin(angle),np.cos(angle),0],[0,0,1]])

# # stap2 = rotationMatrix(np.pi/4) #45 graden

# # theEntireTransformation = np.dot(stap3, np.dot(stap2,stap1))
# # plotOnlyPointsAndMiddle(hv2,mp)
# # hv2yay = applyTransformationToAll(theEntireTransformation, hv2)
# # plotOnlyPointsAndMiddle(hv2yay,mp)

'''laatste opdracht'''
#         eye 0  eye 1    ml 2    mr 3      mm 4
smiley = [[4,5], [6,5], [3,3.5], [7,3.5], [5, 2.5]]

prev = smiley[2]
prev2 = smiley[3]
for i in range (0, 10):
    prev = [prev[0] + 0.2, prev[1] - 0.1]
    prev2 = [prev2[0] - 0.2, prev2[1] - 0.1]
    smiley.append(prev)
    smiley.append(prev2)

smiley = makeUsHomogenous(smiley)

mp = computeCentre(smiley)    
plotPointsOnly(smiley)

stap1 = translationMatrix(-mp)
stap2 = rotationMatrix(np.pi/1)
stap3 = translationMatrix(mp)

smiley = applyTransformationToAll(np.dot(stap3, np.dot(stap2,stap1)), smiley)
plotPointsOnly(smiley)

