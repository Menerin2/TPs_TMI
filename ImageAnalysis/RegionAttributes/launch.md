# How to launch the filtering demonstrations

## Caracteristiques_simples.py

To launch this file, go to the `code` directory and run the following Python script:

```bash
python3 Caracteristiques_simples.py (<image_name>)
# If no image name is provided, it will default to "blob"
```
List of image_name can be found in the [section below](#list-of-available-test-images). 

## Distance.py

To launch this file, go to the `code` directory and run the following Python script:

```bash
python3 Distance.py (<image_name>) (<exercice_number>) (--verbose)
# If no image name is provided, it will default to "xt7_1"
# If no exercice number is provided, it will default to 1
```
List of image_name can be found in the [section below](#list-of-available-test-images). 

In this script, the `exercice_number` argument specifies which exercise to run. It can be 1, 2, or 3.
 - 1 compute and display the distance to the background with distance d4 and d8
 - 2 compute and display the median axis of the object
 - 3 compute and display the skeleton of the object

The `--verbose` flag can be used to display additional information during execution.

## Moment.py

```bash
python3 Moment.py 
```
A table with all the computed moments and their comparison can be found in the [report](CompteRendu.pdf)

## List of available test images

| image_name |
|------------|
| blob       |
| disque     |
| etoile1    |
| etoile2    |
