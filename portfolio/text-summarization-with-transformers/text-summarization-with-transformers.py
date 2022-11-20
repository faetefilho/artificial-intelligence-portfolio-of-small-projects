# -*- coding: utf-8 -*-
"""text-summarization-with-transformers.ipynb


Restart the runtime, before running Colab

Install Hugging Face Transformers
"""

pip install transformers

pip install sentencepiece==0.1.94

"""We will not display archtecture of the model (encoder layers, decode layers, feedforward sublayers)"""

display_architecture=False

import torch
import json

"""Import tokenizer, generation, and configuration classes"""

from transformers import T5Tokenizer, T5ForConditionalGeneration, T5Config

"""Import T5-large conditional generation model to generate text and the T5-large tokenizer"""

model = T5ForConditionalGeneration.from_pretrained('t5-large')

tokenizer = T5Tokenizer.from_pretrained('t5-large')

device = torch.device('cpu')

"""Exploring architecture"""

print(model.config)

print(model)

"""Lets create a summariazation function

"""

def summarize(text, ml):
  # strip remove spaces at the beginning and at the end of the string
  preprocess_text = text.strip().replace('\n', '')
  # apply T5 prefix
  t5_prepared_text = 'summarize: ' + preprocess_text
  print('Preprocessed and prepared text: \n', t5_prepared_text)
  return t5_prepared_text

"""lets check what we have so far"""

t5_prepared_text = summarize('today is a quite cloud day', 0)

"""Lets encode and return the tensors. "pt" to return PyTorch"""

# t5_prepared_text
tokenized_text = tokenizer.encode(t5_prepared_text, return_tensors="pt")
tokenized_text

"""Create summary with T5"""

summary_ids = model.generate(tokenized_text,
                             num_beams = 4,
                             no_repeat_ngram_size = 2,  # If set to int > 0, all ngrams of that size can only occur once
                             min_length = 30,  # The minimum length of the sequence to be generated
                             max_length = 50,  # The maximum length the generated tokens can have
                             # Whether to stop the beam search when at least num_beams sentences are finished per batch or not
                             early_stopping = True)

summary_ids[0]

"""Notes:
**Beam search** reduces the risk of missing hidden high probability word sequences by keeping the most likely num_beams of hypotheses at each time step and eventually choosing the hypothesis that has the overall highest probability.
\n Now lets decode

"""

output = tokenizer.decode(summary_ids[0], skip_special_tokens=True)

output

"""Lets repackage all in one function"""

def summarize_all(text, ml=50):
  # strip remove spaces at the beginning and at the end of the string
  preprocess_text = text.strip().replace('\n', '')
  # apply T5 prefix
  t5_prepared_text = 'summarize: ' + preprocess_text
  tokenized_text = tokenizer.encode(t5_prepared_text, return_tensors="pt")
  summary_ids = model.generate(tokenized_text,
                             num_beams = 4,
                             no_repeat_ngram_size = 2,  # If set to int > 0, all ngrams of that size can only occur once
                             min_length = 30,  # The minimum length of the sequence to be generated
                             max_length = ml,  # The maximum length the generated tokens can have
                             # Whether to stop the beam search when at least num_beams sentences are finished per batch or not
                             early_stopping = True)
  output = tokenizer.decode(summary_ids[0], skip_special_tokens=True)
  return output

"""lets apply to a text"""

text = """Investors weighed a batch of hawkish remarks from Federal Reserve officials Thursday morning. 
Minneapolis Fed President Neel Kashkari acknowledged that the risk of 
overshooting was present, as a lot of policy tightening still needs to work its 
way through the economy. Still, he asserted, he and his colleagues were "quite 
a ways away" from bringing down inflation"""
text

print("Number of characters:", len(text))
summary = summarize_all(text, ml=50)
print("summarized text: \n", summary)

"""Using GPT-3 from open ai"""
