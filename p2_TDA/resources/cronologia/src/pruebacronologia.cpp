#include "cronologia.h"
#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char * argv[]){

  if (argc!=2){
      cout<<"Dime el nombre del fichero con la cronologia"<<endl;
      return 0;
   }

   ifstream f (argv[1]);
   if (!f){
    cout<<"No puedo abrir el fichero "<<argv[1]<<endl;
    return 0;
   }
   
   Cronologia mi_cronologia;
   f>>mi_cronologia; //Cargamos en memoria, en el traductor.
   
   int anio;
   cout<<"Dime un año a consultar:";
   cin >> anio;
   
   vector<string> eventos = mi_cronologia.GetEventos(anio);
   
   /* Escribimos */
   cout << anio << ":";
   for (int i=0;i<eventos.size(); ++i)
     cout<<eventos[i]<<';';
   cout<<endl;

}
