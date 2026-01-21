#include"Path.h"

//class Path

   Path::ContourPoint::ContourPoint(){ //constructeur
      _x=0;_y=0;_tx=0;_ty=0;
   }
	
   Path::Path(FreemanCode c){          //constructeur
		_n = c.getLength();
		computeCoordinates(c);
      computeTangents(c);      // calcul des tangentes symétriques en chaque point
      computeTangentsPos(c);  // calcul des tangentes positives en chaque point
	}


	void Path::computeCoordinates(FreemanCode c){
		int x=c.getP0().x, y=c.getP0().y;
		_xm=_xM=x;
		_ym=_yM=y;
		_tabPts[0]._x=x;
		_tabPts[0]._y=y;

		for (int i = 0; i < _n-1; i++){
			x =x + c.getDeltaX(i);
			if (x < _xm) 
				_xm = x;
			if (x > _xM)
				_xM = x;
			y =y + c.getDeltaY(i);
			if (y < _ym)
				_ym = y;
			if (y > _yM)
				_yM = y;
			_tabPts[i+1]._x=x;
			_tabPts[i+1]._y=y;
		}
	}

   /*
	* Calcul de la tangente symétrique en chaque point du contour
	*/
   void Path::computeTangents(FreemanCode c){
      
		int sym4[4][4] = {{1,1},{-1,1},{-1,-1},{1,-1}};

		for(int i = 0; i < _n; i++){
			DigitalTangent t(c, i);
			// calcul de symetries a partir des caracteristiques 
			// rapportees au 1er quadrant
			int a = t.getA();
			int b = t.getB();
			int quad = t.getQuadrant();
			_tabPts[i]._tx = sym4[quad][0]*b;
			_tabPts[i]._ty = sym4[quad][1]*a;
		}
   
	}



   /*
	* Calcul de la tangente positive en chaque point du contour
	*/
   void Path::computeTangentsPos(FreemanCode c){
    
   int sym4[4][4] = {{1,1},{-1,1},{-1,-1},{1,-1}};
   
   for(int i = 0; i < _n; i++){
      DigitalTangentPositive tp(c, i);
      // calcul de symetries a partir des caracteristiques
      // rapportees au 1er quadrant
      int a = tp.getA();
      int b = tp.getB();
      int quad = tp.getQuadrant();
      _tabPts[i]._tpx = sym4[quad][0]*b;
      _tabPts[i]._tpy = sym4[quad][1]*a;
      _tabPts[i]._lgrTp=tp.getN();
   }
   
}

   int Path::getLength(){
		return _n;
	}

	Point Path::getPMin(){
		return Point(_xm, _ym);
	}

   Point Path::getPMax(){
		return Point(_xM, _yM);
	}

	int Path::getContourX(int i){
		return _tabPts[i]._x;
	}

	int Path::getContourY(int i){
		return _tabPts[i]._y;
	}

   int Path::getContourTX(int i){
		return _tabPts[i]._tx;
	}

	int Path::getContourTY(int i){
		return _tabPts[i]._ty;
	}

   int Path::getContourTPX(int i){
      return _tabPts[i]._tpx;
   }

   int Path::getContourTPY(int i){
      return _tabPts[i]._tpy;
   }

   int Path::getContourTPLgr(int i){
      return _tabPts[i]._lgrTp;
   }



