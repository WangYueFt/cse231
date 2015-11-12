#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "llvm/IR/Instructions.h"
using namespace std;
using namespace llvm;
map<string, int> globalCounter;

void merge(int opcode) {
	//for (vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
		map<string, int>::iterator entry = globalCounter.find(Instruction::getOpcodeName(opcode));
     	if (entry == globalCounter.end()) {
        	globalCounter.insert(pair<string, int>(Instruction::getOpcodeName(opcode), 1));
    	 } else {
       		entry->second += 1;
     	}
	//}
     
}

void print() {
	int total = 0;
	for(map<string,int>::const_iterator it = globalCounter.begin(); it != globalCounter.end(); ++it) {
		cout << it->first << ":" << it->second << "\n";
		total += it->second;
	}
	cout << "Total" << ":" << total << "\n";
}

