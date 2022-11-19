#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun May  1 07:54:28 2022

@author: tinho
"""
import numpy as np
from tensorflow import keras

def generate_time_series(batch_size, n_steps):
    freq1, freq2, offset1, offset2, = np.random.rand(4, batch_size, 1)
    time = np.linspace(0,1,n_steps)
    series = 0.5*np.sin((time - offset1) * (freq1*10+10)) #wave 1
    series += 0.2*np.sin((time - offset2) * (freq2*20+20)) #wave 2
    series += 0.1*(np.random.rand(batch_size, n_steps)-0.5) # noise
    return series[...,np.newaxis].astype(np.float32)

# creating training, validation and test
n_steps=50
series = generate_time_series(10000, n_steps+1)
X_train, y_train = series[:7000, :n_steps], series[:7000, -1]
X_valid, y_valid = series[7000:9000, :n_steps], series[7000:9000, -1]
X_test, y_test = series[9000:, :n_steps], series[9000:, -1]

# simple RNN
model = keras.models.Sequential([
    keras.layers.SimpleRNN(1, input_shape=[None, 1])
    ])

# Deep RNN
model = keras.models.Sequential([
    keras.layers.SimpleRNN(20, return_sequences=True, input_shape=[None, 1]),
    keras.layers.SimpleRNN(20, return_sequences=True),
    keras.layers.SimpleRNN(1)
    ])

# forecasting several steps ahead, one by one by making one prediction, adding
# the prediction, then assuming that is the actual new point, then making
# another prediction and so on
series = generate_time_series(1, n_steps+10)
X_new, Y_new = series[:, :n_steps], series[:, n_steps:]
X = X_new
for steps_ahead in range(10):
    y_pred_one = model.predict(X[:, steps_ahead:])[:, np.newaxis, :]
    X = np.concatenate([X, y_pred_one], axis=1)
    
Y_pred = X[:, n_steps:]

# second option for time series
n_steps=50
series = generate_time_series(10000, n_steps+10)

# third option
Y = np.empty((10000, n_steps, 10))
for step_ahead in range(1, 10+1):
    Y[:,:,step_ahead-1] = series[:, step_ahead:step_ahead + n_steps, 0]
Y_train = Y[:7000]
Y_valid = Y[7000:9000]
Y_test = Y[9000:]



