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
		in = vector<Edge>();
		out = vector<Node>();
	}
	addInEdge(Edge e){
		in.push_back(e);
	}
	addOutEdge(Edge e){
		out.push_back(e);
	}

};






