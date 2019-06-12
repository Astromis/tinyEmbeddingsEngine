'''
This script tests an iterative algorithm for solving of logistic regression problem with Newton-Rafson method. More 

http://www.machinelearning.ru/wiki/index.php?title=%D0%9B%D0%BE%D0%B3%D0%B8%D1%81%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B0%D1%8F_%D1%80%D0%B5%D0%B3%D1%80%D0%B5%D1%81%D1%81%D0%B8%D1%8F_%28%D0%BF%D1%80%D0%B8%D0%BC%D0%B5%D1%80%29 
'''

from sklearn.linear_model import LogisticRegression
from sklearn.datasets import load_iris
from sklearn.model_selection import train_test_split
from sklearn.datasets import make_classification
import numpy as np

def to_csv(name,arr):
    np.savetxt( name + ".csv", arr, delimiter=",")

X,y = make_classification()

#clf = LogisticRegression()
#clf.fit(X_tr,y_tr)
#print clf.score(X_t,y_t)

#to_csv("X", X)
#to_csv('y',y)

print(X.shape)
print(y.shape)

b0 = np.log(np.mean(y) / (1 - np.mean(y)))
print(y)
print("b0 is %s" % str(b0))

b = np.zeros((X.shape[1], 1))
print("shape b is {}, {}".format(b.shape[0],b.shape[1]))
b[0] = b0
b.T
for i in range(20):
    z = np.matmul(X, b)
    p = 1/(1 + np.exp(-z))
    print(p.shape)
    w = p * (1 - p)
    u = z + (y - p) / w
    b_old = b
    #np.linalg.inv np.diag
    #print np.diag(w.reshape(99,)).shape
    if i == 0:
        diag_w = np.diag(w.reshape(100,))
    b = np.linalg.inv(np.matmul(np.matmul(np.transpose(X), diag_w), X))
    b = np.matmul(b, np.transpose(X))
    b = np.matmul(b, diag_w)
    b = np.matmul(b, u)
    ssq = np.sum((b_old - b)**2)
    print(ssq)
