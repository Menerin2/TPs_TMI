#ifndef DIGITALTANGENT_H
#define DIGITALTANGENT_H

#include"commun.h"
#include"FreemanCode.h"
#include"DigitalLineSegment.h"

class DigitalTangent {
   
   DigitalLineSegment _d;  // droite 4-c du premier quadrant
   int _n;                 // tangente symetrique de taille 2n+1
   int _dir0, _dir1;       // directions paire et impaire composant la tangente,
                           // l'une d'elle peut etre indefinie = -1
   int _xm, _ym, _xM, _yM; // points extremes de la tangente dans le 1er quadrant
                           // axes x vers la droite et y vers le haut
   
   public :
   
   bool consistentMove (int );
   
   DigitalTangent(FreemanCode , int );

   int getA();
      
   int getB();
   
   int getQuadrant();


};
#endif