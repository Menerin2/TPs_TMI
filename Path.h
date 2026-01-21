#ifndef PATH_H
#define PATH_H

#include "commun.h"
#include "FreemanCode.h"
#include "DigitalTangent.h"
#include "DigitalTangentPositive.h"

#include <iostream>


class Path {
   
   class ContourPoint{
      
   public :
      // repere x "vers le haut" et y "vers la droite"
      // (x,y) designe le point demi-entier (x+1/2, y+1/2)
      int _x;
      int _y;
      
      // informations geometriques calculees:
      // vecteur tangent
      int _tx;
      int _ty;
      
      // vecteur tangent  dans la direction positive
      int _tpx;
      int _tpy;
      
      int _lgrTp; // Nombre de points de la tangente positive
      
      
      // courbure : TODO
      
      ContourPoint();//constructeur
      
   };
   
   int _n;                 // nb de points de contour
   
   Path::ContourPoint _tabPts[1000]; // tableau des points de contour
   
   int _xm;                // abscisse minimum
   int _ym;                // ordonnée minimum
   int _xM;                // abscisse maximum
   int _yM;                // ordonnée maximum
   
   void computeCoordinates(FreemanCode);
   
   void computeTangents(FreemanCode );
      
   
   public :
   
   Path(FreemanCode);
   
   void computeTangentsPos(FreemanCode );
   
   int getLength();
   
   Point getPMin();
   
   Point getPMax();
   
   int getContourX(int);
   
   int getContourY(int );
   
   int getContourTX(int );
      
   int getContourTY(int);
   
   int getContourTPX(int );
   
   int getContourTPY(int );
   
   int getContourTPLgr(int );
   
   };
#endif