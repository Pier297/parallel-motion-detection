import cv2
import sys
import numpy
from math import ceil
numpy.set_printoptions(threshold=sys.maxsize)

cap = cv2.VideoCapture('./videos/earth_L.mp4')

if not cap.isOpened():
    print('video not opened')
    exit()

def black_white(img):
    res = numpy.zeros((img.shape[0], img.shape[1]))
    for i in range(img.shape[0]):
        for j in range(img.shape[1]):
            res[i][j] = round((int(img[i][j][0]) + int(img[i][j][1]) + int(img[i][j][2])) / 3)
    return res

def blur(img):
    zero_pad_img = numpy.pad(img, ((1, 1), (1, 1)), 'constant')
    res = numpy.zeros_like(img)
    for i in range(1, img.shape[0] + 1):
        for j in range(1, img.shape[1] + 1):
            res[i - 1][j - 1] = round((zero_pad_img[i - 1][j - 1] + zero_pad_img[i - 1][j] + zero_pad_img[i - 1][j + 1] + zero_pad_img[i][j - 1] + zero_pad_img[i][j] + zero_pad_img[i][j + 1] + zero_pad_img[i + 1][j - 1] + zero_pad_img[i + 1][j] + zero_pad_img[i + 1][j + 1]) / 9)
    return res

ret, background = cap.read()
print(background.shape)
# convert background to gray scale by average rgb value
background = black_white(background)
background = blur(background)
print(background.shape)

N_frames_with_motion = 0

k = 0.3
i = 0

while True:
    ret, frame = cap.read()
    if not ret:
        break
    frame = black_white(frame)
    frame = blur(frame)
    
    diff = (frame != background).sum()

    if (diff / (frame.shape[0] * frame.shape[1])) > k:
        N_frames_with_motion += 1
    
    print(i)
    i += 1

print()
print(N_frames_with_motion)