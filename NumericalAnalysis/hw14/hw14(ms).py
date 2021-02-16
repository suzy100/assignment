import numpy as np
from PIL import Image
import cv2
import matplotlib.pyplot as plt

img = cv2.cvtColor(cv2.imread("taxi.jpg"), cv2.COLOR_BGR2LAB)
dst = cv2.pyrMeanShiftFiltering(img, 16, 16)
rslt = cv2.cvtColor(dst, cv2.COLOR_LAB2BGR)

cv2.imwrite('result/ms.jpg', rslt)
cv2.imshow('result', rslt)
cv2.waitKey(0)
cv2.destroyAllWindows()
