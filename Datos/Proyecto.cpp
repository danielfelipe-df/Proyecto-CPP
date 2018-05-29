#include <iostream>
#include <random>
#include <vector>
#include <cmath>
#include <stdio.h>
#include <fstream>

double selfco(std::vector<int> & s, int i, int j, int N);//Autocorrelación no normalizada en donde se mira todos los espines adentro del radio
double selfco1(std::vector<int> & s, int i, int j, int N);//Autocorrelación no normalizada en donde se mira únicamente el espín más lejano dentro del radio
void print(std::vector<int> & s, int N);// función para imprimir
void radios(std::vector<int> & s,int N, std::string name);//para imprimir la correlación dependiente del radio de una temperatura dada

int main(void)
{
  FILE * pFile;
  int N=31; 
  // int N=2;
   std::vector<int> s(N*N);
  
  pFile = fopen("ising2d-3.txt", "r");
  fprintf (pFile, "%d");
  //para generar la matriz de forma correcta 
  for(int l=0; l<N; ++l){
    for(int k=0; k<N; ++k){
      fscanf(pFile, "%d", &s[(N*l)+k]);
      if(s[(N*l)+k]==0){
	s[(N*l)+k] = -1;
      }
    }
  }

  // print(s,N);
  radios(s,N, "radios-3.txt");

  return 0;
}


void print(std::vector<int> & s, int N)
{
  for(int j=0; j<N; ++j){
    for(int i=0; i<N; ++i){
      std::cout << s[(N*j)+i] << " ";
    }
    std::cout << std::endl;
  }
}


double selfco1(std::vector<int> & s, int i, int j, int N)
{
  int selfco1=0;
  for(int l=0; l<N; ++l){
    for(int k=0; k<N; ++k){ 
      //derecha
      selfco1 += s[(N*l)+((k+i)%N)]*s[(N*l)+k];
      //izquierda
      selfco1 += s[(N*l)+((k+N-i)%N)]*s[(N*l)+k];
      //abajo
      selfco1 += s[(N*((l+j)%N))+k]*s[(N*l)+k];
      //arriba
      selfco1 += s[(N*((l+N-j)%N))+k]*s[(N*l)+k];
    }
  }
  return selfco1;
}


double selfco(std::vector<int> & s, int i, int j, int N)
{
  int m;
  int selfco=0;
  for(int l=0; l<N; ++l){
    for(int k=0; k<N; ++k){
      //derecha
      for(m=1; m<=i; ++m){
	selfco += s[(N*l)+((k+m)%N)]*s[(N*l)+k];
	}
      //izquierda
      for(m=1; m<=i; ++m){
	selfco += s[(N*l)+((k+N-m)%N)]*s[(N*l)+k];
      }
      selfco += s[(N*l)+((k+N-i)%N)]*s[(N*l)+k];
      //abajo
      for(m=1; m<=j; ++m){
	selfco += s[(N*((l+m)%N))+k]*s[(N*l)+k];
      } 
      //arriba
      for(m=1; m<=j; ++m){
	selfco += s[(N*((l+N-m)%N))+k]*s[(N*l)+k];
      } 
    }
  }

  return selfco;
}


void radios(std::vector<int> & s,int N, std::string name){

  std::ofstream fout(name);

  for(int i=0, j=0; i<N, j<N; ++i, ++j){
    //for(int j=0; j<N; ++j){
      double r=std::sqrt((i*i)+(j*j));
      double selfcon = selfco(s,i,j,N)/(N*N);//Autocorrelación normalizada
      double selfcon1 = selfco1(s,i,j,N)/(N*N);//Autocorrelación normalizada
    /*
    std::cout << selfco(s,i,j,N) << "\t" << N*N << selfco1(s,i,j,N) << std::endl;
    std::cout << "i = " << i << "\t" << "j = " << j << "\t" << "r = " << r << std::endl;
    std::cout << "Autocorrelación promedio= " << selfcon << "\t";
    std::cout << "Autocorrelación promedio 1= " << selfcon1 << std::endl;
    std::cout << std::endl;
    */
      fout << r << "\t" << selfcon << "\t" << selfcon1 << std::endl;
      // }
  }
  fout.close();
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
