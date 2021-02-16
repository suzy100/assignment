import numpy as np

def make_array(x):
    # [x^2, x, 1]
    result = [x**2, x, 1]
    return result

A = np.array([make_array(-2.1),
              make_array(-0.9),
              make_array(1.1),
              make_array(0.1),
              make_array(1.9),
              make_array(3.1)])

b = np.array([19.7, 5.7, 2.1, 1.2, 8.7, 25.7])
b = b.reshape((6,1))

print('A')
print(A)
print('b')
print(b)

trans_A = np.transpose(A)
tmp = trans_A.dot(A)
tmp = np.linalg.inv(tmp)
tmp = tmp.dot(trans_A)
x = tmp.dot(b)

print('x')
print(x)

# ||Ax-b||^2
error = A.dot(x)-b
trans_err = np.transpose(error)
E = trans_err.dot(error)

print('error')
print(E)
