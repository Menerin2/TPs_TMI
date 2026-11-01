import cv2 as cv #OpenCV
import sys

# On transforme l'image noir sur blanc en blanc sur noir
def initImage(img):
    rows, cols = img.shape
    res = img.copy()
    for i in range(rows):
        for j in range(cols):
            if img[i, j] == 0:
                res[i, j] = 200
            else:
                res[i, j] = 0
    return res

# Affichage d'une matrice dans la console
def printMatrice(mat):
    rows, cols = mat.shape
    for i in range(rows):
        print(" ".join(str(int(mat[i, j])) for j in range(cols)))

# Calcul de la distance de chanfrein avec une 8-connexité
def DT8_chanfrein(img, verbose=False):
    rows, cols = img.shape
    # On ajoute une bordure de 0 pour éviter les problèmes de bord
    chanfrein = cv.copyMakeBorder(img, 1, 1, 1, 1, cv.BORDER_CONSTANT, value=0)

    # Première passe
    for i in range(1, rows+1):
        for j in range(1, cols+1):
            val = chanfrein[i, j]
            if i > 0:
                if j > 0:
                    val = min(val, chanfrein[i-1, j-1] + 1)
                val = min(val, chanfrein[i-1, j] + 1)
                if j < cols - 1:
                    val = min(val, chanfrein[i-1, j+1] + 1)
            if j > 0:
                val = min(val, chanfrein[i, j-1] + 1)
            chanfrein[i, j] = val

    # Affichage de la matrice après la première passe si verbose
    if verbose:
        print("Première passe")
        printMatrice(chanfrein[1:rows+1, 1:cols+1])

    # Deuxième passe
    for i in range(rows-1, -1, -1):
        for j in range(cols-1, -1, -1):
            val = chanfrein[i, j]
            if i < rows - 1:
                if j < cols - 1:
                    val = min(val, chanfrein[i+1, j+1] + 1)
                val = min(val, chanfrein[i+1, j] + 1)
                if j > 0:
                    val = min(val, chanfrein[i+1, j-1] + 1)
            if j < cols - 1:
                val = min(val, chanfrein[i, j+1] + 1)
            chanfrein[i, j] = val

    # Affichage de la matrice après la deuxième passe si verbose
    if verbose:
        print("Deuxième passe")
        printMatrice(chanfrein[1:rows+1, 1:cols+1])

    # On enlève la bordure
    res = chanfrein[1:rows+1, 1:cols+1]
    return res

# Calcul de la distance de chanfrein avec une 4-connexité
def DT4_chanfrein(img, verbose=False):
    rows, cols = img.shape
    # On ajoute une bordure de 0 pour éviter les problèmes de bord
    chanfrein = cv.copyMakeBorder(img, 1, 1, 1, 1, cv.BORDER_CONSTANT, value=0)

    # Première passe
    for i in range(1, rows+1):
        for j in range(1, cols+1):
            val = chanfrein[i, j]
            if i > 0:
                val = min(val, chanfrein[i-1, j] + 1)
            if j > 0:
                val = min(val, chanfrein[i, j-1] + 1)
            chanfrein[i, j] = val

    # Affichage de la matrice après la première passe si verbose
    if verbose:
        print("Première passe")
        printMatrice(chanfrein[1:rows+1, 1:cols+1])

    # Deuxième passe
    for i in range(rows-1, -1, -1):
        for j in range(cols-1, -1, -1):
            val = chanfrein[i, j]
            if i < rows - 1:
                val = min(val, chanfrein[i+1, j] + 1)
            if j < cols - 1:
                val = min(val, chanfrein[i, j+1] + 1)
            chanfrein[i, j] = val

    # Affichage de la matrice après la deuxième passe si verbose
    if verbose:
        print("Deuxième passe")
        printMatrice(chanfrein[1:rows+1, 1:cols+1])

    # On enlève la bordure
    res = chanfrein[1:rows+1, 1:cols+1]
    return res

# Calcul de l'axe médian à partir de la distance de chanfrein avec une 8-connexité
def axeMedianDT8(matrice, verbose=False):
    res = matrice.copy()
    rows, cols = matrice.shape
    for i in range(rows):
        for j in range(cols):
            if matrice[i, j] > 0:
                # On regarde les 8 voisins du pixel (i, j)
                for k in range(-1, 2):
                    for l in range(-1, 2):
                        # On vérifie que les indices sont dans les limites de la matrice
                        if 0 <= i+k < rows and 0 <= j+l < cols:
                            if matrice[i+k, j+l] > matrice[i, j]:
                                res[i, j] = 0
                                break

    # Affichage de la matrice si verbose
    if verbose:
        print("Axe median DT8")
        printMatrice(res)

    return res

