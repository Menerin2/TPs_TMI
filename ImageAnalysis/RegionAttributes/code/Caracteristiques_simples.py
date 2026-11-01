import cv2 as cv #OpenCV
import sys
import math

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

# Calcul de l'aire d'une forme
def aire(mat):
    rows, cols = mat.shape
    aire = 0
    for i in range(rows):
        for j in range(cols):
            if mat[i][j] != 0:
                aire = aire+1
    print("AIRE: ",aire)
    return aire

# Calcul de la boîte englobante d'une forme
def LH(mat):
    rows, cols = mat.shape
    xmin = cols
    xmax = 0
    ymin = rows
    ymax = 0
    for i in range(rows):
        for j in range(cols):
            px = mat[i][j]
            if px != 0:
                if j < xmin:
                    xmin = j
                elif j > xmax:
                    xmax = j
                if i < ymin:
                    ymin = i
                elif i > ymax:
                    ymax = i
    print("boîte englobante L",xmax-xmin)
    print("boîte englobante H",ymax-ymin)

# Calcul du diamètre d'une forme
def diametre(mat):
    rows, cols = mat.shape
    max_dist = 0
    perimetre = 0
    copy_mat = mat.copy()
    for i in range(rows-1):
        for j in range(cols-1):
            #si on a un non-contour on l'enlève de la matrice
            if not (mat[i-1][j] == 0 or mat[i+1][j] == 0 or mat[i][j-1] == 0 or mat[i][j+1] == 0 or mat[i-1][j-1] == 0 or mat[i+1][j-1] == 0 or mat[i-1][j+1] == 0 or mat[i+1][j+1] == 0):
               copy_mat[i][j] = 0
    mat = copy_mat
    #on calcule les distances entre chaque contour
    for i in range(rows):
        for j in range(cols):
            if mat[i][j] != 0:
                perimetre = perimetre+1
                for k in range(rows):
                    for l in range(cols):
                        if mat[k][l] != 0:
                            dist = math.sqrt((l-j)**2+(k-i)**2)
                            if dist > max_dist:
                                max_dist = dist
    print("DIAMETRE: ",max_dist)  
    print("PERIMETRE ",perimetre)
    return max_dist, perimetre

# Calcul du centre de gravité de la forme
def centre(mat):
    rows, cols = mat.shape
    x = 0
    y = 0
    n = 0
    for i in range(rows):
        for j in range(cols):
            px = mat[i][j]  
            if px!= 0:
                x = x+j
                y = y+i
                n = n+1
    print("CENTRE: (",int(x/n),",",int(y/n),")")    

# Calcul du rapport isopérimétrique d'une forme
def rapport_iso(mat):
    _,perimetre = diametre(mat)
    rapport = (perimetre**2) / (4*math.pi * aire(mat))
    print("RAPPORT ISOPERIMETRIQUE: ",rapport)     
    return rapport

# Calcul de l'élongation d'une forme
def elongation(mat):
    elongation = 1 - 1/rapport_iso(mat)
    print("ELONGATION: ",elongation)
    return elongation

# PAS COMPLET
# Calcul du périmètre de Crofton
def crofton(mat):
    rows, cols = mat.shape
    perimetre = 0
    copy_mat = mat.copy()
    for i in range(rows-1):
        for j in range(cols-1):
            #si on a un non-contour on l'enlève de la matrice
            if not (mat[i-1][j] == 0 or mat[i+1][j] == 0 or mat[i][j-1] == 0 or mat[i][j+1] == 0 or mat[i-1][j-1] == 0 or mat[i+1][j-1] == 0 or mat[i-1][j+1] == 0 or mat[i+1][j+1] == 0):
               copy_mat[i][j] = 0
    mat = copy_mat
            #0,45,90,135 degrés
    inter = [0, 45, 90, 135]
    for i in range(rows):
        for j in range(cols):
            px = mat[i][j]
            if px != 0:
                if mat[i][j] != mat[i][j+1]:
                    inter[0] = inter[0]+1
                if mat[i][j] != mat[i+1][j+1]:
                    inter[1] = inter[1]+1
                if mat[i][j] != mat[i+1][j]:
                    inter[2] = inter[2]+1
                if mat[i][j] != mat[i+1][j-1]:
                    inter[3] = inter[3]+1
    print("CROFTON: ", )
                
def main():
    # Nom de l'image
    img_name = sys.argv[1] if len(sys.argv) > 1 else "blob"
    ex = int(sys.argv[2]) if len(sys.argv) > 2 else 1
    verbose = "--verbose" in sys.argv
    matrice = initImage(cv.imread(f"imagesTest/{img_name}.pgm", cv.IMREAD_GRAYSCALE))
    LH(matrice)
    centre(matrice)
    elongation(matrice)

if __name__ == "__main__":
    main()
    
