'''
 * file : functions.py
 * brief : TP3 sur la segmentation basée région
 * author : Phuc Ngo
'''

import cv2
import numpy as np


def voisins(p, adjacence):
    """
    p: tuple or (x, y)
    adjacence: 4 or 8
    """
    vp = []

    # code goes here...

    return vp


def predicat1(src, g, p, seuil):
    """
    src: grayscale image
    g: seed point (x, y)
    p: point (x, y)
    """
    # code goes here...

    return True


def predicat2(src, Ri, p, seuil):
    """
    Ri: list of points already in region
    p: candidate point
    """
    # code goes here...

    return True


def predicat3(src, Ri, p, seuil):
    # code goes here...

    return True


def croissanceRegion(src, germes, seuil, predicat):
    """
    src      : grayscale image
    germes   : list of seed points [(x,y), ...]
    seuil    : threshold
    predicat : which predicate (1, 2, 3)
    """
    dst = np.zeros(src.shape[:2], dtype=np.uint8)

    # code goes here...

    return dst