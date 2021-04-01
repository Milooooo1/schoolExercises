# -*- coding: utf-8 -*-
"""
Created on Tue Feb 16 13:44:55 2021

@author: Milo
"""

import mnist
import random
import math
import numpy as np
import matplotlib.pyplot as plt
from typing import Tuple
from scipy.signal import convolve2d

from scriptss.load_data import load_train


def convolve(image, filt):
    """
    Task: Bouw een functie die over een foto heen glijdt en de dot product op ieder punt berekend
    en de som van daarvan terugzet in een output array.
    
    image: een 28x32 numpy array
    filt: een 3x3 array
    """    
    print(image.shape)
    output = np.zeros((image.shape[0]-1,image.shape[1]-1), dtype=int)
    print(output.shape)
    
    for i in range(0, image.shape[0]-1):
        for j in range (0, image.shape[1]-1):
            res  = np.dot([[image[i-1][j-1], image[i][j-1], image[i+1][j-1]],
                           [image[i-1][j]  , image[i][j]  , image[i+1][j]  ],
                           [image[i-1][j+1], image[i][j+1], image[i+1][j+1]]
                          ], filt)
            
            output[i][j] = int(sum(res.flatten()))
            
    return output


def print_matrix(matrix):
    """
    Prints a matrix
    """
    for x in matrix:
        print(" ".join(map(str, x)))

def relu(x):
    """
    This function applies a ReLu or Rectified Linear Unit. 
    """
    output = np.zeros((x.shape[0],x.shape[1]), dtype=int)
    
    for i in range(0, x.shape[0]):
        for j in range(0, x.shape[1]):
            output[i][j] = max(0, x[i][j])
            
    return output

def max_pooling(image, n):
   """
    Task: Bouw een functie die over een afbeelding heen glijdt en per regio van n breed en n hoog
    het maximale element eruit haalt en deze in een output array zet.
    
    image: een 28x32 numpy array
    n: de grootte van de pool size
    """
   output = np.zeros((math.floor(image.shape[0]/n),math.floor(image.shape[1]/n)), dtype=int)  
   for i in range(0, image.shape[0]-(n*2), n):
      for j in range (0, image.shape[1]-(n*2), n):
          pool = []
          for x in range(0, n):
              for y in range(0, n):
                  pool.append(image[i+x][j+y])
          output[math.floor(i/n)][math.floor(j/n)] = np.amax(pool)                 
   return output      

def softmax_func(nodes):
    """
    Dit wordt de Softmax functie zoals je hebt gelezen in de voorgaande stappen:
    - bereken de numerator
    - bereken de denominator
    - return hiermee uiteindelijk de 'kans' functie
    """
    # output = np.array(len(nodes), dtype=float)
    # print(output.shape)
    # print(len(nodes))
    # print()
    # for i in range(0, len(nodes)):
    #     res = 0
    #     for j in range(0, len(nodes[i])):
    #         # print(nodes[i][j])
    #         # print(math.exp(nodes[i][j]))
    #         res += math.exp(nodes[i][j])
            
    #     np.append(output,  [math.exp(3) / res, math.exp(1) /res ])
    #     print(output)
    # # return( [math.exp(3) / res, math.exp(1)])
    # return output
    
    output = []
    res = 0
    for j in range(0, len(nodes)):
        # print(nodes[i][j])
        # print(math.exp(nodes[j]))
        res += math.exp(nodes[j])
        
    # np.append(output,  [math.exp(3) / res, math.exp(1) /res ])
    for i in range(0, len(nodes)):
        output.append(math.exp(nodes[i]) / res)
    print(output)
    return output
    

def plot_me(nodes):
    plt.title("Output of nodes")
    for i, j in enumerate(nodes):
        plt.bar(i,j)
    plt.show()

'''Load data'''
X_train, y_train = load_train()

# X_train = (X_train / 255) - 0.5                                  #TURN THIS OFF
index = random.randint(0, X_train.shape[0])
image_to_filter = X_train[index]
plt.imshow(image_to_filter)
plt.show()
print("Label: " + str(y_train[index]))
print("Resolution: " + str(X_train[index].shape))


'''Apply filter'''
u_filter = [[0, -1, 0],
            [-1, 5, -1],
            [0, -1, 0]]

# print image and the output after convolution
fig, axs = plt.subplots(1, 2, figsize=(10, 4))

axs[0].imshow(image_to_filter)
axs[0].set_title("image before filter")

#TODO zet de met behulp van de eerder geschreven functie de afbeelding om tot de activatie map
result_image = convolve(image_to_filter, u_filter)
axs[1].imshow(result_image)
axs[1].set_title("image after filter")

plt.show()

'''Sobel'''
diagonal_filter = [[-1, -1, 2], 
                   [-1, 2, -1],
                   [2, -1, -1]]

gx_sobel = [[-1, 0, 1], 
           [-2, 0, 2],
           [-1, 0, 1]]

gy_sobel = [[1, 2, 1], 
           [0, 0, 0],
           [-1, -2, -1]]

# plot the filters
fig, axs = plt.subplots(2, 2, figsize=(9, 9))

axs[0][0].imshow(image_to_filter)
axs[0][0].set_title("image before filter")

# identity filter
axs[0][1].imshow(convolve2d(image_to_filter, diagonal_filter))
axs[0][1].set_title("diagonal line detection")

# Gx sobel filter
axs[1][0].imshow(convolve2d(image_to_filter, gy_sobel))
axs[1][0].set_title("horizontal Sobel filter")

# Gy sobel filter
axs[1][1].imshow(convolve2d(image_to_filter, gx_sobel))
axs[1][1].set_title("vertical Sobel filter")

plt.show()

'''print_matrix'''
matrix = [[3, 5, 6], [6, 2, 8], [9, 5, 6]]

print()
print("Matrix before padding:")
print_matrix(matrix)
print("\nMatrix after zero padding:")
print_matrix(np.pad(matrix, 1))

'''ReLu layer'''
# plot the filters
fig, axs = plt.subplots(1, 3, figsize=(15, 4))

axs[0].imshow(image_to_filter)
axs[0].set_title("image before filter")

filtered_img = convolve2d(image_to_filter, gx_sobel)

axs[1].imshow(filtered_img)
axs[1].set_title("image after filter")

filtered_img = relu(filtered_img)

axs[2].imshow(relu(filtered_img))
axs[2].set_title("image after relu")

plt.show()

'''Pooling Layer'''
# TODO selecteer een cijfer uit de training set
image_to_pool = X_train[index]
plt.imshow(image_to_pool)
plt.show()

image_after_pool = max_pooling(image_to_pool, 2)

# print image and the output after convolution
fig, axs = plt.subplots(1, 2, figsize=(10, 4))

axs[0].imshow(image_to_pool)
axs[0].set_title("image before pooling\nshape: {0}".format(image_to_pool.shape))

axs[1].imshow(image_after_pool)
axs[1].set_title("image after pooling\nshape: {0}".format(image_after_pool.shape))

plt.show()

'''Nodes'''
nodes = [3,1]

plot_me(nodes)

softmax_nodes = softmax_func(nodes)
print("Output nodes after applying the Softmax function: {}".format(softmax_nodes))

total_softmax_nodes = sum(softmax_nodes)
print("Sum of the probabilities: {}".format(total_softmax_nodes))

plot_me(softmax_nodes)