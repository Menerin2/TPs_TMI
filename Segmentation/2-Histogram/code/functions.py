'''
 * file : functions.py
 * brief : TP2 sur la segmentation basée histogramme
 * author : Phuc Ngo
'''

import cv2
import numpy as np


def seuillage(image: np.ndarray, seuil: int) -> np.ndarray:
    # Create result image filled with zeros (same size, 8-bit)
    res = np.zeros(image.shape[:2], dtype=np.uint8)

    # code goes here...

    return res


def seuillageHysteresis(image: np.ndarray, seuil_bas: int, seuil_haut: int) -> np.ndarray:
    # Create result image filled with zeros (same size, 8-bit)
    res = np.zeros(image.shape[:2], dtype=np.uint8)

    # code goes here...

    return res


def histogramme(image: np.ndarray, intervalle: int):
    # code goes here...

    return []


def calculeVariance(histo, seuil: int, nbPixels: int) -> float:
    # code goes here...

    return 0.0


def seuillageOtsu(image: np.ndarray) -> int:
    # code goes here...

    return 127


def kmean(image: np.ndarray, k: int) -> np.ndarray:
    # code goes here...

    return image