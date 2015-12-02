#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Intrinsics.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/GlobalVariable.h"
#include <map>
#include <string>
#include <iostream>
#include <vector>
// #include "LatticeElement.h"
#include "ConstElem.h"
#include "ConstProLattice.h"

using namespace llvm;
using namespace std;

class Edge {
public:
	int num() const{
		return edgeNum;
	}
	Edge() {
		static int numOfEdges = 0;
		edgeNum = numOfEdges++;
	}

private:
	int edgeNum;
};


class Node{
private:
	
	vector<Edge> in,out;
	int nodeId;

public:
	Instruction *inst;
	Node(Instruction *i, int id){
		// static int count=0;
		nodeId = id;
		inst = i;
		in = vector<Edge>();
		out = vector<Edge>();
	}
	void addInEdge(Edge e){
		in.push_back(e);
	}
	void addOutEdge(Edge e){
		out.push_back(e);
	}
	int num() const{
		return nodeId;
	}
	vector<Edge>  getInEdges() const{
		return in;
	}
	vector<Edge> getOutEdges() const{
		return out;
	}
	ConstProLattice<ConstElem> CPFlowOp(ConstProLattice<ConstElem> in) {

		vector<ConstElem*> info_in = in.elems;

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
		if (yOperator != 0) {
			const string yConstName = yOperator->getName().data();
			yName = yConstName;
		} else {
			yIntValue = yConst->getValue().getLimitedValue();
		}
		string zName;
		int zIntValue;
		bool isZ = false;
		if (zOperator != 0) {
			const string zConstName = zOperator->getName().data();
			zName = zConstName;
		} else {
			zIntValue = zConst->getValue().getLimitedValue();
		}

		
		vector<ConstElem*> info_out;
		for (size_t i = 0; i < info_in.size(); i++) {
			if (info_in[i]->getName() != xName) {
				info_out.push_back(info_in[i]);
			}
			if (info_in[i]->getName() != yName) {
				yIntValue = info_in[i]->getValue();
		 		isY = true;
			}
			if (info_in[i]->getName() != zName) {
				zIntValue = info_in[i]->getValue();
		 		isZ = true;
			}
		}
		if (isY && isZ) {
			string op = inst->getOpcodeName();
			if (op == "add") {
				ConstElem* toAdd = new ConstElem(xName, yIntValue+zIntValue);
				info_out.push_back(toAdd);
			} else if (op == "mul") {
				ConstElem* toAdd = new ConstElem(xName, yIntValue-zIntValue);
				info_out.push_back(toAdd);
			} else if (op == "sub") {
				ConstElem* toAdd = new ConstElem(xName, yIntValue*zIntValue);
				info_out.push_back(toAdd);
			} else if (op == "div") {
				ConstElem* toAdd = new ConstElem(xName, yIntValue/zIntValue);
				info_out.push_back(toAdd);
			}
		}	
		in.elems = info_out;
		return in;
	}
};


