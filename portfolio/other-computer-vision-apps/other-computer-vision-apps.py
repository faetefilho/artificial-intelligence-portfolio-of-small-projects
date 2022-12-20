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