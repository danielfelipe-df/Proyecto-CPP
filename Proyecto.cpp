#include <iostream>
#include <random>
#include <vector>
#include <cmath>
#include <stdio.h>

int suma(std::vector<int> & y, int i);

int main ()
{
  FILE * pFile;
  int N=32;
  std::vector<int> s(N*N);
 
  pFile = fopen("ising2d-5.txt", "r");

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


  return 0;
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
