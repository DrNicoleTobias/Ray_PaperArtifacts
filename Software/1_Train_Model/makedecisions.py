# Load libraries
import pandas as pd
from sklearn.tree import DecisionTreeClassifier # Import Decision Tree Classifier
from sklearn.model_selection import train_test_split # Import train_test_split function
from sklearn import metrics #Import scikit-learn metrics module for accuracy calculation
from sklearn.metrics import confusion_matrix
from sklearn.metrics import accuracy_score
from sklearn.metrics import classification_report

col_names = ['Name', 'WaldoID', 'eventnum', 'eventresult', 'eventresult_detailed', 'ch1st', 'ch1end', 'ch1len', 'ch2st', 'ch2end', 'ch2len', 'dist_st', 'dist_end']


# load dataset
pima = pd.read_csv("Sample_Training_Data.csv", sep=',', header=None, names=col_names)
pima.head()

#print("Dataset Length: ", len(pima))
#print("Dataset: ", pima.head())
#print(pima.shape)

#Feature Selection
#split dataset in features and target variable
feature_cols = ['ch1st', 'ch1end', 'ch2st', 'ch2end', 'dist_st', 'dist_end']
X = pima[feature_cols] # Features
y = pima.eventresult # Target variable

# Split dataset into training set and test set
# 70% training and 30% test
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=None, random_state=100, shuffle=True) 
#print(X_train)
#print(y_train)
# Create Decision Tree classifer object
#clf = DecisionTreeClassifier()
#clf = DecisionTreeClassifier(criterion="entropy")
clf = DecisionTreeClassifier(max_depth=4)#criterion="entropy")#, max_depth=4)#, min_samples_leaf = 8)

# Train Decision Tree Classifer
clf = clf.fit(X_train,y_train)

#Predict the response for test dataset
y_pred = clf.predict(X_test)

#print("Confusion Matrix: ",
#        confusion_matrix(y_test, y_pred))

# Model Accuracy, how often is the classifier correct?
print("Accuracy:",metrics.accuracy_score(y_test, y_pred))

from sklearn.tree import export_graphviz
import graphviz

dot_data = export_graphviz(clf, out_file=None,  
                filled=True, rounded=True,
                special_characters=True,
                feature_names = feature_cols,
                class_names=['in', 'out', 'pbin', 'pbout', 'close_door'])

graph = graphviz.Source(dot_data)
graph.render("Sample_DecisionTree_Depth4")