# Calcul de l'axe médian à partir de la distance de chanfrein avec une 4-connexité
def axeMedianDT4(matrice, verbose=False):
    # Liste des pixels voisins dans une 4-connexité
    neighors = [(0,1), (1,0), (0,-1), (-1,0)]
    res = matrice.copy()
    rows, cols = matrice.shape
    for i in range(rows):
        for j in range(cols):
            if matrice[i, j] > 0:
                # On regarde les 4 voisins du pixel (i, j)
                for k, l in neighors:
                    # On vérifie que les indices sont dans les limites de la matrice
                    if 0 <= i+k < rows and 0 <= j+l < cols:
                        if matrice[i+k, j+l] > matrice[i, j]:
                            res[i, j] = 0
                            break

    # Affichage de la matrice si verbose
    if verbose:
        print("Axe median DT4")
        printMatrice(res)

    return res

# Calcul du nombre de Yokoi pour un pixel (i, j)
def nombreYokoi(img, i, j):
    x0 = img[i, j-1]
    x1 = img[i+1, j-1]
    x2 = img[i+1, j]
    x3 = img[i+1, j+1]
    x4 = img[i, j+1]
    x5 = img[i-1, j+1]
    x6 = img[i-1, j]
    x7 = img[i-1, j-1]

    yokoi = x0*(1-x1*x2)+x2*(1-x3*x4)+x4*(1-x5*x6)+x6*(1-x7*x0)

    return yokoi

# Calcul du nombre de voisins en 8-connexité pour un pixel (i, j)
def nbVoisins8(img, i, j):
    nb = 0
    for di in range(-1, 2):
        for dj in range(-1, 2):
            if di == 0 and dj == 0:
                continue
            if img[i+di, j+dj] > 0:
                nb += 1
    return nb

# Retourne True si le pixel (i, j) est un point simple, False sinon
def estPointSimple(img, i, j):
    # Pixel appartenant au fond
    if img[i, j] == 0:
        return False

    # True si point simple, False sinon
    return nombreYokoi(img, i, j) == 1

# Calcul du squelette d'une forme à partir de sa distance de chanfrein
def squelette(distance, verbose=False):
    rows, cols = distance.shape
    squelette = distance.copy()

    # Squelette que composé de 0 et 1 pour faciliter le calcul du nombre de Yokoi
    for i in range(rows):
        for j in range(cols):
            squelette[i, j] = 1 if distance[i, j] > 0 else 0

    # Liste des pixels de la forme pour éviter de parcourir toute l'image à chaque itération
    pixels = []
    for i in range(rows):
        for j in range(cols):
            if distance[i, j] > 0:
                pixels.append((distance[i, j], i, j))

    # Tri des pixels pour traiter d'abord les pixels de bordure
    pixels.sort(key=lambda x: x[0])

    # On ajoute une bordure valant 0 à l'image
    pad = cv.copyMakeBorder(squelette, 1, 1, 1, 1, cv.BORDER_CONSTANT, value=0)

    changed = True
    while changed:
        changed = False
        for _, i, j in pixels:
            # On ajoute 1 à cause de la bordure
            pi, pj = i + 1, j + 1

            if pad[pi, pj] == 0:
                continue

            # Cas d'une bordure de branche
            if nbVoisins8(pad, pi, pj) <= 1:
                continue

            # Si le point est simple, on le supprime
            if estPointSimple(pad, pi, pj):
                pad[pi, pj] = 0
                # On recommence une itération
                changed = True

    # On enlève la bordure
    res = pad[1:rows+1, 1:cols+1]

    # Ajout de la bordure de la forme pour un meilleur affichage
    for i in range(rows):
        for j in range(cols):
            if res[i, j] > 0:
                res[i, j] = 255
            if distance[i, j] == 1:
                res[i, j] = 50

    if verbose:
        print("Squelette final")
        printMatrice(res)
    
    return res


def main():
    # Nom de l'image
    img_name = sys.argv[1] if len(sys.argv) > 1 else "blob"
    ex = int(sys.argv[2]) if len(sys.argv) > 2 else 1
    verbose = "--verbose" in sys.argv
    matrice = initImage(cv.imread(f"imagesTest/{img_name}.pgm", cv.IMREAD_GRAYSCALE))
    chanfrein8 = DT8_chanfrein(matrice, verbose=verbose)
    chanfrein4 = DT4_chanfrein(matrice, verbose=verbose)
    ratioDT8 = int(255/max(chanfrein8.flatten()))
    ratioDT4 = int(255/max(chanfrein4.flatten()))
    if ex == 1:
        cv.imshow("DT8", chanfrein8*ratioDT8)
        cv.imshow("DT4", chanfrein4*ratioDT4)
        cv.waitKey(0)
    axe4 = axeMedianDT4(chanfrein4, verbose=verbose)
    axe8 = axeMedianDT8(chanfrein8, verbose=verbose)
    if ex == 2:
        cv.imshow("Axe median DT4", axe4*ratioDT4)
        cv.waitKey(0)
        cv.imshow("Axe median DT8", axe8*ratioDT8)
        cv.waitKey(0)
    if ex == 3:
        squelette4 = squelette(chanfrein4, verbose=verbose)
        cv.imshow("Squelette DT4 + points simples", squelette4)
        cv.waitKey(0)

    cv.destroyAllWindows()

if __name__ == "__main__":
    main()