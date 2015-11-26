#include <iostream>
#include <vector>
using namespace std;

template <class T>
class LatticeElement {
public:
    vector<T*> elems;
    //virtual vector<T> join(vector<LatticeElement> values){};
};

