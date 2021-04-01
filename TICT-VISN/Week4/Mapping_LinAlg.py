# -*- coding: utf-8 -*-
"""
Created on Sun Feb 14 12:40:45 2021

@author: Milo
"""

import matplotlib.pyplot as plt
import numpy as np
from skimage import io, transform
from skimage.viewer import ImageViewer

orgImg = io.imread("IMG_5192.jpg")

rotationMatrix = np.array([[np.cos(45), -np.sin(45), 0],
                           [np.sin(45), np.cos(45) , 0],
                           [0         , 0          , 1]])

translationMatrix = np.array([[1, 0, 50  ],
                              [0, 1, -50],
                              [0, 0, 1  ]])

stretchMatrix = np.array([[1.2, 0, 0],
                          [0, 0, 0],
                          [0, 0, 1]])

# [1/3, 0]
# [0, 1/3]


finalMatrix = translationMatrix + rotationMatrix

tform = transform.AffineTransform(matrix=finalMatrix)
tf_img_rotation = transform.warp(orgImg, tform)

tform2 = transform.AffineTransform(matrix=translationMatrix)
tf_img_translated = transform.warp(orgImg, tform2)

tform3 = transform.AffineTransform(matrix=stretchMatrix)
tf_img_stretched = transform.warp(orgImg, tform3)




'''Displayment of pictures'''
fig, (ax1, ax2, ax3, ax4) = plt.subplots(nrows=1, ncols=4, figsize=(8, 4),
                                    sharex=True, sharey=True)

ax1.imshow(orgImg, cmap=plt.cm.gray)
ax1.axis('off')
ax1.set_title('image', fontsize=10)

ax2.imshow(tf_img_rotation, cmap=plt.cm.gray)
ax2.axis('off')
ax2.set_title(r'Rotated', fontsize=10)

ax3.imshow(tf_img_translated, cmap=plt.cm.gray)
ax3.axis('off')
ax3.set_title(r'Translated', fontsize=10)

ax4.imshow(tf_img_stretched, cmap=plt.cm.gray)
ax4.axis('off')
ax4.set_title(r'Stretched', fontsize=10)

# viewer = ImageViewer(orgImg)
# viewer.show()