#include <string>
using namespace std;

class PointerElem {
public:
    string name;
    vector<string> toName;
    PointerElem(string name, vector<range> value) {
        this->name = name;
        this->toName = value;
    }

    bool operator == (PointerElem& Pointer) {
        if (name == Pointer.name)
            return true;
        else
            return false;
    }

    PointerElem operator + (PointerElem& Pointer) {
        if (name == Pointer.name) {
            string resultName = name;
            vector<range> resulttoName;
            for (iterator v = toName.start(); v != toName.end(); ++v) {
                resulttoName.push_back(*v);
            }
            for (iterator e = Pointer.toName.start(); e != Pointer.toName.end(); ++e) {
                resulttoName.push_back(*e);
            }
            PointerElem result = new PointerElem(name, resulttoName);
            return result;
        }
    }
};