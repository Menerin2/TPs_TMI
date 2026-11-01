'''
 * file : main.py
 * brief : TP3 sur la segmentation basée région
 * author : Phuc Ngo
'''

import sys
import cv2
import numpy as np
from functions import croissanceRegion

# --- Global variables (same as C++ version) ---
src = None
src_gray = None
dst = None
germes = []     # list of (x, y) tuples

window_org = "Original image"
window_res = "Croissance de region Demo"
trackbar_value = "Seuil"

threshold_value = 10
max_value = 256
predicat = 1


def help():
    print(f"Usage: {sys.argv[0]} [input.png] [predicat=1,2,3]")


# ------------------------------------------------------------
# Trackbar callback
# ------------------------------------------------------------
def onTrackbar(val):
    global dst, threshold_value

    threshold_value = val
    dst = croissanceRegion(src_gray, germes, threshold_value, predicat)
    cv2.imshow(window_res, dst)


# ------------------------------------------------------------
# Mouse callback (click to add germes)
# ------------------------------------------------------------
def onMouse(event, x, y, flags, param):
    global germes, src

    if event == cv2.EVENT_LBUTTONDOWN:
        germes.append((x, y))
        cv2.circle(src, (x, y), 5, (255, 0, 0), -1)
        cv2.imshow(window_org, src)


# ------------------------------------------------------------
# MAIN PROGRAM
# ------------------------------------------------------------
def main():
    global src, src_gray, predicat

    help()

    imageName = "images/rice.png"
    if len(sys.argv) > 1:
        imageName = sys.argv[1]
    if len(sys.argv) > 2:
        predicat = int(sys.argv[2])

    # Load input image
    src = cv2.imread(imageName, cv2.IMREAD_COLOR)
    if src is None:
        print("Could not open or find the image")
        return -1

    # Convert to grayscale
    src_gray = cv2.cvtColor(src, cv2.COLOR_BGR2GRAY)

    # Show original
    cv2.namedWindow(window_org, cv2.WINDOW_AUTOSIZE)
    cv2.imshow(window_org, src)
    cv2.setMouseCallback(window_org, onMouse)

    # Result window + trackbar
    cv2.namedWindow(window_res, cv2.WINDOW_AUTOSIZE)
    cv2.createTrackbar(trackbar_value, window_res, threshold_value, max_value, onTrackbar)

    # Call the function to initialize
    onTrackbar(threshold_value)

    # Wait until user finishes program with ESC key
    while True:
        c = cv2.waitKey(20)
        if c == 27:   # ESC key
            break

    return 0


if __name__ == "__main__":
    main()