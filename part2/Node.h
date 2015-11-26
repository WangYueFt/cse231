#include <vector>
#include "llvm/IR/Instruction.h"

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

};








