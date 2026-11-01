'''
 * file : functions.py
 * brief : TP4 sur la segmentation basée contour
 * author : Phuc Ngo
'''

import cv2
import numpy as np


def elementStruturant(taille, type):
    """
    taille : int
    type   : string ("carre", "croix", "disque", etc.)
    """
    se = None

    # code goes here...

    return se


def dilatation(src, se):
    dst = np.zeros_like(src)

    # code goes here...

    return dst


def erosion(src, se):
    dst = np.zeros_like(src)

    # code goes here...

    return dst


def fermeture(src, se):
    # code goes here...

    return src


def ouverture(src, se):
    # code goes here...

    return src


def debruitage(src, se):
    # code goes here...

    return src


def gradientInterne(src, se):
    # code goes here...

    return src


def gradientExterne(src, se):
    # code goes here...

    return src


def gradientMorphologique(src, se):
    # code goes here...

    return src


def reconstructionInferieure(src, mrk, se, maxIter):
    # code goes here...

    return src


def reconstructionSuperieure(src, mrk, se, maxIter):
    # code goes here...

    return src


def maximaRegionaux(src, se, h):
    # code goes here...

    return src


def minimaRegionaux(src, se, h):
    # code goes here...

    return src

def marqueurs(src, src_gray, se, gSize, h):
    marqueurImage = np.zeros(src_gray.shape, dtype=np.int32)
    # code goes here...

    return marqueurImage



def ligneDePartageDesEaux(src, marqueurImage):
    dst = np.zeros(src.shape, dtype=np.uint8)
    # code goes here...

    return dst
