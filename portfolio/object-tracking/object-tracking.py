#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Feb 18 08:13:09 2023

@author: tinho
"""

import cv2
cv2.__version__

# tracker dictionary, list of useful tracker for object tracking
# might need to update your openCV:
# uninstall opencv-python
# pip install opencv-contrib-python -U

TrDict = {'csrt': cv2.TrackerCSRT_create,
          'kcf': cv2.TrackerKCF_create,
          'boosting': cv2.TrackerBoosting_create,
          'mil': cv2.TrackerMIL_create,
          'tld': cv2.TrackerTLD_create,
          'medianflow': cv2.TrackerMedianFlow_create,
          'mosse': cv2.TrackerMOSSE_create}
