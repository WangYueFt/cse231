#include "Edge.h"
#include "Node.h"


class CFG{
public:
	CFG(vector<Edge> edges, vector<Node> nodes){
		this->edges = edges;
		this->nodes = nodes;
	}
private:
	vector<Edge> edges;
	vector<Node> nodes;
}