#ifndef _hash_h_
#define _hash_h_

#include <bits/stdc++.h>
#include <list>
#include "list.h"
#include <vector>

using namespace std;

class HTable{

  private:
    int _buckets;
    DLList<int>* _table;
    nodeVec<int>* _vtable;
    string _coll;

  public:
    HTable(int M, string collision);
    ~HTable();

    // void del(int key);

    void display();
    void insert(int key);
    void remove(int key);
    void search(int key);

    int multiplication_hash(int key);
    int division_hash(int key);

    int linear_hash(int key, int iterator);
    int quadratic_hash(int key,double c_1, double c_2, int iterator);
    int double_hash(int key, int iterator);

    int hash_func_1(int key);
    int hash_func_2(int key);

    void worstList(int N);
    void insertByVector(vector<int> v);
    void searchByVector(vector<int> v);
    void getHist();


};


#endif
