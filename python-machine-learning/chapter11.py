#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Apr  2 15:48:51 2022

@author: tinho
"""

from tensorflow import keras

# to use other than Glorot defaults
keras.layers.Dense(10, activation='relu', kernel_initialization='he_normal')

# implementing batch normlization in keras
model = keras.models.Sequential([
    keras.layers.Flatten(input_shape=[28, 28]),
    keras.layers.BatchNormalization(),
    keras.layers.Dense(300, activation='elu', kernel_initializer='he_normal'),
    keras.layers.BatchNormalization(),
    keras.layers.Dense(100, activation='elu', kernel_initializer='he_normal'),
    keras.layers.BatchNormalization(),
    keras.layers.Dense(10, activation='softmax'),
    ])

model.summary()

[(var.name, var.trainable) for var in model.layers[1].variables]

model.layers[1].updates