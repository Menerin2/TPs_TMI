#ifndef FREEMANCODE_H
#define FREEMANCODE_H

#include"commun.h"


class FreemanCode {
   
   vector<int> _code;
   
   int _n=0;    // nb de directions
   
   Point _p0; // premier point obtenu par balayage de l'image haut-bas/gauche-droite
   
   int deltaI[4] = {1, 0, -1, 0};
   int deltaJ[4] = {0, -1, 0, 1};
   int prev[4] = {3, 0, 1, 2};
   int next[4] = {1, 2, 3, 0};
   int initialCapacity = 100;
   
   int deltaX[4] = {1, 0, -1, 0};
   int deltaY[4] = {0, 1, 0, -1};
   

   public:
   
   FreemanCode(Mat, int ) ; //Constructeur
   
   int getLength ();
   
   Point getP0 ();

   int getDeltaX (int);

   int getDeltaY (int);

   int getCode (int , int );

};

#endif