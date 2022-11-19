#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon May 23 12:39:19 2022

@author: tinho
"""
from tensorflow import keras
import tensorflow as tf
import os
import googleapiclient.discovery

# using teansor flow serving
# Export saved models
# model = keras.models.Sequential([])
# model.compile([])
# history = model.fit([])

model_version = '0001'
model_name = 'image_classifier_ch10'
model_path = os.path.join(model_name, model_version)
tf.saved_model.save(model, model_path)

# Loading a model and using li e a function
saved_model = tf.saved_model.load(model_path)
#y_pred = saved_model(X_new, training=False)

# or wrap this saved model in a keras model
inputs = keras.layers.Input(shape=...)
outputs = saved_model(inputs, training=False)
model = keras.models.Model(inputs=[inputs], outputs=[outputs])
y_pred = model.predict(X_new)

# Google cloud Platform
os.environ['GOOGLE_APPLICATION_CREDENTIALS'] = 'meta-matrix-351213-bc28ec7c16a8.json'

project_id = 'meta-matrix-351213'
model_id = 'image_classifier_ch10'
model_path = 'projects/{}/models/{}'.format(project_id, model_id)
ml_resource = googleapiclient.discovery.build('ml', 'v1').projects()

# prediction
input_data_json = {'signature_name': 'serving_default',
                   'instances': X_new.tolist()}
request = ml_resource.predict(name=model_path, body=input_data_json)
response = request.execute()
if 'error' in response:
    raise RunTimeError(reponse['error'])
np.array([pred[output_name] for pred in response['predictions']])

model_path2 = 'projects/meta-matrix-351213/ml-prod-filhof17-may22/image_classifier_ch10/0001'
model_path3 = 'projects/meta-matrix-351213/ml-prod-filhof17-may22/image_classifier_ch10'
