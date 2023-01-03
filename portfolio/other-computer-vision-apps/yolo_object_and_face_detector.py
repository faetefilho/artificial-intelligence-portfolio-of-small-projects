# -*- coding: utf-8 -*-
"""yolo-object-and-face-detector.ipynb

Automatically generated by Colaboratory.

Original file is located at
    https://colab.research.google.com/drive/1iMgHt_oaKWtWcC_8gXRiM42T4AJgqGHb
"""

pip install cvlib

import cv2
import matplotlib.pyplot as plt
import numpy as np
import cvlib as cv # pip install cvlib
from cvlib.object_detection import draw_bbox

im = cv2.imread(r'/content/p2.jpeg')

im.shape

plt.imshow(im[:,:,::-1])

bbox , conf = cv.detect_face(im)

bbox

conf

labels = []
for i in range(len(conf)):
    labels.append('person')

labels

im2 = draw_bbox(im,bbox,labels,conf)
plt.imshow(im2[:,:,::-1])

im = cv2.imread(r'/content/a.jpg')
bbox , labels, conf = cv.detect_common_objects(im)

bbox

labels

conf

im2 = draw_bbox(im,bbox,labels,conf)
plt.imshow(im2[:,:,::-1])
