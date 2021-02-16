import numpy as np
from PIL import Image
import cv2
import matplotlib.pyplot as plt
from scipy.fftpack import dct, idct

def largest_indices(array, n):
    flat = array.flatten()
    indices = np.argpartition(flat, -n)[-n:]
    indices = indices[np.argsort(-flat[indices])]
    return np.unravel_index(indices, array.shape)

img = cv2.imread('img/1.jpg')

# BGR
red = img[:,:,2]
green = img[:,:,1]
blue = img[:,:,0]


# RED
block_R = np.zeros(red.shape)
im_h, im_w = red.shape
bl_h, bl_w = 16, 16

for row in np.arange(im_h - bl_h + 1, step=bl_h):
    for col in np.arange(im_w - bl_w + 1, step=bl_w):
        block = red[row:row+bl_h, col:col+bl_w]
        D = dct(dct(block.T, norm='ortho').T, norm='ortho')
        for x in range(16):
            for y in range(16):
                if x>4:
                    D[x,y] = 0
                if y>4:
                    D[x,y] = 0
        
        largest = largest_indices(D, 16)
        block_R[row:row+bl_h, col:col+bl_w] = D

iblock_R = np.zeros(red.shape)
for row in np.arange(im_h - bl_h + 1, step=bl_h):
    for col in np.arange(im_w - bl_w + 1, step=bl_w):
        block = block_R[row:row+bl_h, col:col+bl_w]
        D = idct(idct(block.T, norm='ortho').T, norm='ortho')

        iblock_R[row:row+bl_h, col:col+bl_w] = D

# GREEN
block_G = np.zeros(green.shape)
im_h, im_w = green.shape
bl_h, bl_w = 16, 16

for row in np.arange(im_h - bl_h + 1, step=bl_h):
    for col in np.arange(im_w - bl_w + 1, step=bl_w):
        block = green[row:row+bl_h, col:col+bl_w]
        D = dct(dct(block.T, norm='ortho').T, norm='ortho')
        for x in range(16):
            for y in range(16):
                if x>4:
                    D[x,y] = 0
                if y>4:
                    D[x,y] = 0
        
        block_G[row:row+bl_h, col:col+bl_w] = D

iblock_G = np.zeros(red.shape)
for row in np.arange(im_h - bl_h + 1, step=bl_h):
    for col in np.arange(im_w - bl_w + 1, step=bl_w):
        block = block_G[row:row+bl_h, col:col+bl_w]
        D = idct(idct(block.T, norm='ortho').T, norm='ortho')

        iblock_G[row:row+bl_h, col:col+bl_w] = D


# BLUE
block_B = np.zeros(blue.shape)
im_h, im_w = blue.shape
bl_h, bl_w = 16, 16

for row in np.arange(im_h - bl_h + 1, step=bl_h):
    for col in np.arange(im_w - bl_w + 1, step=bl_w):
        block = blue[row:row+bl_h, col:col+bl_w]
        D = dct(dct(block.T, norm='ortho').T, norm='ortho')
        for x in range(16):
            for y in range(16):
                if x>4:
                    D[x,y] = 0
                if y>4:
                    D[x,y] = 0
        
        block_B[row:row+bl_h, col:col+bl_w] = D

iblock_B = np.zeros(red.shape)
for row in np.arange(im_h - bl_h + 1, step=bl_h):
    for col in np.arange(im_w - bl_w + 1, step=bl_w):
        block = block_B[row:row+bl_h, col:col+bl_w]
        D = idct(idct(block.T, norm='ortho').T, norm='ortho')

        iblock_B[row:row+bl_h, col:col+bl_w] = D


# dct block
img_out = np.zeros((3, img.shape[0], img.shape[1]))
img_out[0] = block_R
img_out[1] = block_G
img_out[2] = block_B
result = np.transpose(img_out, (1, -1, 0))
result = np.around(result)
result = np.where(result > 255, 255, result)
result = np.where(result < 0, 0, result)
result = result.astype(np.int64)


plt.imshow(result)
plt.savefig('dct_3.png')
plt.show()


# idct block
img_out = np.zeros((3, img.shape[0], img.shape[1]))
img_out[0] = iblock_R
img_out[1] = iblock_G
img_out[2] = iblock_B
result = np.transpose(img_out, (1, -1, 0))
result = np.around(result)
result = np.where(result > 255, 255, result)
result = np.where(result < 0, 0, result)
result = result.astype(np.int64)


plt.imshow(result)
plt.savefig('idct_3.png')
plt.show()


##D = dct(dct(block.T, norm='ortho').T, norm='ortho')
