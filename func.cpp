#include "func.h"

using namespace std;


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ loadData in vettore ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


vector <int> loadData(const char* nomefile){

  vector <int> v;
  ifstream in;
  in.open(nomefile);

  if(!in.is_open()) cerr << "Il file non è stato aperto correttamente!" << endl;

  while(!in.eof()){
    double temp = 0.0;
    in >> temp;
    v.push_back(temp);
  }

  v.pop_back();
  in.close();

  return v;
}


vector <string> loadTxt(const char* nomefile){
  vector <string> v;
  ifstream in;
  in.open(nomefile);

  if(!in.is_open()) cerr << "Il file non è stato aperto correttamente!" << endl;

  while(!in.eof()){
    string temp;
    in >> temp;
    v.push_back(temp);
  }

  v.pop_back();
  in.close();

  return v;
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ primo primo maggiore di N ~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int findPrime(int N){
  int prime = N+1;
  while(isPrime(prime)==false) prime+=1;
  return prime;
}



bool isPrime(int N){
  int flag = 0;
  for(int i=2; i<N; i++){
    if(N%i==0) flag=1;
  }
  if(flag==1) return false;
  if(flag==0) return true;
}
