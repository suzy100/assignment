import numpy as np
import random

# exact values
# (-5, -11), (-4, -9), (-3, -7), (-2, -5), (-1, -3), (0, -1)
# (1, 1), (2, 3), (3, 5), (4, 7), (5, 9), (6, 11)
x_val = [-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6]

def make_array(x):
    # [x, 1]
    result = [x, 1]
    return result

def whole(sample):
    A = np.array([make_array(sample[0][0]),
                  make_array(sample[1][0]),
                  make_array(sample[2][0]),
                  make_array(sample[3][0]),
                  make_array(sample[4][0]),
                  make_array(sample[5][0]),
                  make_array(sample[6][0]),
                  make_array(sample[7][0]),
                  make_array(sample[8][0]),
                  make_array(sample[9][0]),
                  make_array(sample[10][0]),
                  make_array(sample[11][0]),
                  ])

    b = np.array([sample[0][1],
                  sample[1][1],
                  sample[2][1],
                  sample[3][1],
                  sample[4][1],
                  sample[5][1],
                  sample[6][1],
                  sample[7][1],
                  sample[8][1],
                  sample[9][1],
                  sample[10][1],
                  sample[11][1],
                  ]).reshape((12,1))

    trans_A = np.transpose(A)
    tmp = trans_A.dot(A)
    tmp = np.linalg.inv(tmp)
    tmp = tmp.dot(trans_A)
    x = tmp.dot(b)

    print("x ", x)

    # ||Ax-b||^2
    error = A.dot(x)-b
    trans_err = np.transpose(error)
    E = trans_err.dot(error)

    print("error ", E)


def sampling(sample):
    flag = True
    curErr = None
    i = 1
    while(flag):
        # Random 6 Index
        ri = random.sample(list(range(12)), 6)

        A = np.array([make_array(sample[ri[0]][0]),
                      make_array(sample[ri[1]][0]),
                      make_array(sample[ri[2]][0]),
                      make_array(sample[ri[3]][0]),
                      make_array(sample[ri[4]][0]),
                      make_array(sample[ri[5]][0]),
                      ])

        b = np.array([sample[ri[0]][1],
                      sample[ri[1]][1],
                      sample[ri[2]][1],
                      sample[ri[3]][1],
                      sample[ri[4]][1],
                      sample[ri[5]][1],
                      ]).reshape((6,1))

        trans_A = np.transpose(A)
        tmp = trans_A.dot(A)
        tmp = np.linalg.inv(tmp)
        tmp = tmp.dot(trans_A)
        x = tmp.dot(b)

        # ||Ax-b||^2
        error = A.dot(x)-b
        trans_err = np.transpose(error)
        E = trans_err.dot(error)


        if i == 1:
            curErr = E
            print("current Error ", curErr)
            
        else:
            if E < curErr:
                curErr = E
                
            if curErr < 0.5 :
                flag = False
                print(i)
                print("current Error ", curErr)
                print("x ", x)
        
        i+=1

# gaussian
mean = 0
var = 2
sigma = var ** 0.5
size = 12
gaussian = np.random.normal(mean, sigma, 12)
print(gaussian)

# 12 samples
sample = np.zeros((12,2))

for i in range(12):
    x = x_val[i]
    y = 2*x - 1 + gaussian[i]
    sample[i] = [x, y]

print(sample)


whole(sample)
sampling(sample)
