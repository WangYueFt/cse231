#include <vector>
#include "Edge.h"
#include "llvm/IR/Instruction.h"

using namespace llvm;
using namespace std;

class Node{
private:
	Instruction inst;
	vector<Edge> in,out;
	int nodeId;

public:
	Node(Instruction i){
		static int count=0;
		nodeId = count++;
		inst = i;
	}
	vector<LatticeElement*> CPFlow(vector<LatticeElement*> info_in) {

	}
	/** Assignment  X = Y **/
	vector<LatticeElement*> CPFlowAss(vector<LatticeElement*> info_in) {
		string xName = inst.X;
		string yName = inst.Y;
		// vector<vector<LatticeElement*>::iterator> postions;
		// for (vector<LatticeElement*>::iterator it = info_in->begin(); it != info_in->end(); ++it) {
		// 	if (it->name() == xName) {
		// 		postions.push_back(it);
		// 	}		
		// }
		// for (int i = 0; i < postions.size(); i++) {
		// 	info_in.erase(postions[i]);
		// }
		// vector<LatticeElement*> newInfos;
		// for (vector<LatticeElement*>::iterator it = info_in->begin(); it != info_in->end(); ++it) {
		// 	if (it->name() == yName) {
		// 		LatticeElement* toAdd = new ConstElem(yName, it->value());
		// 		newInfos.push_back(toAdd);
		// 	}		
		// }
		// for (int i = 0; i < newInfos.size(); i++) {
		// 	info_in
		// }
		vector<LatticeElement*> info_out;
		for (vector<LatticeElement*>::iterator it = info_in->begin(); it != info_in->end(); ++it) {
			if (it->name() != xName) {
				info_out.push_back(*it);
			}	
			if (it->name() == yName) {
				LatticeElement* toAdd = new ConstElem(yName, it->value());
				info_out.push_back(toAdd);
			}	
		}
		return info_out;
	}
	vector<LatticeElement*> CPFlowAdd(vector<LatticeElement*> info_in) {
		string xName = inst.X;
		string yName = inst.Y;
		string zName = inst.Z;
		vector<LatticeElement*> info_out;
		for (vector<LatticeElement*>::iterator it = info_in->begin(); it != info_in->end(); ++it) {
			if (it->name() != xName) {
				info_out.push_back(*it);
			}	
			if (it->name() == yName) {
				LatticeElement* toAdd = new ConstElem(yName, it->value());
				info_out.push_back(toAdd);
			}	
		}
		return info_out;
	}
};






