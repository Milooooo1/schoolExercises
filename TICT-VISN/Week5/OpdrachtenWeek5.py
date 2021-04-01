# -*- coding: utf-8 -*-
"""
Created on Mon Feb 15 09:44:18 2021

@author: Milo
"""

import numpy as np
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn import datasets
from sklearn import svm
import random

digits = datasets.load_digits()
# print(digits.data)
# print(digits.target)

x_test, x_train, y_test, y_train = train_test_split(digits.data, 
                                                    digits.target,
                                                    test_size=0.66)

print(len(digits.data))
print(len(x_train))
print(len(x_test))

clf = svm.SVC(gamma=0.001, C=100).fit(x_train, y_train)
# X,y = digits.data[:-10], digits.target[:-10]
# # X, y = dataset, testset
# clf.fit(X,y)

score = 0
totalTestCases = 250
for i in range(0, totalTestCases):
    index = random.randint(0, len(x_test)-1)
    # print(clf.predict(x_test[index:index+1])) #Beetje flauw, maar hij wil perse 2d-array hebben ook als er maar 1 element inzit
    # print(y_test[index])
    if clf.predict(x_test[index:index+1]) == y_test[index]:
        score += 1
        
print("Total acurracy: " + str(int((score/totalTestCases)*100)))

# plt.imshow(x_test[index].reshape(8,8), cmap=plt.cm.gray_r, interpolation='nearest')
# plt.show()