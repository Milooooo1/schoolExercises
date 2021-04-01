# -*- coding: utf-8 -*-
"""
Created on Tue Feb 16 15:29:01 2021

@author: Milo
"""
import numpy as np
import matplotlib.pyplot as plt
import mnist
from keras.models import Sequential
from keras.layers import Conv2D, MaxPooling2D, Dense, Flatten
from keras.utils import to_categorical
from keras.datasets import cifar10

from scriptss.load_data import load_train, load_test

'''CNN Bouwen'''
# Het importeren en bewerken van de data 
train_images, train_labels = load_train()
test_images, test_labels = load_test()

# Normalizeren van de images
train_images = (train_images / 255) - 0.5
test_images = (test_images / 255) - 0.5

# Reshapen van de images zodat ze de juiste dimensies hebben
train_images = np.expand_dims(train_images, axis=3)
test_images = np.expand_dims(test_images, axis=3)

# Onze CNN

# Stap 1: bepaal hoeveel filters je wilt, hoe groot je filter size moet zijn 
# (let op je filter size mag niet te groot zijn vergeleken met je images), en wat je pool size is. 
num_filters = 2
filter_size = 0
pool_size =   0

# Stap 2: maak het model.
#    In de array die je aan sequential meegeeft, zet je alle layers die in het model moeten:
#    Conv2D, parameters: num_filters, filter_size, input_shape=(x, y, z)
#    MaxPooling2D, parameters: pool_size=pool_size
#    Flatten,
#    Dense, parameters: aantal outputs, activation='softmax'

model = Sequential([])