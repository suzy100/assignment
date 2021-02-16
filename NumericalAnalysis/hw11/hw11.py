import matplotlib.pyplot as plt
import numpy as np
import cv2
from PIL import Image
from scipy.fftpack import dct, idct

img = cv2.cvtColor(cv2.imread("img/10.jpg"), cv2.COLOR_BGR2RGB)

red = img[:,:,0]
green = img[:,:,1]
blue = img[:,:,2]

##img[:,:,0] = 0
##img[:,:,1] = 0
##rgb_im = Image.fromarray(img)
##rgb_im.save('result/10-b.jpg')

red_green = img[:,:,:2]
red_blue = img[:,:,::2]
green_blue = img[:,:,1:3]

rg = np.reshape(red_green, (2, img.shape[0]*img.shape[1]))
rb = np.reshape(red_blue, (2, img.shape[0]*img.shape[1]))
gb = np.reshape(green_blue, (2, img.shape[0]*img.shape[1]))

print(np.corrcoef(rg))
print(np.corrcoef(rb))
print(np.corrcoef(gb))

yuv = cv2.cvtColor(img, cv2.COLOR_RGB2YUV)

y = yuv[:,:,0]
u = yuv[:,:,1]
v = yuv[:,:,2]

y_u = yuv[:,:,:2]
y_v = yuv[:,:,::2]
u_v = yuv[:,:,1:3]

yu = np.reshape(y_u, (2, img.shape[0]*img.shape[1]))
yv = np.reshape(y_v, (2, img.shape[0]*img.shape[1]))
uv = np.reshape(u_v, (2, img.shape[0]*img.shape[1]))

print(np.corrcoef(yu))
print(np.corrcoef(yv))
print(np.corrcoef(uv))

block_Y = np.zeros(y.shape)
im_h, im_w = y.shape
bl_h, bl_w = 16, 16

for row in np.arange(im_h - bl_h +1, step=bl_h):
    for col in np.arange(im_w-bl_w+1, step=bl_w):
        block = y[row:row+bl_h, col:col+bl_w]
        D = dct(dct(block.T, norm='ortho').T, norm='ortho')
        for x in range(16):
            for y in range(16):
                if x>4:
                    D[x,y] = 0
                if y>4:
                    D[x,y] = 0

        
        block_Y[row:row+bl_h, col:col+bl_w]=D

iblock_Y = np.zeros(y.shape)
for row in np.arange(im_h - bl_h +1, step=bl_h):
    for col in np.arange(im_w-bl_w+1, step=bl_w):
        block = y[row:row+bl_h, col:col+bl_w]
        D = idct(idct(block.T, norm='ortho').T, norm='ortho')

        iblock_Y[row:row+bl_h, col:col+bl_w]=D

block_U = np.zeros(u.shape)
im_h, im_w = u.shape
bl_h, bl_w = 16, 16

for row in np.arange(im_h - bl_h +1, step=bl_h):
    for col in np.arange(im_w-bl_w+1, step=bl_w):
        block = u[row:row+bl_h, col:col+bl_w]
        D = dct(dct(block.T, norm='ortho').T, norm='ortho')
        for x in range(16):
            for y in range(16):
                if x>4:
                    D[x,y] = 0
                if y>4:
                    D[x,y] = 0

        
        block_U[row:row+bl_h, col:col+bl_w]=D

iblock_U = np.zeros(u.shape)
for row in np.arange(im_h - bl_h +1, step=bl_h):
    for col in np.arange(im_w-bl_w+1, step=bl_w):
        block = u[row:row+bl_h, col:col+bl_w]
        D = idct(idct(block.T, norm='ortho').T, norm='ortho')

        iblock_U[row:row+bl_h, col:col+bl_w]=D


block_V = np.zeros(y.shape)
im_h, im_w = y.shape
bl_h, bl_w = 16, 16

for row in np.arange(im_h - bl_h +1, step=bl_h):
    for col in np.arange(im_w-bl_w+1, step=bl_w):
        block = v[row:row+bl_h, col:col+bl_w]
        D = dct(dct(block.T, norm='ortho').T, norm='ortho')
        for x in range(16):
            for y in range(16):
                if x>4:
                    D[x,y] = 0
                if y>4:
                    D[x,y] = 0

        
        block_V[row:row+bl_h, col:col+bl_w]=D

iblock_V = np.zeros(y.shape)
for row in np.arange(im_h - bl_h +1, step=bl_h):
    for col in np.arange(im_w-bl_w+1, step=bl_w):
        block = v[row:row+bl_h, col:col+bl_w]
        D = idct(idct(block.T, norm='ortho').T, norm='ortho')

        iblock_V[row:row+bl_h, col:col+bl_w]=D


img_out = np.zeros((3, img.shape[0], img.shape[1]))
img_out[0] = iblock_Y
img_out[1] = iblock_U
img_out[2] = iblock_V
result = np.transpose(img_out, (1,-1,0))
result = np.around(result)

yuv_im = Image.fromarray(yuv, mode='YCbCr')
yuv_im.save('result.jpg')

                    
##yuv_im = Image.fromarray(yuv, mode='YCbCr')
##yuv_im.save('result/10-yuv.jpg')

##yuv[:,:,1] = 128
##yuv[:,:,2] = 128
##yuv_im = Image.fromarray(yuv, mode='YCbCr')
##yuv_im.save('result/2-y.jpg')

##yuv[:,:,0] = 128
##yuv[:,:,2] = 128
##yuv_im = Image.fromarray(yuv, mode='YCbCr')
##yuv_im.save('result/10-u.jpg')

##yuv[:,:,0] = 128
##yuv[:,:,1] = 128
##yuv_im = Image.fromarray(yuv, mode='YCbCr')
##yuv_im.save('result/10-v.jpg')
