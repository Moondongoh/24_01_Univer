import cv2
import random
import numpy as np
import matplotlib.pyplot as plt
import pyautogui

imgList11 = ['./num_0.png', './num_1.png', './num_2.png']
imgList12 = ['./num_3.png', './num_4.png', './num_5.png']
imgList13 = ['./num_6.png', './num_7.png', './num_8.png']
imgList = imgList11 + imgList12 + imgList13

puzzle = np.arange(1,10) 
random.shuffle(puzzle)
puzzle.resize(3,3)

fig, axes = plt.subplots(3, 3, figsize=(5, 5))

def goal(puzzle):
    goalP = 0
    for i in range(3):
        for j in range(3):
            if(puzzle[i][j] == j+i*3+1):
                goalP += j+i*3+1
            if(goalP == 45):
                return 1
            
def checkZero(puzzle):
    x, y = 0, 0
    for i in range(3):
        for j in range(3):
            if puzzle[i][j] == 9:
                y, x = i, j
    return x, y

def visualPuzzle():
    img1 = cv2.imread(imgList[puzzle[0][0]%9])
    img2 = cv2.imread(imgList[puzzle[0][1]%9])
    img3 = cv2.imread(imgList[puzzle[0][2]%9])
    img4 = cv2.imread(imgList[puzzle[1][0]%9])
    img5 = cv2.imread(imgList[puzzle[1][1]%9])
    img6 = cv2.imread(imgList[puzzle[1][2]%9])
    img7 = cv2.imread(imgList[puzzle[2][0]%9])
    img8 = cv2.imread(imgList[puzzle[2][1]%9])
    img9 = cv2.imread(imgList[puzzle[2][2]%9])

    plt.subplot(3, 3, 1)
    plt.gca().axes.xaxis.set_visible(False)
    plt.gca().axes.yaxis.set_visible(False)
    plt.imshow(img1)

    plt.subplot(3, 3, 2)
    plt.gca().axes.xaxis.set_visible(False)
    plt.gca().axes.yaxis.set_visible(False)
    plt.imshow(img2)

    plt.subplot(3, 3, 3)
    plt.gca().axes.xaxis.set_visible(False)
    plt.gca().axes.yaxis.set_visible(False)
    plt.imshow(img3)

    plt.subplot(3, 3, 4)
    plt.gca().axes.xaxis.set_visible(False)
    plt.gca().axes.yaxis.set_visible(False)
    plt.imshow(img4)

    plt.subplot(3, 3, 5)
    plt.gca().axes.xaxis.set_visible(False)
    plt.gca().axes.yaxis.set_visible(False)
    plt.imshow(img5)

    plt.subplot(3, 3, 6)
    plt.gca().axes.xaxis.set_visible(False)
    plt.gca().axes.yaxis.set_visible(False)
    plt.imshow(img6)

    plt.subplot(3, 3, 7)
    plt.gca().axes.xaxis.set_visible(False)
    plt.gca().axes.yaxis.set_visible(False)
    plt.imshow(img7)

    plt.subplot(3, 3, 8)
    plt.gca().axes.xaxis.set_visible(False)
    plt.gca().axes.yaxis.set_visible(False)
    plt.imshow(img8)

    plt.subplot(3, 3, 9)
    plt.gca().axes.xaxis.set_visible(False)
    plt.gca().axes.yaxis.set_visible(False)
    plt.imshow(img9)
    if(goal(puzzle)==1):
        print("goal!!")
        quit()

def add_point(event):
    #if event.inaxes != ax:
    #    return
    if event.button == 1:
        zeroX,zeroY = checkZero(puzzle)
        fore = pyautogui.getActiveWindow()
        pos = pyautogui.position()
        x = pos.x - fore.left
        y = pos.y - fore.top

        if (x >= 75 and x <= 195) and (y >= 95 and y <= 210):
            clickX = 0
            clickY = 0
        if (x >= 205 and x <= 325) and (y >= 95 and y <= 210):
            clickX = 1
            clickY = 0
        if (x >= 335 and x <= 455) and (y >= 95 and y <= 210):
            clickX = 2
            clickY = 0
        if (x >= 75 and x <= 195) and (y >= 225 and y <= 340):
            clickX = 0
            clickY = 1
        if (x >= 205 and x <= 325) and (y >= 225 and y <= 340):
            clickX = 1
            clickY = 1
        if (x >= 335 and x <= 455) and (y >= 225 and y <= 340):
            clickX = 2
            clickY = 1
        if (x >= 75 and x <= 195) and (y >= 355 and y <= 470):
            clickX = 0
            clickY = 2
        if (x >= 205 and x <= 325) and (y >= 355 and y <= 470):
            clickX = 1
            clickY = 2
        if (x >= 335 and x <= 455) and (y >= 355 and y <= 470):
            clickX = 2
            clickY = 2

        gapX = clickX - zeroX
        gapY = clickY - zeroY
        if((gapX==1) or (gapX==-1)) and (gapY==0):
            puzzle[zeroY][zeroX] = puzzle[clickY][clickX]
            puzzle[clickY][clickX] = 9
        elif((gapY==1) or (gapY==-1)) and (gapX==0):
            puzzle[zeroY][zeroX] = puzzle[clickY][clickX]
            puzzle[clickY][clickX] = 9

        plt.subplot(3, 3, clickY*3 + clickX + 1)
        plt.gca().axes.xaxis.set_visible(False)
        plt.gca().axes.yaxis.set_visible(False)
        visualPuzzle()
        plt.show()

visualPuzzle()
cid = plt.connect('button_press_event', add_point)
plt.subplots_adjust(wspace=0.01, hspace=0.02)
plt.show()