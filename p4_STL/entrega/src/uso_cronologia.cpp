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
   
   EventoHistorico eventos;
   eventos = mi_cronologia.GetEventos(anio);  //Asumimos que Cronologia::GetEventos() devuelve objeto de clase EventoHistorico
   

   // Recorremos con iterador los acontecimientos para mostrarlos por pantalla 
   // Este proceso requiere la definición de un tipo iterator // const_iterator en EventoHistorico
   // Y la definición de los métodos begin() y end() en EventoHistorico
   EventoHistorico::const_iterator it;
   cout << anio << ":";              //Imprimimos el anio
   for (it=eventos.begin(); it!=eventos.end();++it){
     cout<<(*it)<<'#';
   cout<<endl;





}
