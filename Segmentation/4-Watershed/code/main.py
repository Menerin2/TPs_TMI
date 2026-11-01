'''
 * file : main.py
 * brief : TP4 sur la segmentation basée contour
 * author : Phuc Ngo
'''

import sys
import cv2
import numpy as np

from functions import (
    elementStruturant,
    dilatation,
    erosion,
    ouverture,
    fermeture,
    debruitage,
    gradientInterne,
    gradientExterne,
    gradientMorphologique,
    reconstructionInferieure,
    reconstructionSuperieure,
    minimaRegionaux,
    maximaRegionaux,
    marqueurs,
    ligneDePartageDesEaux
)

# --- Global variables (same as C++ code) ---
src = None
src_gray = None
dst = None
germes = []             # list of (x, y)

window_org = "Original image"
exercise = 1
typeSE = "croix"        # carree, disque, diamant, croix, hligne, vligne
taille = 1


def help():
    print(f"Usage: {sys.argv[0]} [input.png] [numExo] [typeSE] [taille]")
    print("typeSE: carree, disque, croix, hligne, vligne")


# ----------------------------------------------------------------
# Mouse callback
# ----------------------------------------------------------------
def onMouse(event, x, y, flags, param):
    global germes, src

    if event == cv2.EVENT_LBUTTONDOWN:
        germes.append((x, y))
        cv2.circle(src, (x, y), 3, (255, 0, 0), -1)
        cv2.imshow(window_org, src)


# ----------------------------------------------------------------
# MAIN PROGRAM 
# ----------------------------------------------------------------
def main():
    global src, src_gray, dst, exercise, typeSE, taille

    help()

    imageName = "images/tree.png"

    if len(sys.argv) > 1:
        imageName = sys.argv[1]
    if len(sys.argv) > 2:
        exercise = int(sys.argv[2])
    if len(sys.argv) > 4:
        typeSE = sys.argv[3]
        taille = int(sys.argv[4])

    # structuring element
    element = elementStruturant(taille, typeSE)

    # load image
    src = cv2.imread(imageName, cv2.IMREAD_COLOR)
    if src is None:
        print("Could not open or find the image")
        return -1

    src_gray = cv2.cvtColor(src, cv2.COLOR_BGR2GRAY)

    # original window
    cv2.namedWindow(window_org, cv2.WINDOW_AUTOSIZE)
    cv2.imshow(window_org, src)
    cv2.setMouseCallback(window_org, onMouse)

    # Exercise 2 : morphological operators
    if exercise == 2:
        cv2.namedWindow("Dilatation", cv2.WINDOW_AUTOSIZE)
        cv2.namedWindow("Erosion", cv2.WINDOW_AUTOSIZE)
        cv2.namedWindow("Ouverture", cv2.WINDOW_AUTOSIZE)
        cv2.namedWindow("Fermeture", cv2.WINDOW_AUTOSIZE)

        d = dilatation(src_gray, element)
        e = erosion(src_gray, element)
        o = ouverture(src_gray, element)
        f = fermeture(src_gray, element)

        cv2.imshow("Dilatation", d)
        cv2.imshow("Erosion", e)
        cv2.imshow("Ouverture", o)
        cv2.imshow("Fermeture", f)
        cv2.waitKey(0)

    # Exercise 3 : denoising
    if exercise == 3:
        res = debruitage(src_gray, element)
        cv2.imshow("Debruitage", res)
        cv2.waitKey(0)

    # Exercise 4 : morphological gradients
    if exercise == 4:
        cv2.namedWindow("Gradient interne", cv2.WINDOW_AUTOSIZE)
        cv2.namedWindow("Gradient externe", cv2.WINDOW_AUTOSIZE)
        cv2.namedWindow("Gradient morphologique", cv2.WINDOW_AUTOSIZE)

        gi = gradientInterne(src_gray, element)
        ge = gradientExterne(src_gray, element)
        gm = gradientMorphologique(src_gray, element)

        cv2.imshow("Gradient interne", gi)
        cv2.imshow("Gradient externe", ge)
        cv2.imshow("Gradient morphologique", gm)
        cv2.waitKey(0)

    # Exercise 5 : morphologcial reconstruction
    if exercise == 5:
        print("Sélectionnez les marqueurs en cliquant sur l'image, puis appuyez sur une touche")
        cv2.waitKey(0)

        marqueursD = np.zeros(src.shape[:2], dtype=np.uint8)
        for (x, y) in germes:
            cv2.circle(marqueursD, (x, y), 3, 255, -1)

        ri = reconstructionInferieure(src_gray, marqueursD, element)
        cv2.imshow("Reconstruction Inferieure", ri)

        marqueursE = src_gray.copy()
        marge = 5
        roi = (slice(marge, src_gray.shape[0]-marge),
               slice(marge, src_gray.shape[1]-marge))
        marqueursE[roi] = 255

        rs = reconstructionSuperieure(src_gray, marqueursE, element)
        cv2.imshow("Reconstruction Superieure", rs)
        cv2.waitKey(0)

    # Exercise 6: h-extrema
        minR = minimaRegionaux(src_gray, element, 20)
        srcCopy = src.copy()
        redImg = np.zeros_like(srcCopy)
        redImg[:, :, 2] = 255  # red mask
        srcCopy[minR > 0] = redImg[minR > 0]
        cv2.imshow("Minima regionaux", srcCopy)

        maxR = maximaRegionaux(src_gray, element, 20)
        srcCopy = src.copy()
        srcCopy[maxR > 0] = redImg[maxR > 0]
        cv2.imshow("Maxima Regionaux", srcCopy)
        cv2.waitKey(0)

    # Exercise 7: watershed
    if exercise == 7:
        markers = marqueurs(src, src_gray, element, 5, 20)
        markers_t = cv2.normalize(markers, None, 0, 255, cv2.NORM_MINMAX)
        markers_t = markers_t.astype(np.uint8)
        cv2.imshow("Markers' image", markers_t)
        
        dst = ligneDePartageDesEaux(src, markers)
        cv2.imshow("Watershed Segmentation", dst)
        cv2.waitKey(0)

    return 0


if __name__ == "__main__":
    main()