import numpy as np

A=np.array([[3,-4,-4],
	[4,0,-1],
	[1,-1,1]])
print(A)
B=np.array([[-4],
	[20],
	[0]])
print(B)

invA = np.linalg.inv(A)

X = np.dot(invA,B)
print(X)

arr = np.array([[0, 1, 2], [3, 4, 5]], dtype=np.float32)
print(repr(arr))
