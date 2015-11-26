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

	
	// vector<LatticeElement*> CPFlow(vector<LatticeElement*> info_in) {

	// }
	// /** Constant Assignment X = a **/
	// vector<LatticeElement*> CPFlowConstAss(vector<LatticeElement*> info_in) {
	// 	string xName = inst.X;
	// 	//string yName = inst.Y;
	// 	vector<LatticeElement*> info_out;
	// 	for (vector<LatticeElement*>::iterator it = info_in->begin(); it != info_in->end(); ++it) {
	// 		if (it->name() != xName) {
	// 			info_out.push_back(*it);
	// 		}	
	// 	}
	// 	LatticeElement* toAdd = new ConstElem(xName, inst->value());
	// 	info_out.push_back(toAdd);
	// 	return info_out;
	// }
	/** Assignment  X = Y **/
	// vector<LatticeElement*> CPFlowAss(vector<LatticeElement*> info_in) {
	// 	string xName = inst.X;
	// 	string yName = inst.Y;
	// 	vector<LatticeElement*> info_out;
	// 	for (vector<LatticeElement*>::iterator it = info_in->begin(); it != info_in->end(); ++it) {
	// 		if (it->name() != xName) {
	// 			info_out.push_back(*it);
	// 		}	
	// 		if (it->name() == yName) {
	// 			LatticeElement* toAdd = new ConstElem(xName, it->value());
	// 			info_out.push_back(toAdd);
	// 		}	
	// 	}
	// 	return info_out;
	// }
	/** Operation X = Y op Z **/
	vector<LatticeElement*> CPFlowOp(vector<LatticeElement*> info_in) {
		const string xName = inst->getName().data();

		Value* yValue = inst->getOperand(0);
		Value* zValue = inst->getOperand(1);

		ConstantInt* yConst = dyn_cast<ConstantInt>(yValue);
		BinaryOperator* yOperator = dyn_cast<BinaryOperator>(yValue);

		ConstantInt* zConst = dyn_cast<ConstantInt>(zValue);
		BinaryOperator* zOperator = dyn_cast<BinaryOperator>(zValue);

		string yName;
		int yIntValue;
		bool isY = false;
		if (yOperator != null) {
			const string yConstName = yOperator->getName().data();
			yName = yConstName;
		} else {
			yIntValue = yConst->getValue().getLimitedValue();
		}
		string zName;
		int zIntValue;
		bool isZ = false;
		if (zOperator != null) {
			const string zConstName = zOperator->getName().data();
			zName = zConstName;
		} else {
			zIntValue = zConst->getValue().getLimitedValue();
		}

		
		vector<LatticeElement*> info_out;
				for (vector<LatticeElement*>::iterator it = info_in->begin(); it != info_in->end(); ++it) {
			if (it->name() != xName) {
				info_out.push_back(*it);
			}	
			if (it->name() == yName) {
				yIntValue = it->value();
				isY = true;
			}
			if (it->name() == zName) {
				zIntValue = it->value();
				isZ = true;
			}	
		}
		if (isY && isZ) {
			if (inst->getOpcodeName() == "add") {
				LatticeElement* toAdd = new ConstElem(xName, yValue+zValue);
				info_out.add(toAdd);
			} else if (inst->getOpcodeName() == "mul") {
				LatticeElement* toAdd = new ConstElem(xName, yValue*zValue);
				info_out.add(toAdd);
			} else if (inst->getOpcodeName() == "sub") {
				LatticeElement* toAdd = new ConstElem(xName, yValue-zValue);
				info_out.add(toAdd);
			} else if (inst->getOpcodeName() == "div") {
				LatticeElement* toAdd = new ConstElem(xName, yValue/zValue);
				info_out.add(toAdd);
			}
		}	
		return info_out;
	}

	// vector<LatticeElement*> CPFlowAss(vector<LatticeElement*> info_in) {
		
	// }
};






