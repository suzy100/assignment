import matplotlib.pyplot as plt
import numpy as np

img = plt.imread('./checkerboard.png')

dy, dx = np.gradient(img)
Ixx = dx*dx
Iyx = dy*dx
Iyy = dy*dy

height = img.shape[0]
width = img.shape[1]

corner = np.zeros(img.shape)

# 3, 7, 11
window_size = 11
win = window_size//2

for y in range(win, height-win):
    for x in range(win, width-win):
        A = Ixx[y-win:y+win+1, x-win:x+win+1].sum()
        B = Iyx[y-win:y+win+1, x-win:x+win+1].sum()
        C = Iyy[y-win:y+win+1, x-win:x+win+1].sum()

        # Harris matrix H
        H = np.array([A,B,B,C]).reshape(2,2)
        # eigenvalues of H
        w = np.linalg.eigvals(H)

        corner[y,x] = min(w[0], w[1])

##        # Harris response
##        if (w[0]+w[1]) != 0:
##            corner[y,x] = (w[0]*w[1])/(w[0]+w[1])

save_name = ('hw2_%s.png' % window_size)
plt.imsave(save_name, corner, cmap='gray')
