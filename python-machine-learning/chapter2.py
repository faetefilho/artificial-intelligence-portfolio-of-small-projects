#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Mar 11 10:07:53 2022
End to end machine learning project
@author: tinho
"""
from mymodule import fetch_housing_data
import pandas as pd
import os
import matplotlib.pyplot as plt 
import numpy as np
from sklearn.impute import SimpleImputer
from sklearn.preprocessing import OrdinalEncoder
from sklearn.preprocessing import OneHotEncoder
from sklearn.pipeline import Pipeline
from sklearn.preprocessing import StandardScaler
from sklearn.pipeline import Pipeline
from mymodule import CombinedAttributesAdder
from sklearn.compose import ColumnTransformer
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error
from sklearn.tree import DecisionTreeRegressor
from sklearn.model_selection import cross_val_score
from sklearn.model_selection import GridSearchCV
from sklearn.ensemble import RandomForestRegressor
from scipy import stats

HOUSING_PATH = os.path.join("datasets", "housing","housing.csv")

housing=pd.read_csv(HOUSING_PATH)
housing['ocean_proximity'].value_counts()
# summary of the numerical attributes
housing.describe()
# plots
housing.hist(bins=50, figsize=(20,15))
plt.show()

from mymodule import split_train_test

train_set, test_set = split_train_test(housing, 0.2)
len(train_set)
len(test_set)

# Can also use method from scikit
# from sclearn.model_selection import train_test_plit
# train_set, test_set = train_test_split(housing, test_size=0.2, random_state=42)

# Create an income category attribute
housing['income_cat'] = pd.cut(housing['median_income'], bins=[0,1.5,3,4.5,6,np.inf], labels=[1,2,3,4,5])
housing['income_cat'].hist()

from sklearn.model_selection import StratifiedShuffleSplit

split = StratifiedShuffleSplit(n_splits=1, test_size=0.2, random_state=42)
for train_index, test_index in split.split(housing, housing['income_cat']):
    strat_train_set = housing.loc[train_index]
    strat_test_set = housing.loc[test_index]

# checking for strata
strat_test_set['income_cat'].value_counts()/len(strat_test_set)
housing['income_cat'].value_counts()/len(housing)

# removing income_cat atribute so the data is back to original
for set_ in (strat_train_set, strat_test_set):
    set_.drop('income_cat', axis=1, inplace=True)

housing = strat_train_set.copy()
housing.plot(kind='scatter', x='longitude', y='latitude', alpha=0.1)
housing.plot(kind='scatter', x='longitude', y='latitude', alpha=0.4, s=housing['population']/100, label='population', figsize=(10,7), c='median_house_value', cmap=plt.get_cmap('jet'), colorbar=True)
plt.legend()

# looking for correlations between pair of attributes
corr_matrix = housing.corr()
corr_matrix['median_house_value'].sort_values(ascending=False)
# scatter matrix
attributes = ['median_house_value', 'median_income', 'total_rooms', 'housing_median_age']
pd.plotting.scatter_matrix(housing[attributes], figsize=(12,8))
# zooming in
housing.plot(kind='scatter', x='median_income', y='median_house_value', alpha=0.1)

housing['rooms_per_household'] = housing['total_rooms']/housing['households']
housing['bedrooms_per_room'] = housing['total_bedrooms']/housing['total_rooms']
housing['population_per_household'] = housing['population']/housing['households']
corr_matrix = housing.corr()
housing['median_house_value'].sort_values(ascending=False)

housing = strat_train_set.drop('median_house_value', axis=1)
housing_labels = strat_train_set['median_house_value'].copy()

# data cleaning options
# housing.dropna(subset=['total_bedrooms']) #option1
# housing.drop('total_bedrooms', axis=1)  #option2
# median = housing['total_bedrooms'].median()  #option3
# housing['total_bedrooms'].fillna(median, inplace=True)

imputer = SimpleImputer(strategy='median')
# imputer only works on numerical
housing_num = housing.drop('ocean_proximity', axis=1)
imputer.fit(housing_num)
imputer.statistics_
housing_num.median().values
X = imputer.transform(housing_num)
# putting it back into pandas
housing_tr = pd.DataFrame(X, columns=housing_num.columns, index=housing_num.index)

# working categorical attributes
housing_cat = housing[['ocean_proximity']]
housing_cat.head(10)
#cats to numbers
ordinal_encoder = OrdinalEncoder()
housing_cat_encoded = ordinal_encoder.fit_transform(housing_cat)
# see list of categories
ordinal_encoder.categories_
# categorical to one hot vector
cat_encoder = OneHotEncoder()
housing_cat_1hot = cat_encoder.fit_transform(housing_cat)
# Transformation pipeline below
   
num_pipeline = Pipeline([
    ('imputer', SimpleImputer(strategy='median')),
    ('attribs_adder', CombinedAttributesAdder()),
    ('std_scaler', StandardScaler()),
    ])
housing_num_tr = num_pipeline.fit_transform(housing_num)

# Transformer for all columns in the data
num_attribs = list(housing_num)
cat_attribs = ['ocean_proximity']

full_pipeline = ColumnTransformer([
    ('num',num_pipeline, num_attribs),
    ('cat', OneHotEncoder(), cat_attribs),
    ])

housing_prepared = full_pipeline.fit_transform(housing)

# select and train a model
lin_reg = LinearRegression()
lin_reg.fit(housing_prepared, housing_labels)

some_data = housing.iloc[:5]
some_labels = housing_labels.iloc[:5]
some_data_prepared = full_pipeline.transform(some_data)
print('\npredictions: ',lin_reg.predict(some_data_prepared))
print('\nLabels: ',list(some_labels))

# measuring error
housing_predictions = lin_reg.predict(housing_prepared)
lin_mse = mean_squared_error(housing_labels, housing_predictions)
lin_rmse = np.sqrt(lin_mse)

# not good error so lets try decision trees
tree_reg = DecisionTreeRegressor()
tree_reg.fit(housing_prepared, housing_labels)
# evaluating
housing_predictions = tree_reg.predict(housing_prepared)
tree_mse = mean_squared_error(housing_labels, housing_predictions)
tree_rmse = np.sqrt(tree_mse)
# cross validation
scores = cross_val_score(tree_reg, housing_prepared, housing_labels, scoring='neg_mean_squared_error', cv=10)
tree_rmse_scores = np.sqrt(-scores)

lin_scores = cross_val_score(lin_reg, housing_prepared, housing_labels, scoring='neg_mean_squared_error', cv=10)
lin_rmse_scores = np.sqrt(-lin_scores)

# fine tuning model
param_grid = [
    {'n_estimators': [3,10,30], 'max_features':[2,4,6,8]},
    {'bootstrap': [False], 'n_estimators':[3,10], 'max_features':[2,3,4]},
    ]
forest_reg = RandomForestRegressor()

grid_search = GridSearchCV(forest_reg, param_grid, cv=5,
                           scoring='neg_mean_squared_error',
                           return_train_score=True)
grid_search.fit(housing_prepared, housing_labels)

grid_search.best_params_
grid_search.best_estimator_
# analyze best models and their errors
feature_importances = grid_search.best_estimator_.feature_importances_

# evaluate your system on the test set
final_model = grid_search.best_estimator_
X_test = strat_test_set.drop('median_house_value', axis=1)
y_test = strat_test_set['median_house_value'].copy()

X_test_prepared = full_pipeline.transform(X_test)
final_predictions = final_model.predict(X_test_prepared)    

final_mse = mean_squared_error(y_test, final_predictions)
final_rmse = np.sqrt(final_mse) #evaluates

# confdence interval for the generalization error

confidence = 0.95
squared_errors = (final_predictions-y_test)**2
np.sqrt(stats.t.interval(confidence, len(squared_errors)-1,
                         loc=squared_errors.mean(),
                         scale=stats.sem(squared_errors)))










