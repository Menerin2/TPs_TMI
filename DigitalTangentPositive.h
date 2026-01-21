#ifndef DIGITALTANGENTPOSITIVE_H
#define DIGITALTANGENTPOSITIVE_H

#include"commun.h"
#include"FreemanCode.h"
#include"DigitalLineSegment.h"

class DigitalTangentPositive {
   
   DigitalLineSegment _d;  // droite 4-c du premier quadrant
   int _n;                 // taille du segt
   int _dir0, _dir1;       // directions paire et impaire composant le segt,
                           // l'une d'elle peut etre indefinie = -1
   int _xm, _ym, _xM, _yM; // points extremes du segt dans le 1er quadrant
   // axes x vers la droite et y vers le haut
   
   
   bool consistentMove (int);

   public :
   
   DigitalTangentPositive(FreemanCode , int );
   
   int getXM();
   
   int getYM();
   
   int getA();
   
   int getB();
   
   int getN();
   
   int getQuadrant();

};
#endif