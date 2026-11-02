"""
Application de l'algorithme de Freeman
"""
import sys
import cv2 as cv #OpenCV
from matplotlib import pyplot as plt #matplotlib pour afficher les images

# Codage des 8 directions
DIRECTIONS = [(1, 0), (1, -1), (0, -1), (-1, -1), (-1, 0), (-1, 1), (0, 1), (1, 1)]
P0 = None # Le premier pixel noir trouvé
P1 = None 

"""
Fonction qui retourne les coordonnées du premier pixel noir trouvé
Paramètres:
- img: image ou cherche
- start_x, start_y: coordonnées de départ de la recherche
Retourne:
- (x, y): coordonnées du premier pixel noir trouvé
(None, None) si aucun pixel noir trouvé
"""
def get_first_black_pixel(img, start_x, start_y):
    # Parcours de l'image à partir des coordonnées de départ données
    for y in range(start_y, img.shape[0]):
        for x in range(start_x, img.shape[1]):
            # Verifie si le pixel est noir
            if img[y, x] == 0:
                return (x, y)
    # Aucun pixel noir trouve
    return (None, None)

"""
Fonction qui retourne les coordonnées du prochain pixel noir
en et la direction utilisee pour y arriver.
Paramètres:
- img: l'image ou l'algorithme est applique
- x, y: la position du pixel noir courrant 
- dir_init: la direction de depart pour la recherche du pixel suivant
Retourne:
- (new_x, new_y): la position du prochain pixel noir
- dir: la direction utilisée pour se rendre au prochain pixel noir
"""
def get_next_pixel(img, x, y, dir_init):
    # On teste pour les 8 directions
    for i in range(8):
        dir = (dir_init + i)%8
        dx, dy = DIRECTIONS[dir]
        new_x = x+dx
        new_y = y+dy
        # Si on atteint un bord de l'image, on passe à la direction suivante
        if new_x < 0 or new_y < 0 or new_x >= img.shape[1] or new_y>= img.shape[0]:
                continue
        # On a trouvé le prochain pixel noirs
        if img[new_y, new_x] == 0:
            return (new_x, new_y), dir
    # Aucun pixel noir trouvé
    return (None, None), None

def main(sys):
    # Nom de l'image
    if len(sys.argv) < 2:
        img_name = "xt7_1"
    else:
        img_name = sys.argv[1]
    # Chemin de l'image
    path = 'Archive/ImagesTest/ImagesTest/'+img_name+'.pgm'
    # Lecture de l'image
    img = cv.imread(path, cv.IMREAD_GRAYSCALE)
    if img is None:
        raise ValueError("Image not found or unable to load")
    rows, cols = img.shape
    # Tableau d'entier stockant le code de Freeman
    out = []

    # On initialise la direction initiale à 4 car on parcours
    # l'image avec des directions 0 et qu'on parcours l'image 
    # en sens anti horaire
    dir = 4
    dir_init = 4

    # On recupere le premier pixel noir P0
    P0 = get_first_black_pixel(img, 0, 0)
    if P0 == (None, None):
        raise ValueError("No black pixel found")

    # On calcul le prochain pixel
    P1, dir = get_next_pixel(img, P0[0], P0[1], dir)
    next_pixel = P1

    # Tant qu'on est pas retourner au point P0
    while next_pixel != P0:
        # On ajoute la direction au code de Freeman
        out.append(dir)
        # On modifie la direction initiale en prenant
        # la direction opposée + 1 de la dernière 
        # direction utilisée
        dir_init = (dir + 5)%8

        # On récupère le prochain pixel noir et la direction necessaire
        next_pixel, dir = get_next_pixel(img, next_pixel[0], next_pixel[1], dir_init)

    # On ajoute la dernière direction symbolisant le retour vers P0
    out.append(dir)

    # On affiche le point de départ P0 et le code de Freeman
    print(f"P0={P0}, C={out}")
    # Affichage de l'image avec le point de départ P0
    plt.imshow(img, cmap='gray')
    plt.scatter(P0[0], P0[1], color='red', marker='x')
    plt.show()

if __name__ == "__main__":
    main(sys)
