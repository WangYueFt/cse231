#include <iostream>
#include <map>
#include <set>

using namespace std;

map<string, int> funcMap;
map<string, int> takenMap;
set<string> funcNameSet;

void print(){ 
	cout << "Function\t" << "Bias\t" << "Taken\t" << "Total\n";
	for(set<string>::iterator iter = funcNameSet.begin(); iter != funcNameSet.end(); iter++ ){
		
		int numTaken = 0;
		int numTotal = 0;
		map<string, int>::iterator ifunc = funcMap.find(*iter);
		if (ifunc != funcMap.end()) {
			numTotal =  ifunc->second;
		} 
		map<string, int>::iterator itaken = takenMap.find(*iter);
		if (itaken != takenMap.end()) {
			numTaken = itaken->second;
		} 
		float bias = numTotal==0?0.0:1.0*numTaken/numTotal;
		cout << *iter << "\t" << bias << "\t" << numTaken << "\t" << numTotal << "\n";
	}
}

void funcName(char* funcName) {
	
	funcNameSet.insert(funcName);
}

void branch(char* funcName, bool isTrue){

	map<string, int>::iterator it = funcMap.find(funcName);
	if (it == funcMap.end()){
		funcMap.insert(pair<string, int>(funcName, 1));
	} else {
		it->second++;
	}

	if (isTrue) {
		it = takenMap.find(funcName);
		if (it == takenMap.end()){
			takenMap.insert(pair<string, int>(funcName, 1));
		} else {
			it->second++;
		}
	}

}
