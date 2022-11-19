#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Apr  1 15:55:39 2022

@author: tinho
"""
from sklearn.datasets import fetch_openml
from sklearn.linear_model import SGDClassifier
from sklearn.model_selection import cross_val_predict
from sklearn.metrics import confusion_matrix
from sklearn.metrics import precision_score, recall_score
from sklearn.metrics import precision_recall_curve
import matplotlib as mpl
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np


mnist = fetch_openml('mnist_784', version=1)
mnist.keys()

X, y = mnist['data'], mnist['target']
X.shape
y.shape

some_digit = X.iloc[0,]
some_digit_values = some_digit.values
some_digit_image = some_digit_values.reshape(28,28)

plt.imshow(some_digit_image, cmap='binary')
plt.axis('off')
plt.show()

y[0]
# cast to number for ML algo
y = y.astype(np.uint8)

# separating the data
X_train, X_test, y_train, y_test = X[:60000], X[60000:], y[:60000], y[60000:]

# train to only identify 5s
y_train_5 = (y_train == 5)
y_test_5 = (y_test == 5)

sgd_clf = SGDClassifier(random_state=42)
sgd_clf.fit(X_train, y_train_5)
# predict
sgd_clf.predict([some_digit])

# Using confusion matrix to evaluate results (precision & recall)
y_train_pred = cross_val_predict(sgd_clf, X_train, y_train_5, cv=3)
confusion_matrix(y_train_5, y_train_pred)
precision_score(y_train_5, y_train_pred)
recall_score(y_train_5, y_train_pred)
# score function for each intance that can be used for setting threshold
y_scores = sgd_clf.decision_function([some_digit])
# asks for prediction scores
y_scores = cross_val_predict(sgd_clf, X_train, y_train_5, cv=3, 
                             method='decision_function')
precisions, recalls, thresholds = precision_recall_curve(y_train_5, y_scores)

def plot_precision_recall_vs_threshold(precisions, recalls, thresholds):
    plt.plot(thresholds, precisions[:-1], 'b--', label='prediction')
    plt.plot(thresholds, recalls[:-1], 'g-', label='recall')
    
plot_precision_recall_vs_threshold(precisions, recalls, thresholds)
plt.show()