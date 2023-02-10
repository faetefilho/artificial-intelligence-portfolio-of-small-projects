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
#  pre-trained on millions of text instances and labels, many languages avail
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
print(span.start, span.end)

# language pipelines such as pre-trained English have 
# many attributes, here a few:
print("Index :      ", [token.i for token in doc[:6]])
print("Text :       ", [token.text for token in doc[:6]])
print("is_alpha :   ", [token.is_alpha for token in doc[:6]])
print("is_punct :   ", [token.is_punct for token in doc[:6]])
print("Like_num :   ", [token.like_num for token in doc[:6]])
print("Base Word :  ", [token.lemma_ for token in doc[:6]])

# vocab is shared between documents
nlp.vocab
# the doc object only contains the words from txt
doc.vocab

# spacy communicates with hashes
nlp.vocab.strings["green"]
nlp.vocab.strings[3487151913243070096]

# when you look words from the vocan you are looking up lexeme
lexeme = nlp.vocab["green"]
type(lexeme)

print(lexeme.text, lexeme.orth, lexeme.is_digit)

# we can create docs manually
from spacy.lang.en import English
from spacy.tokens import Doc

nlp = English()

words = ["I", "like", "Brazil", "!"]
spaces = [True, True, False, False]

doc = Doc(nlp.vocab, words=words, spaces=spaces)

len(doc)
doc.text

# same with span
from spacy.tokens import Span

span = Span(doc,0, 1)

span.text

# Name Entity Recognition
txt = """" Cleopatra wasn't actually Egyptian! 
         As far as historians can tell, Egypt's 
         famous femme fatal was actually Greek!. 
         She was a descendant of Alexander the Great's
         Macedonian general Ptolemy"""
         

doc = nlp(txt)

for ent in doc.ents:
    print(f"{ent.text:<20}{ent.label_:<20}")
    
spacy.explain("NORP")

# using the visual entity tagger

from spacy import displacy

displacy.render(doc, style="ent")

# Lets manually tag alexander as a person

# extract name as span first
#from spacy.tokens import Span

alexander = Span(doc, 32, 35, label="PERSON")
alexander

# update the ent list
doc.ents = list(doc.ents) + [alexander]

# token's part-of-speech tag and its syntactic dependency
txt = "The first footprints on the moon will remain there for a million years"

doc = nlp(txt)

print(
    f"{'Text':<20} {'Part-of-speech':<20} "
    f"{'Dependency':<20} {'Dependency text':<20}\n"
)

for token in doc:
    print(f"{token.text:<20} {token.pos_:<20} "
          f"{token.dep_:<20} {token.head.text:<20}")

# explanation for some of the stuff in the table
pos_tags = ["DET", "AUX", "ADP"]
dep_tags = ["amod", "nsubj", "nummod"]

for pos in pos_tags:
    print(pos, "-->", spacy.explain(pos))

for dep in dep_tags:
    print(dep, "-->", spacy.explain(dep))
    
# extract noum chunks

txt = """The teddy bear is named after President Theodore Roosevelt. 
         After he refused to shoot a captured black bear on a hunt, 
         a stuffed-animal maker decided to create
         a bear and name it after the president."""

doc = nlp(txt)

for chunk in doc.noun_chunks:
    print(chunk.text)

# create a pattern on the dictionary so alexander the great is one token
# Create a pattern
# is_alpha:	Does the token consist of alphabetic characters?
# is_title:	Is the token in titlecase?
# is_stop:	Is the token part of a “stop list”?
pattern = [
    {"IS_ALPHA": True, "IS_TITLE": True},
    {"IS_STOP": True},
    {"IS_ALPHA": True, "IS_TITLE": True},
]

# create a matcher for the object

from spacy.matcher import Matcher

txt = """" Cleopatra wasn't actually Egyptian! 
         As far as historians can tell, Egypt's 
         famous femme fatal was actually Greek!. 
         She was a descendant of Alexander the Great's
         Macedonian general Ptolemy"""
         

# Init the matcher with the shared vocab
matcher = Matcher(nlp.vocab)

# Add the pattern to the matcher
matcher.add("TITLED_PERSON", [pattern])



# Word Vector and semantic similarity
doc1 = nlp("What a lukeworm sentiment.")
doc2 = nlp("What a short sentence.")

doc1.similarity(doc2)
# All doc, token and span objects have this similarity method

# can compare to each other
doc1[0:2].similarity(doc1[3])

# The similarity is calculated using word vectors, which are 
# multi-dimensional mathematical representations of words
array = doc1[0].vector

array.shape

array[:10]

nlp.pipe_names


# add pipeline that adds the conqueror's name as an entity
from spacy.language import Language
#from spacy.matcher import Matcher
from spacy.util import filter_spans

#nlp = spacy.load("en_core_web_sm")

@Language.component("titled_person")
def titled_person(doc):
    pattern = [
        {"IS_ALPHA": True, "IS_TITLE": True},
        {"IS_STOP": True},
        {"IS_ALPHA": True, "IS_TITLE": True},
    ]
    # Create the matcher
    matcher = Matcher(nlp.vocab)
    # Add the pattern
    matcher.add("TITLED_PERSON", [pattern])

    matches = matcher(doc)
    matched_spans = [Span(doc, start, end, label="PERSON") for _, start, end in matches]

    # Filter the entities for potential overlap
    filtered_matches = filter_spans(list(doc.ents) + matched_spans)
    # Add the matched spans to doc's entities
    doc.ents = filtered_matches

    return doc

nlp.add_pipe("titled_person")
#nlp.add_pipe("titled_person", first=True)  # Beginning
#nlp.add_pipe("titled_person", after="parser")  # After parser
#nlp.add_pipe("titled_person", before="tagger") # Before POS tagger

# lets test it now
txt = """Cleopatra wasn't actually Egyptian! 
         As far as historians can tell, Egypt's 
         famous femme fatal was actually Greek!. 
         She was a descendant of Alexander the Great's
         Macedonian general Ptolemy"""

doc = nlp(txt)

nlp.pipe_names

doc.ents























