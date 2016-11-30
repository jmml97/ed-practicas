#include "cronologia.h"
#include <fstream>
#include <iostream>

using namespace std;

// Esta funcion también puede implementarse como método de la clase Cronologia (A vuestra elección)
Cronologia & Union(const Cronologia & c1, const Cronologia & c2){
  //completar implementacion
}


// Este método también puede implementarse como operator<< asociado a la clase Cronología (A vuestra elección).  
void ImprimeCronologia (const Cronologia &c, ostream &os){
   Cronologia::const_iterator it;
   for (it=c.begin(); it!=c.end();++it){
       os<<(*it).first<<"#";          //año esta en el key del map
       EventoHistorico::const_iterator it_ev;
       for (it_ev=(*it).second.begin(); it_ev!=(*it).second.end();++it_ev)
        os<<(*it_ev)<<"#";
   }
}   




int main(int argc, char * argv[]){

  if (argc!=3 && argc!=4){
      cout<<"Error: debe dar al menos los nombres de dos ficheros con cronologías. "<<endl;
      cout<<"[Opcional]: un tercer nombre de fichero para guardar la cronología resultante."<<endl;
      return 0;
   }

   ifstream f1 (argv[1]);
   if (!f1){
    cout<<"No puedo abrir el fichero "<<argv[1]<<endl;
    return 0;
   }
   ifstream f2 (argv[2]);
   if (!f2){
    cout<<"No puedo abrir el fichero "<<argv[2]<<endl;
    return 0;
   }

   Cronologia c1, c2, cUnion;
   f1 >> c1;    // Cargamos los datos de los ficheros en las cronologías.
   f2 >> c2; 

   cUnion = Union(c1, c2);
   
   if (argc==3)   //No se dio fichero de salida, imprimimos en cout
      ImprimeCronologia(cUnion,cout);
   else{          
     ofstream fout(argv[3]);  
     if (!fout){
      cout<<"No puedo crear el fichero "<<argv[3]<<endl;
      return 0;
     }
     ImprimeCronologia(cUnion,fout);
      
   }
}