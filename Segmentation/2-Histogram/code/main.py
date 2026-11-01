'''
 * file : main.py
 * brief : TP2 sur la segmentation basée histogramme
 * author : Phuc Ngo
'''

import sys
import cv2
import numpy as np
from functions import (
    seuillage,
    seuillageHysteresis,
    histogramme,
    seuillageOtsu,
    kmean,
)

window1_name = "Image originale"
window2_name = "Image convertie"
window_res = "Image resultante"
exercise = 1


def help():
    print(f"Usage: {sys.argv[0]} [input.png] [numExo]")


# ------------------------------------------------------------
# MAIN PROGRAM
# ------------------------------------------------------------
def main():
    global exercise
    help()

    # Default image
    imageName = "images/coins.png"
    if len(sys.argv) > 1:
        imageName = sys.argv[1]
    if len(sys.argv) > 2:
        exercise = int(sys.argv[2])

    # Load image
    image = cv2.imread(imageName, cv2.IMREAD_COLOR)
    if image is None:
        print("Could not open or find the image")
        return -1

    # Show original
    cv2.namedWindow(window1_name, cv2.WINDOW_AUTOSIZE)
    cv2.imshow(window1_name, image)

    # Convert to gray
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    cv2.namedWindow(window2_name, cv2.WINDOW_AUTOSIZE)
    cv2.imshow(window2_name, gray)

    # Exercise 1 : theshold
    if exercise == 1:
        thresh_list = [50, 100, 150]
        cv2.namedWindow(window_res, cv2.WINDOW_AUTOSIZE)

        for t in thresh_list:
            dst = seuillage(gray, t)
            cv2.imshow(window_res, dst)
            cv2.waitKey(0)

    # Exercise 2 : Hysteresis theshold
    if exercise == 2:
        threshold_bas = 60
        threshold_haut = 98
        dst = seuillageHysteresis(gray, threshold_bas, threshold_haut)
        cv2.imshow(window_res, dst)
        cv2.waitKey(0)

    # Exercise 3 : histogram 
    if exercise == 3:
        intervalle_list = [1, 10, 20]

        for itv in intervalle_list:
            h = histogramme(gray, itv)

            print(f"Histogramme de {imageName} avec un intervalle de {itv} est :")
            print("Valeur :", end=" ")
            for i in range(len(h) - 1):
                print(f"{i * itv}--{(i + 1) * itv - 1}", end="\t")
            print(f"{(len(h) - 1) * itv}--255")

            print("Quantité :", end=" ")
            for v in h:
                print(v, end="\t")
            print("\n")

    # Exercise 4: Otsu's method 
    if exercise == 4:
        threshold = seuillageOtsu(gray)
        print(f"Seuil de Otsu obtenue : {threshold}")

        dst = seuillage(gray, threshold)
        cv2.imshow(window_res, dst)
        cv2.waitKey(0)

    # Exercise 5: kmean method 
    if exercise == 5:
        k = 2
        dst = kmean(gray, k)
        cv2.imshow(window_res, dst)
        cv2.waitKey(0)

    return 0


if __name__ == "__main__":
    main()