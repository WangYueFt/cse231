#include "ConstElem.h"
class ConstProLattice {
public:
    vector<ConstElem*> elems;
    ConstProLattice join(ConstProLattice constProLattice);
};

ConstProLattice ConstProLattice::join(ConstProLattice constProLattice) {
    vector<ConstElem*> values = constProLattice.elems;
    vector<ConstElem*> result;
    typedef typename vector<ConstElem*>::iterator iterator;
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
