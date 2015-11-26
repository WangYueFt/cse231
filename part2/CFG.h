#include "Edge.h"
#include "Node.h"
#include <iostream>

using namespace std;

class CFG{
public:
	CFG(vector<Edge> edges, vector<Node> nodes){
		this->edges = edges;
		this->nodes = nodes;
	}
	print(){
		cout << "CFG begin:" << endl;
		for(int i=0; i<nodes.size(); i++){
			cout << "NodeId:" << nodes[i].num() << endl;
			vector<Edge> edges;
			edges = nodes[i].getInedges();
			cout << "IN:"
			for(int j=0; j<edges.size(); j++)
				cout << edges[j].num() << " ";
			cout << endl;
			edges = nodes[i].getOutedges();
			cout << "OUT:"
			for(int j=0; j<edges.size(); j++)
				cout << edges[j].num() << " ";
			cout << endl;
		}
		cout << "CFG end" << endl;
	}
private:
	vector<Edge> edges;
	vector<Node> nodes;
};

