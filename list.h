

#ifndef __type_h__
#define __type_h__

#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>

using namespace std;

template <class T> struct nodeVec{
  T _value;
  string _flag;
};

template <class T> struct node {
    T _value;
    node<T>* _left;
    node<T>* _right;
    node(T key): _value(key), _right(nullptr){}
};

/////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////    DOUBLY LINKED LIST       //////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

template <class T> class DLList{
  private:
    node<T>* _head;
    node<T>* _tail;
    unsigned int _len;

  public:
    DLList();
    ~DLList();

    void search( T key);
    void push(T key);
    void remove(T key);
    T get(int index);
    bool is_empty();
    int countNodes();
    void display();
    int getLen();
};


//~~~~~~~~~~~~~~~~~~~~~~~~~~~ implemento DLList ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~ costruttore e distruttore ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

template <class T> DLList<T>::DLList(){
  _len = 0;
  _head = _tail = nullptr;
}


template <class T> DLList<T>::~DLList(){
  node<T>* appo = _head;
  while(appo!=nullptr){
      appo = _head->_right;
      delete _head;
      _head = appo;
  }
  delete _head;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~ conto nodi o check lista vuota ~~~~~~~~~~~~~~~~~~~~~~

template <class T> int DLList<T>::countNodes(){
  return _len;
}

template <class T> bool DLList<T>::is_empty(){
  if(_len<=0) return true;
  else return false;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ inserisci chiave ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

template <class T> void DLList<T>::push(T data){
  _len++;
  node<T>* N  = new node<T>(data);                                              // creo un nodo N svincolato contenente la chiave
                                                                                // puntatori a vuoto a destra e sinistra di N
  if(_head==nullptr){                                                           // se la testa è vuota N = testa = coda
    _head = N;
    _tail = N;
  }else{
    _head->_left = N;                                                           // puntatore sx di testa punta alla chiave in N
    N->_right = _head;                                                          // puntatore dx di N punta alla chiave di testa
    _head = N;                                                                  // aggiorno la testa
  }
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ricerca chiave ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

template <class T> void DLList<T>::search(T data){
  if(!is_empty()){                                                              // se la lista non è vuota
                                                                                // creo nodo temporaneo e lo pongo = alla testa
    node<T>* temp = _head;
    while(temp!=nullptr){                                                       // finché non arrivo alla fine
      if(temp->_value == data){                                                 // se il valore a cui punta temp è quel che cerco break
        //cout << "Trovato!\n";
        break;
      } else temp = temp->_right;                                               // salto al prossimo nodo
    }
    if(temp==nullptr) cout << "Elemento non trovato!" << endl;                  // se arrivo alla fine e non lo trovo, è assente
  }else{
    cout << "La lista è vuota!\n";
  }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ rimuovi chiave ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

template <class T> void DLList<T>::remove(T data){

  if(!is_empty()){
    node<T>* temp = _head;
    while(temp!=nullptr){
      if(temp->_value == data){
        temp->_right->_left = temp->_left;
        temp->_left->_right = temp->_right;
        delete temp;
        _len --;
        return;
      }else temp = temp->_right;
    }
    if(temp==nullptr) cout << "Elemento non trovato!" << endl;
  }else{
    cout << "La lista è vuota!\n";
  }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ stampa lista ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

template <class T> void DLList<T>::display(){
  node<T>* temp = _head;

  if(is_empty()){
    cout << "Questa lista è vuota\n";
    return;
  }

  while(temp->_right != nullptr){
    cout << temp->_value << " <--> ";
    temp = temp->_right;
  }
  cout << temp->_value << endl;
};


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ get len ~~~~~~~~~~~~~~~~~~~~~~~

template <class T> int DLList<T>::getLen(){
  return _len;
}

template <class T> T DLList<T>::get(int index){
  node<T>* temp = _head;
  int i = 0;
  while(i!=index){
    if(temp->_right == nullptr) break;
    else{
      temp = temp->_right;
    }
  }
  return temp->_value;
}

#endif
