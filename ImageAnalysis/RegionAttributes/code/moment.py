import cv2 as cv #OpenCV
import os
import math

# On récupère les chemins vers les images de chiffre
folder = "imagesTest/"
imgPaths = []
for filename in os.listdir(folder):
    if filename.endswith(".pgm") and filename.startswith("x"):
        imgPaths.append(os.path.join(folder, filename))

for path in imgPaths:
    img = cv.imread(path, cv.IMREAD_GRAYSCALE)
    if img is None:
        print("Could not read the image:", path)
        continue

    _, img = cv.threshold(img, 128, 255, cv.THRESH_BINARY)
    moments = cv.moments(img)
    huMoments = cv.HuMoments(moments)

    for i in range(0, 7):
        huMoments[i] = -1 * math.copysign(1.0, huMoments[i]) * math.log10(abs(huMoments[i]))

    cv.imshow(f"Image: {path}", img)
    print(f"Image: {path}")
    print(f"Hu Moments:{huMoments.flatten()}\n")

    for path2 in imgPaths:
        if path != path2:
            img2 = cv.imread(path2, cv.IMREAD_GRAYSCALE)
            d1 = cv.matchShapes(img, img2, cv.CONTOURS_MATCH_I1, 0)
            d2 = cv.matchShapes(img, img2, cv.CONTOURS_MATCH_I2, 0)
            d3 = cv.matchShapes(img, img2, cv.CONTOURS_MATCH_I3, 0)
            print(f"Comparing {path} and {path2}:")
            print(f"d1: {d1}")
            print(f"d2: {d2}")
            print(f"d3: {d3}\n")
            
    cv.waitKey(0)
