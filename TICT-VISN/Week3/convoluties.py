# -*- coding: utf-8 -*-
"""
Created on Mon Feb  8 16:36:15 2021

@author: Milo
"""
import matplotlib.pyplot as plt
from skimage import data, filters, io, feature
from skimage.filters import * 
from skimage.viewer import ImageViewer
import scipy
from scipy import ndimage

image = data.camera()
cannyimage = io.imread("IMG_3288.jpg")
print(cannyimage.shape)
cannyimage = cannyimage[:,:,0]
print(cannyimage.shape)

'''Verschillende Masks'''
mask1=[[-1,-2,-1],[0,0,0],[1,2,1]] #X-axis edge detection
mask2=[[1,0,-1],[2,0,-2],[1,0,-1]] #Y-axis edge deteciton
mask3=[[-0.02,-0.08,-0.02],[0,0,0],[0.02,0.08,0.02]] #Sensitive

newimage=scipy.ndimage.convolve(image, mask1)
# viewer = ImageViewer(newimage)
# viewer.show()

newimage=scipy.ndimage.convolve(newimage, mask2)
# viewer = ImageViewer(newimage)
# viewer.show()

'''Verschillende Filters'''
# newimage=sobel_h(image)#, mask1)
# newimage=sobel_v(image)
# newimage=prewitt(image)
# newimage=laplace(image)
# newimage=scharr(image)

'''Canny Edge Detection'''
edges1sigma = 3
edges2sigma = 3.5
edges1 = feature.canny(cannyimage, sigma=edges1sigma)
edges2 = feature.canny(cannyimage, sigma=edges2sigma)
print(edges2.shape)

'''Displayment of pictures'''
fig, (ax1, ax2, ax3) = plt.subplots(nrows=1, ncols=3, figsize=(8, 3),
                                    sharex=True, sharey=True)

ax1.imshow(cannyimage, cmap=plt.cm.gray)
ax1.axis('off')
ax1.set_title('image', fontsize=10)

ax2.imshow(edges1, cmap=plt.cm.gray)
ax2.axis('off')
ax2.set_title(r'Canny filter, $\sigma=$' +str(edges1sigma), fontsize=10)

ax3.imshow(edges2, cmap=plt.cm.gray)
ax3.axis('off')
ax3.set_title(r'Canny filter, $\sigma=$'+str(edges2sigma), fontsize=10)


# viewer = ImageViewer(newimage)
# viewer.show()
# viewer2 = ImageViewer(edges2)
# viewer2.show()