"""
Demonstration des differentes fonctions de filtrage d'openCV.
Auteur: LOI Léo
"""

import cv2 as cv #OpenCV
from matplotlib import pyplot as plt #matplotlib pour afficher les images

# Constantes pour les types de flous
BLUR = 0
GAUSSIAN_BLUR = 1
MEDIAN_BLUR = 2

"""
Demonstration des types de filtrage: blur, gaussian_blur et median_blur.
"""
def blurring_demo():
    # Nom de l'image a charger
    name = 'casserole'
    size = 3
    # Chemin de l'image
    path = 'Archive/imageFiltres/imageFiltres/'+name+'.tif'
    # Ouverture de l'image
    img = cv.imread(path)
    assert img is not None, "file could not be read"
 
    # On stocke les images filtrees dans une liste
    filtred = [None]*3
    filtred[BLUR] = cv.blur(img, (size,size))
    filtred[GAUSSIAN_BLUR] = cv.GaussianBlur(img,(size,size),0)
    filtred[MEDIAN_BLUR] = cv.medianBlur(img,size)

    # Affichage des images filtrees
    cpt = 0
    while(True):
        plt.plot()
        plt.imshow(filtred[cpt])
        if cpt == 0:
            plt.title('blur')
        elif cpt == 1:
            plt.title('Gaussian')
        elif cpt == 2:
            plt.title('Median')
        plt.xticks([]), plt.yticks([])

        # On change d'image si un bouton est presse
        if(plt.waitforbuttonpress(20)):
            cpt = cpt+1
            if cpt > 2:
                break

"""
Demonstration du filtre bilaterak.
"""
def bilateral_demo():
    # Nom de l'image a charger
    name = 'snack-orig'
    # Chemin de l'image
    path = 'Archive/imageFiltres/imageFiltres/'+name+'.png'
    # Ouverture de l'image
    img = cv.imread(path)
    assert img is not None, "file could not be read"

    # Demonstration de la modification du parametre d
    bilateral_d10 = cv.bilateralFilter(img, 10, 50, 50)
    bilateral_d50 = cv.bilateralFilter(img, 50, 50, 50)
    bilateral_d100 = cv.bilateralFilter(img, 100, 50, 50)
    plt.subplot(221),plt.imshow(img),plt.title('Original')
    plt.xticks([]), plt.yticks([])
    plt.subplot(222),plt.imshow(bilateral_d10),plt.title('d = 10')
    plt.xticks([]), plt.yticks([])
    plt.subplot(223),plt.imshow(bilateral_d50),plt.title('d = 50')
    plt.xticks([]), plt.yticks([])
    plt.subplot(224),plt.imshow(bilateral_d100),plt.title('d = 100')
    plt.xticks([]), plt.yticks([])
    plt.show()

    # Demonstration de la modification du parametre sigma
    bilateral_50 = cv.bilateralFilter(img, 50, 10, 10)
    bilateral_100 = cv.bilateralFilter(img, 50, 100, 100)
    bilateral_200 = cv.bilateralFilter(img, 50, 200, 200)
    plt.subplot(221),plt.imshow(img),plt.title('Original')
    plt.xticks([]), plt.yticks([])
    plt.subplot(222),plt.imshow(bilateral_50),plt.title('sigma = 50')
    plt.xticks([]), plt.yticks([])
    plt.subplot(223),plt.imshow(bilateral_100),plt.title('sigma = 100')
    plt.xticks([]), plt.yticks([])
    plt.subplot(224),plt.imshow(bilateral_200),plt.title('sigma = 200')
    plt.xticks([]), plt.yticks([])
    plt.show()

# Lancement des demonstrations
# Decommenter la ligne correspondante pour lancer la demontration
blurring_demo()
bilateral_demo()