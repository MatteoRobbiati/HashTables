#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

vector<int> loadData(const char* nomefile);
vector <string> loadTxt(const char* nomefile);
int findPrime(int N);
bool isPrime(int N);
