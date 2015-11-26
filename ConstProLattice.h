#include "LatticeElement.h"
template <class T>
class ConstProLattice:public LatticeElement<T> {
public:
    //vector<T> join(vector<T> values);
};

// template <class T>
// vector<T> ConstProLattice<T>::join(vector<T> values) {
//     vector<T> result;
//     typedef typename vector<T>::iterator iterator;
//     for (iterator v = values.begin(); v != values.end(); ++v) {
//         for (iterator e = this->elems.begin(); e != this->elems.end(); ++e) {
//             if (*v == *e) {
//                 result.push_back(*v);
//             }
//         }
//     }
//     return result;
// }
