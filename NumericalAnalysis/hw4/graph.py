import numpy as np 
from matplotlib import pyplot as plt 

data = np.array([[-2.9, 35.4],
                [-2.1, 19.7], 
		[-0.9, 5.7], 
		[1.1, 2.1], 
		[0.1, 1.2],
                [1.9, 8.7],
		[3.1, 25.7],
                [4.0, 41.5]])

plt.scatter(data[:, 0], data[:, 1]) 
plt.xlabel("x")
plt.ylabel("y")
plt.axis([-4, 5, 0, 50])

def xrange(start, final, interval):
    numbers = []
    while start < final:
        numbers.append(start)
        start += interval
    return numbers

def h(x):
    return 3.24789136*x*x - 2.1379364*x + 1.01464205

def f(x):
    return 3.1795778*x*x - 2.44861543*x + 1.33249827

# 선형회귀 그래프 데이터 생성
x_data = xrange(-5, 5, 0.0001)
y_data_1 = []
y_data_2 = []
for x in x_data:
    y_data_1.append(3.1795778*x*x - 2.44861543*x + 1.33249827)
    y_data_2.append(3.24789136*x*x - 2.1379364*x + 1.01464205)

plt.plot(x_data, y_data_1, 'b')
plt.plot(x_data, y_data_2, 'r')
plt.show()
