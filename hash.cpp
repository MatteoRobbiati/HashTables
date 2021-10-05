#include "hash.h"
#include "list.h"
#include <fstream>
#include <cmath>

using namespace std;


//~~~~~~~~~~~~~~~~~~~~~~~ costruttore e distruttore ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

HTable::HTable(int M, string collision){

  _coll = collision;
  _buckets = M;

  if(collision == "chaining"){
  _table = new DLList<int>  [_buckets];
  }

  else if(collision == "OA"){
    _vtable = new nodeVec<int> [_buckets];
    for(int i=0; i<_buckets; i++) _vtable[i]._flag="VOID";
  }
}


HTable::~HTable(){
  if(_coll=="chaining") delete [] _table;
  else if(_coll=="OA") delete [] _vtable;
};

//~~~~~~~~~~~~~~~~~~~ funzioni di hash ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~ metodi chaining ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int HTable::multiplication_hash(int key){
  double A = (sqrt(5.)-1.)/2.;
  A = _buckets*(key*A-int(key*A));

  int index;
  index = int(A);
  return index;
}

int HTable::division_hash(int key){
  return key%_buckets;

}


//~~~~~~~~~~~~~~~~~~~~ indirizzamento aperto ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


int HTable::hash_func_1(int key){
  return key%_buckets;
}


int HTable::hash_func_2(int key){
  return (1+(key%(_buckets-3)));
}


int HTable::linear_hash(int key, int iterator){
  return (hash_func_2(key)+iterator)%_buckets;
}


int HTable::quadratic_hash(int key, double c_1, double c_2, int iterator){
  int A = hash_func_2(key)+c_1*iterator+c_2*iterator*iterator;
  return abs((A)%_buckets);
}


