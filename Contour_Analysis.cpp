#include"commun.h"
#include"FreemanCode.h"
#include"Path.h"

/** Global variables **/

   int W, H;                   // taille de l'image initiale
   int iMin, iMax, jMin, jMax; // coordonnées de la ROI contenant l'objet analysé
   int GL;                     // niveau de gris de l'objet analysé
   int ZL;                     // niveau de zoom de la visualisation
   int NSIZE = 5;              //coefficient pour la visualisation des tangentes

   Mat ip;

/** Function Headers */

int getIVisu(Path , int );

int getJVisu(Path , int );

int getIVisu(int );

int getJVisu(int );

   

/**
 * @function main
 */
int main( int argc, char** argv )
{
   //Lecture de l'image à analyser
   ip = imread( argv[1], IMREAD_GRAYSCALE);
   if( ip.empty() )
   {
      cout << "Could not open or find the image!\n" << endl;
      cout << "Usage: " << argv[0] << " <Input image>" << endl;
      return -1;
   }
   GL = 0; //traitement des composantes connexes noires
   ZL = pow(2, 3);//Zoom de 8
   
   //Taille de l'image
   W = ip.size().width;
   H = ip.size().height;
   //cout<<"largeur:"<<W<<" hauteur:"<<H<<endl;
   // Création du contour de la région
   int margin = 3;
   FreemanCode c(ip, GL); //Recherche du code de Freman du bord 4-connexe en lignel
   
   Path p(c);             //Déduction du bord en lignel et calcul des tangentes
   iMin = p.getPMin().x - margin + 1; //Calcul de la boite englobante de la composante connexe
   iMax = p.getPMax().x + margin;
   jMax = H-1 - (p.getPMin().y - margin + 1);
   jMin = H-1 - (p.getPMax().y + margin);
      
   // Création de l'image de sortie - ipz
   Mat ipz=Mat::zeros(iMax-iMin+1, jMax-jMin+1, CV_8UC3);
   //Chgt d'echelle
   Mat ipzc;
   resize(ipz,ipzc,Size((iMax-iMin+1)*ZL, (jMax-jMin+1)*ZL));
   // Tracé des points de la grille 1/2
   for(int i=0; i<W*ZL; i+=ZL)
      for(int j=0; j<H*ZL; j+=ZL)
         circle(ipzc,Point(i, j), 1, Scalar(255,0,0), FILLED, LINE_8);
   // Tracé du chemin
   int ind, i1, j1, i2=0, j2=0;
   for(ind=0; ind<p.getLength()-1; ind++){
      i1 = getIVisu(p, ind);
      j1 = getJVisu(p, ind);
      i2 = getIVisu(p, ind+1);
      j2 = getJVisu(p, ind+1);
      line(ipzc,Point(i1, j1), Point(i2, j2),Scalar(0,250,0),1,LINE_8);
   }
   i1 = i2;
   j1 = j2;
   i2 = getIVisu(p, 0);
   j2 = getJVisu(p, 0);
   line(ipzc,Point(i1, j1), Point(i2, j2),Scalar(0,250,0),1,LINE_8);
   //Image calculée du contour avec la grille
   imshow("Contour",ipzc);
 
   // Tracé des normales associées aux tangentes symétriques
   for(ind = 0; ind < p.getLength(); ind+=5){
         int x = p.getContourX(ind);
         int y = p.getContourY(ind);
         int a = p.getContourTY(ind);
         int b = p.getContourTX(ind);
         
         i1 = getIVisu(x);
         j1 = getJVisu(y);
         float norme=sqrt(a*a+b*b);
         i2 = getIVisu((int)(x+(NSIZE*a)/norme+0.5));
         j2 = getJVisu((int)(y-(NSIZE*b)/norme+0.5));
         line(ipzc,Point(i1, j1), Point(i2, j2),Scalar(0,0,250),1,LINE_8);
      }
   imshow("Normales aux tangentes symétriques-rouges",ipzc);
   waitKey(0);

   // Tracé des normales associées aux tangentes positives
   for(ind = 0; ind < p.getLength(); ind+=5){
      int x = p.getContourX(ind);
      int y = p.getContourY(ind);
      int a = p.getContourTPY(ind);
      int b = p.getContourTPX(ind);
      
      i1 = getIVisu(x);
      j1 = getJVisu(y);
      float norme=sqrt(a*a+b*b);
      i2 = getIVisu((int)(x+(NSIZE*a)/norme+0.5));
      j2 = getJVisu((int)(y-(NSIZE*b)/norme+0.5));
      line(ipzc,Point(i1, j1), Point(i2, j2),Scalar(250,250,0),1,LINE_8);
   }
   imshow("Normales aux tangentes symétriques-rouges et positives-bleues",ipzc);
   waitKey(0);
   
      /***************************************************************************************
       * Affichage dans la console pour chaque point du contour des indices des points
       * de début et de fin de la tangente positive, c'est à dire du segment de droite discrete
       * le plus long dans le sens du parcours
       ****************************************************************************************/
  
   int n = c.getLength();
   
   cout<<"Tgte positive"<<endl;
   for(int i = 0; i < n; i++){
      cout<<"Point "<<i<<" : "<<i<<" --> "<< (i+p.getContourTPLgr(i))<<" : "<<p.getContourTPX(i)<<", "<<p.getContourTPY(i)<<endl;
   }
  

      /*
       * TO DO : En déduire les segments maximaux du contour et les tangentes lambdaMST - afficher leurs normales ...
       */
      
   
   
   
   
   
   
}//FIN Main

   
int getIVisu(Path p, int ind){
   return (p.getContourX(ind)-iMin+1)*ZL;
}

int getJVisu(Path p, int ind){
   return (H-1-p.getContourY(ind)-jMin)*ZL;
}

int getIVisu(int x){
   return (x-iMin+1)*ZL;
}

int getJVisu(int y){
   return (H-1-y-jMin)*ZL;
}

