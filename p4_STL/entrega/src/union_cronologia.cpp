#include "cronologia.hpp"
#include <fstream>
#include <iostream>

using namespace std;

Cronologia & Union(const Cronologia & c1, const Cronologia & c2){
  //completar implementacion
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
    cout << cUnion;
   else{
     ofstream fout(argv[3]);
     if (!fout){
      cout<<"No puedo crear el fichero "<<argv[3]<<endl;
      return 0;
     }
     fout << cUnion;

   }
}
