#include "ConstProLattice.h"

class A {
public:
    int a;
    A(){
        a = 0;
    }
};

class B:public A{
public:
    void print() {
        cout << a << endl;
    }
};
int main(void) {
    ConstProLattice<int> c;
    c.elems.push_back(1);
    c.elems.push_back(2);
    c.elems.push_back(3);
    ConstProLattice<int> v;
    v.elems.push_back(2);
    v.elems.push_back(3);
    vector<int> result = c.join(v.elems);
    for (vector<int>::iterator i = result.begin(); i != result.end(); ++i)
        cout << *i << endl;
}