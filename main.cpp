
#include "hash.h"
#include "list.h"
#include "func.h"
#include <vector>
#include <string>
#include <cmath>
#include <chrono>

using namespace std;
using namespace std::chrono;


int main(){

  vector<int> v = loadData("../Results/uniform.dat");
  vector<int> u = loadData("../Results/not_in.dat");
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ nel caso si voglia fare un test sul metodo OA ~~~~~~~~~~~~~~~~~~~~~~~~~~

//  vector<string> w = loadTxt("../Results/strings.txt");
//  vector<int> u;
  /*for(int i=10000; i>0; i--){
    u.push_back(v.at(i));
  }*/

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ valido in generale "chaining"/"OA" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  int N = v.size();
  int prime = findPrime(1000);
  cout << "Primo trovato: " << prime << endl;


  HTable tab(prime, "chaining");

  tab.insertByVector(v);
  //tab.display();



  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ test temporali ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    double tempo = 0.;

    for(unsigned int i=0; i<v.size(); i++){
      auto start = high_resolution_clock::now();
      tab.search(v.at(i));
      auto stop = high_resolution_clock::now();
      auto duration = duration_cast<microseconds>(stop - start);
      tempo+=duration.count();
      if(i%500000==0) cout << "Loop " << i << endl;
      //cout << "Tempo per ricerca di " << v.at(303) << " : " << duration.count() << " microsecondi" << endl;
    }

    cout << "Tempo medio per trovare un elemento se la tabella ne contiene 2e7: " << tempo/(v.size()*1.) << endl;

 // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ricerca di elementi di un vettore  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  /*
  cout << endl << "Ricerca di 10000 elementi non presenti in tabella\n";
  tab.searchByVector(w);
  cout << endl;

  cout << "Load Factor:                                        " << 0.99997 << endl;
  cout << "limite massimo # accessi medio teorico per ricerca senza successo: " << 33334.3 << endl;
  cout << "limite massimo # accessi medio teorico per ricerca con successo:   " << (1/0.99997)*log(1./(1.-0.99997)) << endl;*/

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ lunghezze delle liste ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


  tab.worstList(N);
  //tab.getHist();

  return 0;
}
