#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Dec 20 17:55:29 2022

@author: tinho
"""

# PANORAMA APPLICATION

# Get images
im1 = cv2.imread(r'C:\images\1.jpg')
im2 = cv2.imread(r'C:\images\2.jpg')
im3 = cv2.imread(r'C:images\3.jpg')

# plot images
plt.subplot(131)
plt.imshow(im1[:,:,::-1]) # opencv is BGR
plt.subplot(132)
plt.imshow(im2[:,:,::-1])
plt.subplot(133)
plt.imshow(im3[:,:,::-1])
plt.show()

# append images as required
imgs = []
imgs.append(im1)
imgs.append(im2)
imgs.append(im3)

# perform stitching
M = cv2.Stitcher.create(cv2.Stitcher_PANORAMA)
status,pano = M.stitch(imgs)

# plot created panorama
plt.imshow(pano[:,:,::-1])


# BLURRING< EDGE< SHARPENING

import numpy as np
import matplotlib.pyplot as plt
import cv2
from scipy import signal

# path to image
im = plt.imread(r'C:\image.png')[:,:,:3]
# gray scale
imGray = cv2.cvtColor(im,cv2.COLOR_RGB2GRAY)
# blurring, sum of mask is one
smoothingMask = np.ones((15,15))/(15*15)
# symm boundary symmetrically copies
imBlurred = signal.convolve2d(imGray,smoothingMask,
                             boundary='symm',mode='same')
# plots
fig,(ax1,ax2) = plt.subplots(1,2,figsize=(10,15))
ax1.imshow(imGray,cmap='gray')
ax2.imshow(imBlurred,cmap='gray')

# Creates 2D masks,  
xMask = np.array([[-1,0,1],[-1,0,1],[-1,0,1]])
yMask = xMask.T.copy()

# convolve original grayscale with masks
fx = signal.convolve2d(imGray,xMask,boundary='symm',mode='same')
fy = signal.convolve2d(imGray,yMask,boundary='symm',mode='same')

# they should have same shape
fx.shape
imGray.shape

# Grading magnitude, then plots
Gm = (fx**2 + fy**2)**0.5
plt.imshow(Gm,cmap = 'gray')

# create a threshold
th = Gm.max()-4*Gm.std()
th

# Adge image, need to try a few threshold
E = Gm>th
plt.imshow(Gm>0.1,cmap = 'gray')

# sharpening, one of doing it
imSharped = imBlurred + 0.5*Gm

# plot ot compare
fig,(ax1,ax2) = plt.subplots(1,2,figsize=(10,15))
ax1.imshow(imBlurred,cmap='gray')
ax2.imshow(imSharped,cmap = 'gray')

# CANNY EDGE DETECTOR

#
import cv2
import matplotlib.pyplot as plt
import numpy as np

#
imPth = r'C:\cm.jpg'
img = plt.imread(imPth)

#
plt.imshow(img,cmap='gray')

# canny function, threshold might need to be adjusted
E = cv2.Canny(img,150,250)

# plot results
plt.subplot(121)
plt.imshow(img,cmap='gray')
plt.axis('off')
plt.subplot(122)
plt.imshow(E,cmap='gray')
plt.axis('off')
plt.show()

# create gaussian kernel using openCV, sum will equal 1
cv2.getGaussianKernel(5, 1)











