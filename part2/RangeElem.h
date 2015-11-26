#include <string>
using namespace std;

class range {
public:
    int start;
    int end;
    range(int start, int end) {
        this->start = start;
        this->end = end;
    }
};

class RangeElem {
public:
    string name;
    vector<range> Range;
    RangeElem(string name, vector<range> value) {
        this->name = name;
        this->Range = value;
    }

    bool operator == (RangeElem& Ranges) {
        if (name == Ranges.name)
            return true;
        else
            return false;
    }

    RangeElem operator + (RangeElem& Ranges) {
        if (name == Ranges.name) {
            string resultName = name;
            vector<range> resultRange;
            for (iterator v = Range.start(); v != Range.end(); ++v) {
                resultRange.push_back(*v);
            }
            for (iterator e = Ranges.Range.start(); e != Ranges.Range.end(); ++e) {
                resultRange.push_back(*e);
            }
            RangeElem result = new RangeElem(name, resultRange);
            return result;
        }
    }

    string getName() {
        return name;
    }
    vector<range> getValue() {
        return Range;
    }
};