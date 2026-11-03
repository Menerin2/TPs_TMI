# How to launch the watershed demonstrations

## main.cpp

To launch this file, go to the `code` directory and run the following C++ executable:

```bash
make;
./main (<image_name>) (<exercice_number>) (<typeSE>) (<size>)
# If no image name is provided, it will default to "images/rice.png"
# If no typeSE is provided, it will default to "carre"
# If no size is provided, it will default to 1
```
List of image_name can be found in the [section below](#list-of-available-test-images). 

In this script, the `exercice_number` argument specifies which exercise to run. It can be 2, 3, 4, 5, 6, or 7.
 - 2 : morphological operators
 - 3 : denoising
 - 4 : morphological gradients
 - 5 : morphological reconstruction
 - 6 : h-extrema
 - 7 : markers + watershed

`typeSE` correponds to the type of structuring element used in the morphological operations. It can be one of the following:
 - "carre" : square
 - "disque" : disk
 - "diamant" : diamond
 - "croix" : cross
 - "hline" : horizontal line
 - "vline" : vertical line
An example of each type can be visualized at the beginning of the [Report](CompteRendu.pdf)

The structuring element can be of two sizes 1 or 2.

## List of available test images

| image_name  |
|-------------|
| bottle_bruit|
| circuit     |
| coins       |
| lena_bruit  |
| lotus       |
| puppy_bruit |
| puppy       |
| rice        |
| tree_bruit  |
| tree        |