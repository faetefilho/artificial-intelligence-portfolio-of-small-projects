#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Feb  9 09:55:53 2023

@author: tinho
"""

# 

# pip install -U spacy

# there are three diffferent pipelines
# en_core_web_sm, 12MB
# en_core_web_md, 31MB
# en_core_web_lg, 382MB

import spacy

txt = "Where do babies come from? let me tell you the answer to that. "

# create a language object
nlp = spacy.load("en_core_web_sm")

# create the doc object, this is just an iterator
doc = nlp(txt)

for token in doc:
    print(token)    

type(token)
len(doc)

# if you extract more than one token, you have a span
span = doc[:6]
type(span)
span.text

# language pipelines such as pre-trained English have 
# many attributes, here a few:
print("Index :      ", [token.i for token in doc[:6]])
print("Text :       ", [token.text for token in doc[:6]])
print("is_alpha :   ", [token.is_alpha for token in doc[:6]])
print("is_punct :   ", [token.is_punct for token in doc[:6]])
print("Like_num :   ", [token.like_num for token in doc[:6]])
print("Base Word :  ", [token.lemma_ for token in doc[:6]])