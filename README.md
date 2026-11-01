# Traitement et Modelisation de l'Image

This repository contains all the TP I did during the course "Traitement et Modelisation de l'Image"

## Organisation

The repository contains 2 main directories:

- 'ImageAnalysis': contains all the TP related to Contour and shape descriptors in images. 
- 'Segmentation': contains all the TP related to image segmentation.

Each TP directory contains:
- The description of the TP.
- The code and ressources used in the TP.
- The report related to the TP.
- A file 'launch.md' containing instructions to launch the TP.

## ImageAnalysis

### Geometrical Attributes of Contours

The objective of this TP is to analyze a 2D discrete contour: calculation of tangents, normals, curvature at each point, calculation of the contour length, and extraction of dominant points.

The explanation of each file and its purpose can be found within the file [EstimateursGeometriquesContours_2025-26.pdf](ImageAnalysis/GeometricalAttributsOfContours/EstimateursGeometriquesContours_2025-26.pdf)

### Filtering and Contour Comparaison

In this TP, we firstly focus on trying different filter from OpenCV and analyzing their effects on various images. 
Then, we proceed to contour detection with the Freeman code algorithm, the Boyer-Moore algorithm and the Wagner and Fischer algorithm.

### Region Attributes

In this TP, we focus on analyzing the differents attributes of regions in an image. We mainly used the Median axis, the Crofton perimeter and geometric moments.

## Segmentation