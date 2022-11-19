#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Mar 26 15:50:51 2022

@author: tinho
"""
import tensorflow as tf
from tensorflow import keras
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from PIL import Image
from sklearn.datasets import fetch_california_housing
from sklearn.model_selection import train_test_split
from sklearn.model_selection import RandomizedSearchCV
from sklearn.preprocessing import StandardScaler
import os
import time
from mymodule import build_model
from scipy.stats import reciprocal


fashion_mnist = keras.datasets.fashion_mnist
(X_train_full, y_train_full), (X_test, y_test) = fashion_mnist.load_data()

# 28x28 matrix of int 0 to 255for pixel intensity
X_train_full.shape
X_train_full.dtype

# scaling and creating validation set
X_valid, X_train = X_train_full[:5000]/255.0, X_train_full[5000:]/255.0
y_valid, y_train = y_train_full[:5000], y_train_full[5000:]

class_names = ['T-shirt/top', 'Trouser', 'Pullover', 'Dress', 'Coat', 'Sandal', 'Shirt', 'Sneaker', 'Bag', 'Ankle boot']

# build NN

model = keras.models.Sequential()
model.add(keras.layers.Flatten(input_shape=[28, 28]))
model.add(keras.layers.Dense(300, activation='relu'))
model.add(keras.layers.Dense(100, activation='relu'))
model.add(keras.layers.Dense(10, activation='softmax'))

# or equivalent

# model = keras.models.Sequential([
#     keras.layers.Flatten(input_shape=[28, 28]),
#     keras.layers.Dense(300, activation='relu'),
#     keras.layers.Dense(100, activation='relu'),
#     keras.layers.Dense(10, activation='softmax')
#     ])
#summary
model.summary()
keras.utils.plot_model(model, to_file='model.png')
model.layers
hidden1 = model.layers[1]
hidden1.name
model.get_layer('dense')
weights, biases = hidden1.get_weights()
# compile method to specify loss function
model.compile(loss='sparse_categorical_crossentropy',
              optimizer='sgd',
              metrics=['accuracy'])

# training and evaluation
# class_weight argument in fit if some classes are being overrepresented,
#those weight being used by keras to compute loss.
# For per instance weights use sample_weights to give preference to expert labeler
#over crowdsource labelers 
history = model.fit(X_train, y_train, epochs=30, validation_data=(X_valid, y_valid))
# plots
pd.DataFrame(history.history).plot(figsize=(8,5))
plt.grid(True)
plt.gca().set_ylim(0,1)
plt.show

# evaluation of the model
model.evaluate(X_test, y_test)

# making prediction
X_new = X_test[:3]
y_proba = model.predict(X_new)
y_proba.round(2)

# if interested in the highly estimated classes
y_pred = model.predict_classes(X_new)

np.array(class_names)[y_pred]

# Building a regression MLP using the sequential API
housing = fetch_california_housing()
X_train_full, X_test, y_train_full, y_test = train_test_split(housing.data, housing.target)

X_train, X_valid, y_train, y_valid = train_test_split(X_train_full, y_train_full)

scaler = StandardScaler()
X_train = scaler.fit_transform(X_train)
X_valid = scaler.transform(X_valid)
X_test = scaler.transform(X_test)

model = keras.models.Sequential([
    keras.layers.Dense(30, activation='relu', input_shape=X_train.shape[1:]),
    keras.layers.Dense(1)
    ])
model.compile(loss='mean_squared_error', optimizer='sgd')
history = model.fit(X_train, y_train, epochs=20, validation_data=(X_valid, y_valid))
mse_test = model.evaluate(X_test, y_test)
X_new = X_test[:3] #pretend those are new instances
y_pred = model.predict(X_new)

# Building complex models using the functional API: wide and deep neural network
input_ = keras.layers.Input(shape=X_train.shape[:1])
hidden1 = keras.layers.Dense(30, activation='relu')(input_)
hidden2 = keras.layers.Dense(30, activation='relu')(hidden1)
concat = keras.layers.Concatenate()([input_, hidden1])
output = keras.layers.Dense(1)(concat)
model = keras.Model(inputs=[input_], outputs=[output])
# now compile, train, evaluate, and make predictions

# Sending a subset to wide path and a subset though deep path
input_A = keras.layers.Input(shape=[5], name='wide_input')
input_B = keras.layers.Input(shape=[6], name='deep_input')
hidden1 = keras.layers.Dense(30, activation='relu')(input_B)
hidden2 = keras.layers.Dense(30, activation='relu')(hidden1)
concat = keras.layers.concatenate([input_A, hidden2])
output = keras.layers.Dense(1, name='output')(concat)
model = keras.Model(inputs=[input_A, input_B], outputs=[output])

model.compile(loss='mse', optimizer=keras.optimizers.SGD(lr=1e-3))

X_train_A, X_train_B = X_train[:,:5], X_train[:, 2:]
X_valid_A, X_valid_B = X_valid[:,:5], X_valid[:,2:]
X_test_A, X_test_B = X_test[:,:5], X_test[:,2:]
X_new_A, X_new_B = X_test_A[:3], X_test_B[:3]

history = model.fit((X_train_A, X_train_B), y_train, epochs=20,
                    validation_data=((X_valid_A, X_valid_B),y_valid))
mse_test = model.evaluate((X_test_A, X_test_B), y_test)
y_pred = model.predict((X_new_A, X_new_B))

# To save the model
model.save('my_keras_model.h5')
# load model, does not work with subclassing
model = keras.models.load_model('my_keras_model.h5')

# using callbacks to save at the end of each epoch
# after build and compile
checkpoint_cb = keras.callbacks.ModelCheckpoint('my_keras_model.h5')
history = model.fit(X_train, y_train, epochs=10, callbacks=[checkpoint_cb])
# interrupt training if no progress
early_stopping_cb = keras.callbacks.EarlyStopping(patience=10,
                                                  restore_best_weights=True)
history = model.fit(X_train, y_train, epochs=10, callbacks=[checkpoint_cb, early_stopping_cb])
# for more callbacks: keras.io/callbacks/

# Using tensor baord for visualization
root_logdir = os.path.join(os.curdir, 'my_logs')
run_id = time.strftime('run_%Y_%m_%d-%H_%M_%S')
run_logdir = os.path.join(root_logdir, run_id)

tensorboard_cb = keras.callbacks.TensorBoard(run_logdir)
history = model.fit(X_train, y_train, epochs=30, 
                    validation_data=(X_valid, y_valid),
                    callbacks=[tensorboard_cb])

# on fine tuning NN hyperparameters
writer = tf.summary.create_file_writer(run_logdir)
with writer.as_default():
    for step in range(1,1000+1):
        tf.summary.scalar('my_scalar', np.sin(step/10), step=step)
        data = (np.random.randn(100)+2)*step/100 # random data
        tf.summary.histogram('my hist', data, buckets=50, step=step)
        images = np.random.rand(2,32,32,3) # random 32x32 images
        tf.summary.image('my_image', images*step/1000, step=step)
        texts = ['The step is '+str(step), 'Its square is: '+str(step**2)]
        tf.summary.text('my text', texts, step=step)
        sine_wave = tf.math.sin(tf.range(12000)/48000*2*np.pi*step)
        audio = tf.reshape(tf.cast(sine_wave,tf.float32),[1,-1,1])
        tf.summary.audio('my_audio', audio, sample_rate=48000, step=step)

keras_reg = keras.wrappers.scikit_learn.KerasRegressor(build_model)
keras_reg.fit(X_train, y_train, epochs=100,
              validation_data=(X_valid, y_valid),
              callbacks=[keras.callbacks.EarlyStopping(patience=10)])
mse_test = keras_reg.score(X_test, y_test)
y_pred = keras_reg.predict(X_new)

# randomized search rather than grid search
param_distribs = {
    'n_hidden': [0,1,2,3],
    'n_neurons': np.arange(1,100),
    'learning_rate': reciprocal(3e-4, 3e-2),
    }

rnd_search_cv = RandomizedSearchCV(keras_reg, param_distribs, n_iter=10, cv=3)

rnd_search_cv.fit(X_train, y_train, epochs=100,
                  validation_data=(X_valid, y_valid),
                  callbacks=[keras.callbacks.EarlyStopping(patience=10)])





















