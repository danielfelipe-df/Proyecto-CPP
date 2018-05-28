#include <iostream>
#include <random>
#include <vector>
#include <cmath>
#include <stdio.h>

int selfco(std::vector<int> & s, double r, int N);

int main(void)
{
  FILE * pFile;
  //int N=32; 
  int N=2;
  std::vector<int> s(N*N);
  double r = std::sqrt(2);
 
  pFile = fopen("datos1.txt", "r");

  fprintf (pFile, "%d");

  for(int j=0; j<N; ++j){
    for(int i=0; i<N; ++i){
      fscanf(pFile, "%d", &s[(N*j)+i]);
      if(s[(N*j)+i]==0){
	s[(N*j)+i] = -1;
      }
      std::cout << s[(N*j)+i] << " ";
    }
    std::cout << std::endl;
  }

  std::cout << selfco(s,r,N) << std::endl;

  return 0;
}


int selfco(std::vector<int> & s, double r, int N)
{
  int m;
  int selfco=0;

  for(int l=0; l<N; ++l){
    for(int k=0; k<N; ++k){
  
      //derecha
      for(m=1; m<=r; ++m){
	selfco += s[(N*l)+((k+m)%N)]*s[(N*l)+k];
      } 

      //izquierda
      for(m=1; m<=r; ++m){
	selfco += s[(N*l)+((k+N-m)%N)]*s[(N*l)+k];
      }  

      //abajo
      for(m=1; m<=r; ++m){
	selfco += s[(N*((l+m)%N))+k]*s[(N*l)+k];
      } 

      //arriba
      for(m=1; m<=r; ++m){
	selfco += s[(N*((l+N-m)%N))+k]*s[(N*l)+k];
      } 
    }
  }

  return selfco;
}




/*
int main()
{
  int seed = 3, N=100;
  std::mt19937 gen(seed);
  std::uniform_int_distribution<> dis(0,1);
  std::vector<int> y(N);
  
  for(int i=0; i < N/4; i++){
    for (int n = 0; n < N/25; ++n) {
      y[n] = dis(gen); 
      //std::cout << y[n] << '\n';
      if(y[n] == 0)
	{
	  y[n] = -1;
	}
      std::cout << y[n] << '\t';
    }
    std::cout << std::endl;
  }

  return 0;
}
*/