int HTable::double_hash(int key, int iterator){
  return abs((hash_func_1(key)+iterator*hash_func_2(key))%_buckets);
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~ inserimento      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void HTable::insert(int key){

  if(_coll=="chaining"){
    int index = division_hash(key);
    _table[index].push(key);
    return;
  }


  else if(_coll=="OA"){
    int i=0;
    while(i<_buckets){
      int j = quadratic_hash(key,0.5,0.5, i);
      if(_vtable[j]._flag=="VOID" || _vtable[j]._flag=="DELETED"){
        _vtable[j]._value=key;
        _vtable[j]._flag="FULL";
        cout << "Chiave inserita dopo " << i << "tentativi \n";
        return;
      }else i++;
    }
    if(i==_buckets) cout << "Non è stato possibile inserire la chiave\n";
    cout << endl << endl;
    return;
  }

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ delete ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void HTable::remove(int key){

  if(_coll=="chaining"){
    int index = multiplication_hash(key);
    _table[index].remove(key);
    return;
  }

  if(_coll=="OA"){
    int i=0;
    while(i<_buckets){
      int j = quadratic_hash(key, 0.5, 0.5, i);
      if(_vtable[j]._flag=="VOID"){
        cout << "Elemento assente! Impossibile eliminare la chiave.\n\n";
        return;
      }
      else if(_vtable[j]._flag=="DELETED" || _vtable[j]._value!=key) i++;
      else if(_vtable[j]._value==key){
        _vtable[j]._value = -1;
        _vtable[j]._flag = "DELETED";
        cout << "Elemento eliminato!\n\n";
        return;
      }
    }
  }

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ricerca ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


void HTable::search(int key){

  //cout << "---> ### OPERAZIONE DI RICERCA DI " << key << "  ### ";

  if(_coll=="chaining"){
    int index = division_hash(key);
    _table[index].search(key);
    return;
  }

  if(_coll=="OA"){

    int i=0;
    while(i<_buckets){
      int j = quadratic_hash(key, 0.5, 0.5, i);
      if(_vtable[j]._flag=="VOID"){
        cout << "Elemento assente!\n\n";
        return;
      }
      else if(_vtable[j]._flag=="DELETED" || _vtable[j]._value!=key) i++;
      else if(_vtable[j]._value==key){
        cout << "Elemento trovato dopo " << i+1 << " accessi\n\n";
        return;
      }
    }
    cout << "Elemento non trovato\n";
  }
}



// ~~~~~~~~~~~~~ inserimento da vettore ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


void HTable::insertByVector(vector<int> v){

  double alpha = double(v.size()*1.0/_buckets*1.0);

  cout << "-------------------------------------------------------------------------\n";
  cout << "---> ### OPERAZIONE DI INSERIMENTO DA VETTORE ###\n";
  cout << "Lunghezza della tabella:                           " << _buckets << endl;
  cout << "Numero di elementi da inserire:                    " << v.size() << endl;
  cout << "Fattore di carico al termine dell'operazione:      " << alpha << endl;



  if(_coll=="chaining"){
    for(unsigned int k=0; k<v.size(); k++){
      int index = division_hash(v.at(k));
      _table[index].push(v.at(k));
    }
    cout << "\nProcesso terminato. Tutte le chiavi sono state inserite nella tabella.\n\n";
    cout << "-------------------------------------------------------------------------\n";
    return;
  }


  else if(_coll=="OA"){

    if(alpha>1.0){
      cout << "\n\nAl termine dell'operazione di inserimento il fattore di caricamento sarà superiore ad uno. \n";
      cout << "Se vuoi mantenere questo valore di alpha e non perdere nessuna informazione\n";
      cout << "imposta chaining come metodo di risoluzione delle collisioni.\n" << endl;
    }

    double probe = 0;
    int not_in=0;

    for(unsigned int k=0; k<v.size(); k++){
      int i=0;
      while(i<_buckets){
        int j = quadratic_hash(v.at(k),0.5,0.5, i);
        if(_vtable[j]._flag=="VOID" || _vtable[j]._flag=="DELETED"){
          _vtable[j]._value=v.at(k);
          _vtable[j]._flag="FULL";
          break;
        }else i++;
        probe=probe+(i+1);
      }
      if(i==_buckets) not_in+=1;
    }

    //probe = probe/(v.size()*1.-not_in*1.);
    cout << "Processo di inserimento terminato.";
    if(not_in!=0) cout << " Non sono stati inseriti " << not_in << " elementi! \n\n";
    cout << "\nIl numero medio di accessi effettuati per inserire con successo un elemento è: " << probe/(v.size()*1.0-not_in*1.0) << endl;
    cout << "Il valore teorico della stessa variabile è al più 1/(1-alpha)= " << 1./(1.-double(v.size()*1.0/_buckets*1.0)) << endl;
    cout << "\n-------------------------------------------------------------------------\n";
    return;
  }
}




// ~~~~~~~~~~~~~~~~~~~~~~~~~~ stampo tabella ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void HTable::display(){

  if(_coll=="chaining"){
    for(int i=0; i<_buckets; i++){
      cout << "bucket  " << i << "  = ";
      _table[i].display();
    }
  }else if(_coll=="OA"){
    for(int i=0; i<_buckets; i++){
      cout << "bucket  " << i << "  = ";
      cout << "(" << _vtable[i]._flag << ", " << _vtable[i]._value << ")" << endl;
    }
  }
  return;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~ lista peggiore ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void HTable::worstList(int N){

  int len_max=0, index = 0;
  for(int i=0; i<_buckets; i++){
    if(_table[i].getLen()>len_max){
      len_max = _table[i].getLen();
      index = i;
    }
  }
  cout << "La lista più lunga è la " << index << " e contiene " << len_max << " elementi.\n";
  cout << "Sotto ipotesi di hashing uniforme ci aspettiamo " << N*1./_buckets*1. << " elementi per lista.\n\n";

/*  ofstream out;
  out.open("../Results/lista.dat");
  for(int j=0; j<_table[index].getLen();j++){
    out << _table[index].get(j) << endl;
  }
  out.close();*/

  return;
}


// ~~~~~~~~~~~~~~~~~~~~~~~ ricerca da vettore ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void HTable::searchByVector(vector <int> v){

  cout << "---> ### OPERAZIONE DI RICERCA DA VETTORE  ###\n";

  if(_coll=="chaining"){
    for(unsigned int i=0; i<v.size(); i++){
      int index = multiplication_hash(v.at(i));
      _table[index].search(v.at(i));
    }
    return;
  }

  if(_coll=="OA"){
  double probe = 0;
    for(unsigned int k=0; k<v.size(); k++){
      int i=0;
      while(i<_buckets){
        int j = quadratic_hash(v.at(k),0.5,0.5, i);
        if(_vtable[j]._flag=="DELETED" || _vtable[j]._value!=v.at(k)) i++;
        else if(_vtable[j]._value==v.at(k)) break;
        }
        probe += i+1;
      }
    cout << "# medio accessi per le ricerche:" << probe*1./v.size()*1.<< endl;
  }
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~ printHist ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void HTable::getHist(){

  ofstream out;
  out.open("../Results/chai_mul.dat");
  for(int i=0; i<_buckets; i++){
    out << _table[i].getLen() << endl;
  }
  out.close();
  return;
}
