# create a completion
completion = openai.Completion.create(engine="ada", prompt="Hello world")

# image generation
image_resp = openai.Image.create(prompt="a person playing with a virtual reality headset", 
                                 n=1, 
                                 size="512x512")
image_resp["data"][0]

# create a completion
completion = openai.Completion.create(
  model="text-davinci-003",
  prompt="what are the key software and programming languages used by data scientist?",
  # Most models have a context length of 2048 tokens
  max_tokens=200, # max number of tokens to generate for completion
  # Higher values means the model will take more risks. 
  # Try 0.9 for more creative applications, and 0 (argmax sampling) 
  # for ones with a well-defined answer.
  temperature=0.5
  
)

print(completion['choices'][0]['text'])

## Grammar correction
response = openai.Completion.create(
  engine="davinci",
  prompt="Original: She no went to the market.\nStandard American English:",
  temperature=0,
  max_tokens=60,
  top_p=1.0,
  frequency_penalty=0.0,
  presence_penalty=0.0,
  stop=["\n"]
)
print(response)
response["choices"][0]["text"]

# Translation
response = openai.Completion.create(
  engine="davinci",
  prompt="Original: She no went to the market.\n French with no contractions:",
  temperature=0, 
  max_tokens=60,
  top_p=1.0,
  frequency_penalty=0.0,
  presence_penalty=0.0,
  stop=["\n"]
)
r = (response["choices"][0])
print(r["text"])

# instruction series
response = openai.Completion.create(
  engine="davinci-instruct-beta",
  prompt="Write a plan of actions based on these instructions:\n\nStart Internet Explorer.\nYou need to eventually click on the advanced tab.\nBut before that, click on the Internet options on the tools menu.\nAfter the click on the advanced tab, click to clear or select the enable\npersonalized favorite menu check box.\n\n\nACTIONS:",
  temperature=0,
  max_tokens=120,
  top_p=1,
  frequency_penalty=0,
  presence_penalty=0
)
r = (response["choices"][0])
print(r["text"])

# translating from one programming language to another

response = openai.Completion.create(
  engine="davinci-codex",
  prompt="##### Translate this function  from Python into Javascript\n### Python\n    \n    def predict_proba(X: Iterable[str]):\n        return np.array([predict_one_probas(tweet) for tweet in X])\n    \n### Javascript\n    \n    function predict_proba(X: Iterable[str]):\n        return np.array([predict_one_probas(tweet) for tweet in X])\n\n# Now we can use the function in Javascript\n%%",
  temperature=0,
  max_tokens=54,
  top_p=1,
  frequency_penalty=0,
  presence_penalty=0,
  stop=["###"]
)
r = (response["choices"][0])
print(r["text"])

# Tweet classifier
response = openai.Completion.create(
  engine="davinci",
  prompt="This is a tweet sentiment classifier\nTweet: \"I loved the new Batman movie!\"\nSentiment: Positive\n###\nTweet: \"I hate it when my phone battery dies\"\nSentiment: Negative\n###\nTweet: \"My day has been 👍\"\nSentiment: Positive\n###\nTweet: \"This is the link to the article\"\nSentiment: Neutral\n###\nTweet text\n\n\n1. \"I loved the new Batman movie!\"\n2. \"I hate it when my phone battery dies\"\n3. \"My day has been 👍\"\n4. \"This is the link to the article\"\n5. \"This new music video blew my mind\"\n\n\nTweet sentiment ratings:\n1: Positive\n2: Negative\n3: Positive\n4: Neutral\n5: Positive\n\n\n###\nTweet text\n\n\n1. \"I can't stand homework\"\n2. \"This sucks. I'm bored 😠\"\n3. \"I can't wait for Halloween!!!\"\n4. \"My cat is adorable ❤️❤️\"\n5. \"I hate chocolate\"\n\n\nTweet sentiment ratings:\n1.",
  temperature=0.3,
  max_tokens=60,
  top_p=1,
  frequency_penalty=0,
  presence_penalty=0,
  stop=["###"]
)
r = (response["choices"][0])
print(r["text"])

# text summarization
response = openai.Completion.create(
  engine="davinci",
  prompt="My second grader asked me what this passage means:\n\"\"\"\nJupiter is the fifth planet from the Sun and the largest in the Solar System. It is a gas giant with a mass one-thousandth that of the Sun, but two-and-a-half times that of all the other planets in the Solar System combined. Jupiter is one of the brightest objects visible to the naked eye in the night sky, and has been known to ancient civilizations since before recorded history. It is named after the Roman god Jupiter.[19] When viewed from Earth, Jupiter can be bright enough for its reflected light to cast visible shadows,[20] and is on average the third-brightest natural object in the night sky after the Moon and Venus.\n\"\"\"\nI rephrased it for him, in plain language a second grader can understand:\n\"\"\"\n",
  temperature=0.5,
  max_tokens=100,
  top_p=1,
  frequency_penalty=0.2,
  presence_penalty=0,
  stop=["\"\"\""]
)
r = (response["choices"][0])
print(r["text"])

# Parse unstructured data
#prompt="There are many fruits that were found on the recently discovered planet Goocrux. There are neoskizzles that grow there, which are purple and taste like candy. There are also loheckles, which are a grayish blue fruit and are very tart, a little bit like a lemon. Pounits are a bright green color and are more savory than sweet. There are also plenty of loopnovas which are a neon pink flavor and taste like cotton candy. Finally, there are fruits called glowls, which have a very sour and bitter taste which is acidic and caustic, and a pale orange tinge to them.\n\nPlease make a table summarizing the fruits from Goocrux\n| Fruit | Color | Flavor |\n| Neoskizzles | Purple | Sweet |\n| Loheckles | Grayish blue | Tart |\n"

response = openai.Completion.create(
  engine="davinci",
  prompt="There are many fruits that were found on the recently discovered planet Goocrux. There are neoskizzles that grow there, which are purple and taste like candy. There are also loheckles, which are a grayish blue fruit and are very tart, a little bit like a lemon. Pounits are a bright green color and are more savory than sweet. There are also plenty of loopnovas which are a neon pink flavor and taste like cotton candy. Finally, there are fruits called glowls, which have a very sour and bitter taste which is acidic and caustic, and a pale orange tinge to them.\n\nPlease make a table summarizing the fruits from Goocrux\n| Fruit | Color | Flavor |\n| Neoskizzles | Purple | Sweet |\n| Loheckles | Grayish blue | Tart |\n",
  temperature=0,
  max_tokens=100,
  top_p=1,
  frequency_penalty=0,
  presence_penalty=0,
  stop=["\n\n"]
)
r = (response["choices"][0])
print(r["text"])

response = openai.Completion.create(
  engine="davinci",
  prompt="There are many fruits that were found on the recently discovered planet Goocrux. There are neoskizzles that grow there, which are purple and taste like candy. There are also loheckles, which are a grayish blue fruit and are very tart, a little bit like a lemon. Pounits are a bright green color and are more savory than sweet. There are also plenty of loopnovas which are a neon pink flavor and taste like cotton candy. Finally, there are fruits called glowls, which have a very sour and bitter taste which is acidic and caustic, and a pale orange tinge to them.\n\nPlease make a table summarizing all the fruits from Goocrux\n| Fruit | Color | Flavor |\n| Loheckle | Grayish blue | Tart |\n",
  temperature=0,
  max_tokens=100,
  top_p=1,
  frequency_penalty=0,
  presence_penalty=0,
  stop=["\n\n"]
)
r = (response["choices"][0])
print(r["text"])







