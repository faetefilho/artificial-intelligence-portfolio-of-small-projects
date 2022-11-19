#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue May 17 14:58:26 2022

@author: tinho
"""
import tensorflow as tf
import tensorflow_datasets as tfds
from tensorflow import keras
import numpy as np

shakespeare_url = 'https://holm.info/shakespeare' # shortcut URL
shakespeare_url='https://raw.githubusercontent.com/karpathy/char-rnn/master/data/tinyshakespeare/input.txt'

filepath = keras.utils.get_file('shakespeare.txt', shakespeare_url)
with open(filepath) as f:
    shakespeare_text = f.read()

# tokenize, char_level = true to get character level tokenization rather than 
# word level tokens
tokenizer = keras.preprocessing.text.Tokenizer(char_level=True)
tokenizer.fit_on_texts([shakespeare_text])

# see inside
tokenizer.texts_to_sequences(['First'])
tokenizer.texts_to_sequences(['first'])
#tokenizer.sequences_to_texts([20, 6, 9, 8, 3]) # produces error
tokenizer.sequences_to_texts([[20, 6, 9, 8, 3]])
max_id = len(tokenizer.word_index)  # number of distinct characters
dataset_size = tokenizer.document_count

[encoded] = np.array(tokenizer.texts_to_sequences([shakespeare_text]))-1

# sliptting a sequential dataset
train_size = dataset_size *90//100
train_size = len(encoded)*90//100
dataset = tf.data.Dataset.from_tensor_slices(encoded[:train_size])

# Chopping sequential dataset into multiple windows
n_steps = 100
window_length = n_steps + 1 # target = input shifted 1 character ahead
dataset = dataset.window(window_length, shift=1, drop_remainder=True)

# cannot use nested dataset directly for training, as model expect tensors
# need to convert to flat dataset

dataset = dataset.flat_map(lambda window: window.batch(window_length))

batch_size = 32
dataset = dataset.shuffle(10000).batch(batch_size)
dataset = dataset.map(lambda windows: (windows[:,:-1], windows[:,1:]))

dataset = dataset.map(lambda X_batch, Y_batch: (tf.one_hot(X_batch, depth=max_id), Y_batch))

dataset = dataset.prefetch(1)

model = keras.models.Sequential([
    keras.layers.GRU(128, return_sequences=True, input_shape=[None, max_id],
                     dropout=0.2, recurrent_dropout=0.2),
    keras.layers.GRU(128, return_sequences=True,
                     dropout=0.2, recurrent_dropout=0.2),
    keras.layers.TimeDistributed(keras.layers.Dense(max_id, activation='softmax'))
    ])

model.compile(loss='sparse_categorical_crossentropy', optimizer='adam')

history = model.fit(dataset, epochs=20)

# preprocess to use prediction
def preprocess(texts):
    X = np.array(tokenizer.texts_to_sequences(texts))-1
    return tf.one_hot(X, max_id)

# do prediction
X_new = preprocess(['How are yo'])
Y_pred = np.argmax(model(X_new), axis=-1)
tokenizer.sequences_to_texts(Y_pred+1)[0][-1] #first sentence last char

tf.random.set_seed(42)

# generate new text
def next_char(text, temperature=1):
    X_new = preprocess([text])
    y_proba = model(X_new)[0, -1:, :]
    rescaled_logits = tf.math.log(y_proba)/temperature
    char_id = tf.random.categorical(rescaled_logits, num_samples=1)+1
    return tokenizer.sequences_to_texts(char_id.numpy())[0]

next_char("How are yo", temperature=1)

# reteatedly call next char to get the next character
def complete_text(text, n_chars=50, temperature=1):
    for _ in range(n_chars):
        text += next_char(text, temperature)
    return text

# generate some texts
print(complete_text('t', temperature=0.2))
print(complete_text('w', temperature=1))
print(complete_text('h', temperature=2))

# creating statefull RNN
dataset = tf.data.Dataset.from_tensor_slices(encoded[:train_size])
dataset = dataset.window(window_length, shift=n_steps, drop_remainder=True)
dataset = dataset.flat_map(lambda window: window.batch(window_length))
batch_size=1
dataset = dataset.batch(1)
dataset = dataset.map(lambda windows: (windows[:,:-1], windows[:,1:]))
dataset = dataset.map(lambda X_batch, Y_batch: (tf.one_hot(X_batch, depth=max_id), Y_batch))
dataset = dataset.prefetch(1)

model = keras.models.Sequential([
    keras.layers.GRU(128, return_sequences=True, stateful=True, 
                     dropout=0.2, recurrent_dropout=0.2,
                     batch_input_shape=[batch_size, None, max_id]),
    keras.layers.GRU(128, return_sequences=True, stateful=True,
                     dropout=0.2, recurrent_dropout=0.2),
    keras.layers.TimeDistributed(keras.layers.Dense(max_id, activation='softmax'))
    ])

# reset states before we go back to the begining of the text
class ResetStatesCallback(keras.callbacks.Callback):
    def on_epoch_begin(self, epoch, logs):
        self.model.reset_states()

# compile
model.compile(loss='sparse_categorical_crossentropy', optimizer='adam')
model.fit(datasetepochs=50, callback=[ResetStatesCallback()])

# Sentiment analysis
(X_train, y_train), (X_test, y_test) = keras.datasets.imdb.load_data()
X_train[0][:10]

# decode 
word_index = keras.datasets.imdb.get_word_index()
id_to_word = {id_ +3:word for word, id_ in word_index.items()}
for id_, token in enumerate(('pad', '<sos>', '<unk>')):
    id_to_word[id_] = token
    
' '.join([id_to_word[id_] for id_ in X_train[0][:10]])

# reusing embeddings
import tensorflow_hub as hub

model = keras.Sequential([
    hub.KerasLayer('https://tfhub.dev/google/tf2-preview/nnlm-en-dim50/1',
                   dtype=tf.string, input_shape=[], output_shape=[50]),
    keras.layers.Dense(128, activation='relu'),
    keras.layers.Dense(1, activation='sigmoid')
    ])

model.compile(loss='binary_crossentropy', optimizer='adam', metrics=['accuracy'])

#load dataset and train the model
datasets, info = tfds.load('imdb_reviews', as_supervised=True, with_info=True)
train_size = info.splits['train'].num_examples
batch_size = 32
train_set = datasets['train'].batch(batch_size).prefetch(1)
history = model.fit(train_set, epochs=5)






































