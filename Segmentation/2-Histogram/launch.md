# How to launch the histogram demonstrations

## main.cpp

To launch this file, go to the `code` directory and run the following C++ executable:

```bash
make;
./main (<image_name>) (<exercice_number>)
# If no image name is provided, it will default to "images/coins.png"
# If no exercice number is provided, it will default to 1
```
List of image_name can be found in the [section below](#list-of-available-test-images). 

In this script, the `exercice_number` argument specifies which exercise to run. It can be 1, 2, 3, 4, or 5.
 - 1 : threshold
 - 2 : Hysteresis threshold
 - 3 : histogram
 - 4 : Otsu's method
 - 5 : kmean method

## List of available test images

| image_name |
|------------|
| coins      |
| daisy      |
| fruits     |
| lezard     |
| lotus      |
| toit       |
| ville      |