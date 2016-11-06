#include <iostream>
#include <cola.h>

using namespace std;

int main(){
	
  Cola <int> p;
  int i;

  for ( i=0; i<10 ; i++) 
    p.poner(i);
   
  int x = p.frente();
  cout << x << endl;
     
  p.quitar();

  int y = p.frente();
  cout << y << endl;
 
  cout << p.num_elementos() << endl;
  
  
  Cola <float> q;
  int j;
  
  
  for ( j=0; j<10 ; j++) 
    q.poner(j/10.0);
   
  float z = q.frente();
  cout << z << endl;
     
  q.quitar();

  float w = q.frente();
  cout << w << endl;
  
  cout << q.num_elementos() << endl;

  return 0;
}
