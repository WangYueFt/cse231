#include <string>
using namespace std;

class ConstElem {
public:
    string name;
    int value;
    ConstElem(string name, int value) {
        this->name = name;
        this->value = value;
    }
    bool operator == (ConstElem& Const) {
        if (name == Const.name && value == Const.value)
            return true;
        else
            return false;
    }
    string getName() {
        return name;
    }
    int getValue() {
        return value;
    }
};
