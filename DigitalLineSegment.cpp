
#include"DigitalLineSegment.h"


   //class DigitalLineSegment -- implémentation
	// droite 4-connexe du 1er quadrant (déplacements 0 et 1)
	// mu <= ax - by < mu + a+ b 

	

   void DigitalLineSegment::initDLS(int firstMove){
      _U.x=0;_U.y=0;
		_L.x=0;_L.y=0;

		_mu = 0;

		if (firstMove == 0){
			_a = 0;
			_b = 1;
			_Us.x=1;_Us.y=0;
         _Ls.x=1;_Ls.y=0;
		}
		else{
			_a = 1;
			_b = 0;
         _Us.x=0;_Us.y=1;
         _Ls.x=0;_Ls.y=1;
		}
	}

   DigitalLineSegment::DigitalLineSegment(DigitalLineSegment &d){
		_a = d._a;
		_b = d._b;
		_mu = d._mu;
      
		_U.x=d._U.x;
      _U.y=d._U.y;
		_L.x=d._L.x;
      _L.y=d._L.y;
      
      _Us.x=d._Us.x;
      _Us.y=d._Us.y;
      _Ls.x=d._Ls.x;
      _Ls.y=d._Ls.y;
	}

   DigitalLineSegment::DigitalLineSegment(){
		_a = 0;
		_b = 0;
		_mu = 0;
      
      _U.x=0;_U.y=0;
      _L.x=0;_L.y=0;
      
      _Us.x=0;_Us.y=0;
      _Ls.x=0;_Ls.y=0;
	}


   void DigitalLineSegment::copy(DigitalLineSegment d){
		_a = d._a;
		_b = d._b;
		_mu = d._mu;
      
      _U.x=d._U.x;
      _U.y=d._U.y;
      _L.x=d._L.x;
      _L.y=d._L.y;
      
      _Us.x=d._Us.x;
      _Us.y=d._Us.y;
      _Ls.x=d._Ls.x;
      _Ls.y=d._Ls.y;

	}

   int DigitalLineSegment::getA(){
		return _a;
	}
	int DigitalLineSegment::getB(){
		return _b;
	}

	

	// Ajout d'un point a l'extremite d'abscisse positive d'un segment
	// de droite 4-connexe du 1er quadrant 

   bool DigitalLineSegment::addPositivePoint (int x, int y){
		int r;
		r = _a*x-_b*y;
		if(_mu<=r && r<_mu+_a+_b){
         if (r==_mu){
            _Us.x=x; _Us.y=y;
         }
         if(r==_mu+_a+_b-1){
            _Ls.x=x; _Ls.y=y;
         }
			return true;
		}

		if(r==_mu-1){ // la pente augmente
			//mise a jour des points d'appui
         _L.x=_Ls.x;
         _L.y=_Ls.y;//setLocation(_Ls);
         _Us.x=x; _Us.y=y;


			//mise a jour des caracteristiques
			_a = y - _U.y;
			_b = x - _U.x;
			_mu = _a*x-_b*y;
			return true;
		}

		if(r==_mu+_a+_b){ // la pente diminue
         //mise a jour des points d'appui
         _U.x=_Us.x;
         _U.y=_Us.y;//setLocation(_Us);
			 _Ls.x=x; _Ls.y=y;

			//mise a jour des caracteristiques
			_a = y - _L.y;
			_b = x - _L.x;
			_mu = _a*(x-1)-_b*(y+1)+1;
			return true;
		}
		// sinon le nouveau point ne permet pas de continuer la droite
		return false;
	}


	// Ajout d'un point a l'extremite d'abscisse negative d'un segment
	// de droite 4-connexe du 1er quadrant 

   bool DigitalLineSegment::addNegativePoint(int x, int y){
		int r;
		r = _a*x-_b*y;
		if(_mu<=r && r< _mu+_a+_b){
         if (r==_mu){
            _U.x=x;_U.y=y;
         }
         if(r == _mu+_a+_b-1){
            _L.x=x;_L.y=y;
         }
			return true;
		}

		if(r==_mu-1){ //la pente diminue
			// mise a jour des points d'appui
         _Ls.x=_L.x;
         _Ls.y=_L.y;//setLocation(_L);
			_U.x=x;_U.y=y;

			// mise a jour des caracteristiques
			_a = _Us.y - y;
			_b = _Us.x - x;
			_mu = _a*x-_b*y;
			return true;
		}

		if(r==_mu+_a+_b){ // la pente augmente
			// mise a jour des points d'appui
         _Us.x=_U.x;
         _Us.y=_U.y;//setLocation(_U);
         _L.x=x;_L.y=y;

			// mise a jour des caracteristiques
			_a = _Ls.y-y;
			_b = _Ls.x-x;
			_mu = _a*(x-1)-_b*(y+1)+1;
			return true;
		}
		// le nouveau point ne permet pas de continuer la droite
		return false;
	}


