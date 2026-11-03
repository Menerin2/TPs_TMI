# How to launch the tests on OpenCV

## main.cpp

To launch this file, go to the `code` directory and run the following C++ executable:

```bash
make;
./main (<image_name>)
# If no image name is provided, it will default to "images/coins.png"
```
List of image_name can be found in the [section below](#list-of-available-test-images). 

When the image is displayed, you can interact with the window using the keyboard:
- Press any key to close the window and exit the program.
- press `r` to switch to the red version of the image
- press `g` to switch to the green version of the image
- press `b` to switch to the blue version of the image
- press `y` to switch to the grayscale version of the image

## List of available test images

| image_name |
|------------|
| coins      |
| daisy      |
| lezard     |
| lotus      |
| ville      |