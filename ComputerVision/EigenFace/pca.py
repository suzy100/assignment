import numpy as np
from PIL import Image
# do not import any other modules

#pre-defined util
def show_np_arr(np_arr):#np_arr should be 2-dim
  tmp = np_arr
  tmp = (tmp - np.min(tmp))/(np.max(tmp) - np.min(tmp))
  tmp = np.clip(255*tmp, 0, 255)
  tmp = Image.fromarray(np.uint8(tmp)).convert('RGB')
  tmp.show()  


#load and pre-process dataset, do not modify here
x_train = np.load("./x_train.npy")/255.
y_train = np.load("./y_train.npy")
x_test = x_train[2]

idx = np.argsort(y_train)
x_train = x_train[idx]
x_train = x_train[::200]
print(x_train.shape, x_test.shape)



#Q1. Eigenface
##step1: compute mean of x_train
mu = np.zeros((1, x_test.shape[0]*x_test.shape[1]))

for i in x_train:
  i = i.reshape((1, x_test.shape[0]*x_test.shape[1]))
  mu = np.add(mu, i)

mu = np.divide(mu, x_train.shape[0]).flatten()


##show_np_arr(mu.reshape(x_test.shape[0], x_test.shape[1]))


##step2: subtract the mean
phi = np.zeros((x_train.shape[0], x_test.shape[0]*x_test.shape[1]))

for i in range(x_train.shape[0]):
  train = x_train[i].reshape((1, -1))
  phi[i] = np.subtract(train, mu)

##show_np_arr(phi[0].reshape(x_test.shape[0], x_test.shape[1]))


##step3: compute covariance C

##C = np.zeros((x_train.shape[0], x_train.shape[0]))
##for i in range(x_train.shape[0]):
##  phio = phi[i].reshape((1,-1))
##  phit = phi[i].reshape((-1,1))
##  C = np.add(C, np.dot(phio, phit))
##C = np.divide(C, x_train.shape[0])
##print(C)

C = np.cov(phi)
C = np.divide(C, x_train.shape[0])

#step4: Compute eigenvector of C, you don't need to do anything at step4.
eigenvalues, eigenvec = np.linalg.eig(C)
eigenvec = eigenvec.T
print("Shape of eigen vectors = ",eigenvec.shape)

##step5: choose K
K = 40

##step6: show top K eigenfaces. use show_np_arr func.
sort_val = eigenvalues[eigenvalues.argsort()][::-1]
sort_vec = eigenvec[eigenvalues.argsort()][::-1]

# top K
k_eigen = eigenvec[0:K, :]
img = k_eigen.reshape(K,  x_test.shape[0], x_test.shape[1])

# print it until K
show_np_arr(np.real(img[0]))




#Q2. Image Approximation
x = x_test

##step1: approximate x as x_hat with top K eigenfaces and show x_hat
x_hat = ...

##step2: compater mse between x and x_hat by changing the number of the eigenfaces used for reconstruction (approximation) from 1 to K
for i in range(1, K+1):
  x_hat = ...
  mse = ...
  print(i, mse)




#Q3. Implement fast version of you algorithm in Q1. Show top 'K' eigenfaces using show_np_arr(...)
  ...
