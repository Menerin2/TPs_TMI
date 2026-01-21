#ifndef DIGITALLINESEGMENT_H
#define DIGITALLINESEGMENT_H

#include"commun.h"


class DigitalLineSegment {
   // droite 4-connexe du 1er quadrant (déplacements 0 et 1)
   // mu <= ax - by < mu + a+ b
   
   int _a, _b, _mu; /* caracteristiques */
   
   Point _U; /*pt d'appui sup d'absc min*/
   Point _L; /*pt d'appui inf d'absc min*/
   Point _Us;/*pt d'appui sup d'absc max*/
   Point _Ls;/*pt d'appui inf d'absc max*/
   
   
public:
   
   DigitalLineSegment(DigitalLineSegment &);//constructeur
   
   void initDLS(int);

   DigitalLineSegment();         //constructeur

   
   void copy(DigitalLineSegment );

   int getA();

   int getB();

   bool addPositivePoint (int , int );

   bool addNegativePoint(int , int );
   
};

#endif