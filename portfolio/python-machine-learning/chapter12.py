#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Apr 16 09:55:50 2022

@author: tinho
"""
import tensorflow as tf
import numpy as np

#matrix
tf.constant([[1,2,3],
             [4,5,6]])
# scalar
tf.constant(42)

# type and shape
t=tf.constant([[1.,2,3],
             [4,5,6]])
t.shape
t.dtype

#indexing
t[:,1:]

#opeartions
t+10
tf.square(t)
tf.transpose(t)

# tensor and Numpy
a = np.array([2., 4, 5])
tf.constant(a)
t.numpy
tf.square(a)
np.square(t)

# type conversions: give an exception, tf is default 32 bit
tf.constant(2.)+tf.constant(42)
tf.constant(2.)+tf.constant(42, dtype=tf.float64)

# variables, for operations, since tf.tensor is imutable
v = tf.Variable([[1.,2,3],[4,5,6]])
v.assign(2*v)
v[0,1].assign(42)
v[:,2].assign([0,1.])
v.scatter_nd_update(indices=[[0,1], [1,2]],updates=[100.,200])

# custom loss functions, use tf operations to benefit from tf graph features
def huber_fn(y_true, y_pred):
    error = y_true - y_pred
    is_small_error = tf.abs(error)<1
    squared_loss = tf.square(error)/2
    linear_loss = tf.abs(error)-0.5
    return tf.where(is_small_error, squared_loss, linear_loss)

# add to keras model
model.compile(loss=huber_fn, optimizer='nadam')
model.fit(X_train, y_train)

# saving & loading models that contains custom components
model = keras.models.load_model('my_model_with_a_custom_loss.h5',
                                custom_objects={'huber_fn': huber_fn})
# custom activation functions, initializers, regularizers, and constraints

# return value is just tf.nn.softplus(z)
def my_softplus(z):
    return tf.math.log(tf.exp(z)+1)
# glorot initializer
def my_glorot_initializer(shape, dtype=tf.float32):
    stddev = tf.sqrt(2./(shape[0]+shape[1]))
    return tf.random.normal(shape, stddev=stddev, dtype=dtype)
# l1 regulirizer
def my_l1_regularizer(weights):
    return tf.reduce_sum(tf.abs(0.01*eights))
# ensure weights are positive
def my_positive_weights(weights):
    return tf.where(weights<0, tf.zeros_like(weights), weights)

# then use them normally
layer = keras.layers.Dense(30, activation=my_softplus,
                           kernel_initializer=my_glorot_initializer,
                           kernel_regularizer=my_l1_regularizer,
                           kernel_constraint=my_positive_weights)

# custom metrics, using huber previously creted
model.compile(loss='mse', optimizer='nadam', metrics=[create_huber(2.0)])



































