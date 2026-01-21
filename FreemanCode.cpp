#include"FreemanCode.h"

    //class FreemanCode
    //Construction d'un code de Freeman par suivi de la composante connexe de niveau 
    //de gris ng dans l'image (composante 8-connexe) extraction du code du bord en lignel. Hypothèse : bordure entourant l'image

 FreemanCode::FreemanCode(Mat ip, int gl){
   //Point 	_p0 ;
	_n = 0;
	int i, j, i0=0, j0=0;
	int k = 0;
   int w = ip.size().width;
	int h = ip.size().height;
   bool found = false;
      
	// parcours de l'image jusqu'à trouver le premier pixel de la composante connexe
	for(j=0; j<h && !found; j++)
	    for(i=0; i<w && !found; i++){
		   if (ip.at<uchar>(j,i) == gl){
		    found = true;
		    i0 = i;
		    j0 = j;
		   }
      }
	// premières directions
   _code.push_back(2);k++;
   _code.push_back(3);k++;
	i = i0;
	j = j0;
	int dir = 3;
	while (i != i0 || j != j0 || dir != 2){ // on n'est pas revenu au 1er point
	    int i_test = i+deltaI[dir]+deltaI[prev[dir]];
	    int j_test = j+deltaJ[dir]+deltaJ[prev[dir]];
	    if(ip.at<uchar>(j_test, i_test) == gl){
          dir = prev[dir];
          i = i_test;
          j = j_test;
	    }
	    else{
          i_test = i+deltaI[dir];
          j_test = j+deltaJ[dir];
          if(ip.at<uchar>(j_test, i_test) == gl){
             i = i_test;
             j = j_test;
          }
          else
             dir	= next[dir];
	    }
      _code.push_back(dir);k++;
	}
	_code.pop_back();//supprime le dernier élément
	_n = k - 1; //on est revenu au 1er pas
   _p0.x = i0;
   _p0.y = h-1-j0;
 }

    // taille du chemin en nombre de directions élémentaires
   int FreemanCode::getLength (){
      return _n;
   }
   
    // premier point
   Point FreemanCode::getP0 (){
      return Point(_p0);
   }

    // Variations en x et y pour un pas du chemin defini par le code 
    // l'indice ind doit vérifier 0 <= i < _n
    // Repère utilisé
    //
    //   ^ y
    //   |
    //   |
    //    ------> x 

   int FreemanCode::getDeltaX (int ind){
      return deltaX[_code.at(ind)];
   }

   int FreemanCode::getDeltaY (int ind){
      return deltaY[_code.at(ind)];
   }

    // direction élémentaire - hypothèse : chemin fermé
   int FreemanCode::getCode (int ind, int shift){
	 if(shift > 0)
	    return _code.at((ind+shift-1)%_n);
	 if(ind+shift >= 0)
	    return _code.at(ind+shift);
      return _code.at((ind+shift)%_n+_n);
   }

