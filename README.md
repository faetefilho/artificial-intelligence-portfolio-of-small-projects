# Artificial Intelligence and Machine Learning - A Compilation of Examples
This is a collection of small projects covering different topics in A.I. and M.L. to be used as a training resource for students. Some of the projects were collected from online resources and adapted, and some are original projects:

- [Deep Artificial Neural Network for Regression](/portfolio/deep-ann-for-regression/deep_ann_for_regression.ipynb): This application focuses on ANN for determining housing prices on a large dataset. The ANN can be easily improved/modified for deeper and wider configuration.
- [Object detection with R-CNN](/portfolio/R-CNN-object-detection/R_CNN_object_detection.ipynb): This is the region proposal based CNN to identify/localize objects within an image. Uses VGG16
- [Anomaly detection of credit card transactions using autoencoders](portfolio/anomaly-detection-of-credit-card-transactions-using-autoencoders/anomaly_detection_credit_card_transaction_autoencoder.ipynb
): We are trying to differentiate between normal and abnormal credit card transactions. The reconstruction error scores toguether with threshold are used to help us identify an anomaly. 
- [Multiple Linear Regression with SKLearn](/portfolio/multiple-linear-regression): Exploratory data analysis and linear regression on a dataset with multiple columns (numerical/categorical).
- [Telecom Customers Churn Prediction](/portfolio/machine-learning-classification/): Various classification algorithms are tested for this case study such as logistic regression, support vector machine, random forest, k-nearest neighbour and naive bayes. Performance comparison is evaluated for all five models.
- [Credit Card Default Prediction](/portfolio/credit-card-default-prediction/credit-card-default-prediction-with-xgboost.ipynb): The technique used in this application is XGBoost algorithm.
- [Cardiovascular Disease Prediction](/portfolio/cardiovascular-disease-prediction/cardiovascular-disease-detection.ipynb): Detect the presence or absence of cardiovascular disease in person based on several given features. First half of notebook uses XGBoost module.
- [Kyphosis classification](/portfolio/k-nearest-neighbors/knn-for-kyphosis-disease-classification.ipynb): Classification application using K nearest neighbors.

## Computer Vision
- [Simple ANN with PyTorch](/portfolio/simple-ann-with-pytorch): A simple ANN using Pytorch module for regression. 
- [Object detection with YOLOv4](/portfolio/object-detection-with-yolov4/YOLO_object_detection.ipynb): Uses YOLOv4 to classify and localize buses and trucks. Builds upon available code from other GitHub repositories.
- [Image Classification With PyTorch (aka Misha detector)](/portfolio/image-classification-pytorch/cnn_for_real_world_image_classification.ipynb): This artificial intelligence based application uses a NVIDIA Tesla T4 (16GDDR6) GPU to train a convolutional neural network to, among other things, identify/classify the most adorable dog, Misha. 

## AWS SageMaker
- [Linear Learner](/portfolio/linear-learner): This Python script creates S3 bucket, uploads data, prepare data, create model, train and make predictions. All tasks are performed programatically on AWS. 
- [Multiple Linear Regression with XGBoost](/portfolio/mlr-with-sklearn): Determine life expectancy based on a number of features with a sizeable number of missing features. This uses SKlearn and XGBoost algorithm.
- [XGBoost with Amazon SageMaker](/portfolio/xgboost-with-sagemaker/): Exploratory data analysis, model training, and deployment to an endpoint, and inference. This dataset contains missing data.  
- [Hyperparameter optimization with scikit-learn/SageMaker & XGBoost](/portfolio/hyperparameter-optimization-for-xgboost-in-sk-learn): Ride sharing use prediction based on a number of parameters. Here we use gridsearch, random search, and bayesian optimization for hyperparameter selection of a XGBoost based model.
- [Credit Card Default Prediction using SageMaker and XGBoost](/portfolio/credit-card-default-prediction/credit-card-default-prediction-with-xgboost.ipynb): Here we go through a already cleaned dataset and use python XGBoost modules and AWS XGBoost algorithm to predict if clients are going to default on their loans.
- [Cardiovascular Disease Prediction](/portfolio/cardiovascular-disease-prediction/cardiovascular-disease-detection.ipynb): Detect the presence or absence of cardiovascular disease in person based on several given features. We use both python and AWS XGBoost algos.
- [Kyphosis classification with k nearest neighbors](/portfolio/k-nearest-neighbors/knn-for-kyphosis-disease-classification.ipynb): Application to medical field using python modules and AWS endpoint for classification. Additional M.L. techniques are used towards the end of the notebook for comparison. 
- [AutoGluon for Regression](/portfolio/autogluon-for-regression/autogluon-for-regression.ipynb): This is the library behind SageMaker Autopilot. It allows for quick prototyping of AI/ML models using a few simple lines of code. Autogluon works with text, image and tabular datasets. 


## Power & Energy
- [Differential Evolution for Controller optimization (MATLAB)](/portfolio/differential-evolution/): Series of MATLAB scripts designed to use differential evolution to determine optimal motor control parameters. This work was later published in a IEEE Journal.
- [K-means Clustering For Voltage Estimation (to be added)]:
- [Neural Networks for converter control (to be added)]:

## Natural Language Processing
- [Text Summarization with Transformers](/portfolio/text-summarization-with-transformers): An application of text-to-text transfer transformer (T5) to summarize a sample text file
- [Sentiment Analysis (Transformers)](/portfolio/sentiment_analysis_with_RoBERTa_large/sentiment_analysis_with_RoBERTa_large.ipynb): Analyze a number of different techniques to analyze sentiment. We look into Allen, Hugginface and OpenAI models for a number of easy and challenging tasks within sentiment analysis.
- [Sentiment Analysis on Twitter](/portfolio/sentiment-analysis/Twitter_Sentiment_Analysis.ipynb): We look at a couple thounsands of tweets and test Random Forests (RF), Support Vector Machine (SVM), and Naive Bayes (NB) to try to predict if a tweet is likely to contain Fake News.

## Software Development:
- [Futures market algorithmic trading system](/portfolio/algo-trading-system): This quite simple algo was developed in TradeStation EasyLanguage to trade Wheat futures 420 minutes time frame. It was developed in 2017 using walk-forward and monte carlo techniques, incubate in 2018, live for 2019-2020 and retired in 2021 when it hit its pre defined stop/retirement point.
- [Game Developement with A.I. Integration](/portfolio/rocket-booster-sandbox): A simple 3D game developed using Unit3D and coded on C# (.net) with two basic levels. This is a sandbox for testing A.I. integration using different techniques. Compiled for WebGL. 
- [Java](/portfolio/java): Collection of well commented programs written in Java
- [C++14](/portfolio/cpp14): Collection of C++ files and headers for several programs to demonstrate key concepts. 
- [Python for Machine Learning](/portfolio/python-machine-learning): Series of scripts demonstrating several machine learning techniques.
- [Python](/portfolio/python-scripts): Your run off the mill everyday use scripts demonstrating basic concepts.  

## Other Resources:
- [Python Pandas/Numpy Cheat Sheet](/portfolio/python-numpy-pandas-cheatsheet/python-numpy-pandas-cheatsheet.ipynb): Selection of interesting tools and tricks. By no means comprehensive but a good way to refresh concepts. 
- [Coding Interview Questions](/portfolio/coding-interview-questions/coding-interview-questions.ipynb): Those have been gathered by me and other students/friends/coworkers over the time and added here. Only actual code interview questions are allowed in this notebook. 
