# Load libraries
import pandas as pd 
from sklearn.tree import DecisionTreeClassifier # Import Decision Tree Classifier
from sklearn.model_selection import train_test_split # Import train_test_split function
from sklearn import metrics #Import scikit-learn metrics module for accuracy calculation

#col_names = ['Name', 'WaldoID', 'eventnum', 'result', 'result_detailed', 'ch1st', 'ch1end', 'ch1len', 'ch2st', 'ch2end', 'ch2len', 'dist_st', 'dist_end']
#col_names = ['WaldoID', 'packetID', 'result', 'ch1st', 'ch1end', 'ch1len', 'ch2st', 'ch2end', 'ch2len', 'dist_st', 'dist_end', 'diff_lengths']

col_names = ['Name', 'WaldoID', 'eventnum', 'result', 'result_detailed', 'ch1st', 'ch1end', 'ch2st', 'ch2end']


# load dataset
pima = pd.read_csv("Sample_Training_Data.csv", header=None, names=col_names)
pima.head()

#Feature Selection
#split dataset in features and target variable
feature_cols = ['ch1st', 'ch2st', 'ch1end', 'ch2end']
X = pima[feature_cols] # Features
y = pima.result_detailed # Target variable

# Split dataset into training set and test set
# 70% training and 30% test
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=1) 

# Create Decision Tree classifer object
#clf = DecisionTreeClassifier()
#clf = DecisionTreeClassifier(criterion="entropy")
clf = DecisionTreeClassifier(criterion="entropy", max_depth=4)

# Train Decision Tree Classifer
clf = clf.fit(X_train,y_train)

#Predict the response for test dataset
y_pred = clf.predict(X_test)

# Model Accuracy, how often is the classifier correct?
print("Accuracy:",metrics.accuracy_score(y_test, y_pred))

from sklearn.tree import export_graphviz
import graphviz

dot_data = export_graphviz(clf, out_file=None,  
                filled=True, rounded=True,
                special_characters=True,
                feature_names = feature_cols,
                class_names=['lab_in', 'lab_out', 'lab_in_running', 'lab_out_running', 'lab_pbin', 'lab_pbout', 'closed_door'])

graph = graphviz.Source(dot_data)
graph.render("LabTraining_basefeatures")
