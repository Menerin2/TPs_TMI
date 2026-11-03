# How to launch the regions based segmentation demonstrations

## main.cpp

To launch this file, go to the `code` directory and run the following C++ executable:

```bash
make;
./main (<image_name>) (<predicat>)
# If no image name is provided, it will default to "images/rice.png"
# If no predicat is provided, it will default to 1
```
List of image_name can be found in the [section below](#list-of-available-test-images). 

In this script, the `predicat` argument specifies which predicate to use for region growing. It can be 1, 2, or 3.
 - 1 : predicate 1
 - 2 : predicate 2
 - 3 : predicate 3

### Explanation of the predicates

Each similarity predicates defines if a pixel is included in the seeded region. They are based on a point $p$, a seed $g_i$ of the region $R_i$ and a threshold.

- $P_1(p,g_i) = \left\{\begin{array}{ll}\text{true if } |I(p) - I(g_i)| < \text{threshold} \\ \text{false otherwise} \end{array}\right.$
- $P_2(p,R_i) = \left\{\begin{array}{ll}\text{true if } |I(p) - \text{means}(R_i)| < \text{threshold} \\ \text{false otherwise} \end{array}\right.$
- $P_3(p,R_i) = \left\{\begin{array}{ll}\text{true if variance}(R_i\cup p)  < \text{threshold} \\ \text{false otherwise} \end{array}\right.$

## List of available test images

| image_name |
|------------|
| coins      |
| daisy      |
| lotus      |
| rice       |
| toit       |