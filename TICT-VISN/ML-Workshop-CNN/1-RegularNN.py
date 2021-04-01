# -*- coding: utf-8 -*-
"""
Created on Mon Feb 15 16:11:56 2021

@author: Milo
"""

from scriptss.load_data import load_train, load_test, load_example

import matplotlib.pyplot as plt
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Activation
from tensorflow.keras.utils import to_categorical
import numpy as np

# Laad de trainingsdata en labels
train_data, train_labels = load_train()
# De kleurwaarden in de afbeelding zijn nu 0 tot 255, we zetten deze om naar -0.5 tot 0.5
train_data = (train_data / 255) - 0.5

print(train_data.shape)
print(train_labels.shape)

plt.imshow(train_data[7])
plt.title(f"{train_labels[7]}")
print(f"Label: {train_labels[7]}")
plt.show()

train_labels = to_categorical(train_labels, 10)
train_data = train_data.reshape(train_data.shape[0], (train_data.shape[1]*train_data.shape[2]))

print(train_data.shape)
print(train_labels.shape)

model = Sequential()
# input_dim moet gelijk zijn aan de lengte van 1 input
model.add(Dense(32, input_dim=28)) # FIXME
model.add(Dense(10, activation="softmax"))

model.summary()