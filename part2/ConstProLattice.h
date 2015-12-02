#include "LatticeElement.h"
template <class T>
class ConstProLattice:public LatticeElement<T> {
public:
    ConstProLattice<T> join(ConstProLattice<T> constProLattice);
};

template <class T>
ConstProLattice<T> ConstProLattice<T>::join(ConstProLattice<T> constProLattice) {
    vector<T*> values = constProLattice.elems;
    vector<T*> result;
    typedef typename vector<T*>::iterator iterator;
    for (iterator v = values.begin(); v != values.end(); ++v) {
        for (iterator e = this->elems.begin(); e != this->elems.end(); ++e) {
            if (**v == **e) {
                result.push_back(*v);
            }
        }
    }
    ConstProLattice constProLatticeResult = ConstProLattice();
    constProLatticeResult.elems = result;
    return constProLatticeResult;
}
