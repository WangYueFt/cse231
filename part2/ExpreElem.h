#include <string>
using namespace std;

class ExpreElem {
public:
    string name;
    string expression
    ConstElem(string name, string expression) {
        this->name = name;
        this->expression = expression;
    }
    bool operator == (ExpreElem& Expre) {
        if (name == Expre.name && expression == Expre.expression)
            return true;
        else
            return false;
    }
    string getName() {
        return name;
    }
    string getValue() {
        return expression;
    }
};