#include <map>
#include <vector>
#include "ConstProLattice.h"
using namespace std;

class WorkList {
public:
	WorkList(vector<Node> nodes, vector<Edge> edges) {
		for (vector<Edge>::iterator it = edges.begin(); it != edges.end(); ++it) {
			m[it->num()] = ConstProLattice<ConstElem>();
		}
		for (vector<Node>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
			worklist.push_back(*it);
		}
	}
	void doWorkList() {
		while (!worklist.empty()) {
			Node n = worklist.back();
			worklist.pop_back();
			// vector<LatticeElement*> info_in;
			// for (vector<LatticeElement*>::iterator it = n->incoming_edges->begin(); it != n->incoming_edges->end(); ++it) {
			// 	info_in.push_back(*it)
			// }
			vector<ConstProLattice<ConstElem>> info_in;
			vector<Edge> in_edges = n.getInEdges();
			for (int i = 0; i < in_edges.size(); i++) {
				Edge e = in_edges[i];
				info_in.push_back(m[e.num()]);
			}
			ConstProLattice<ConstElem> in_constProLattice = info_in[0];
			for (int i = 1; i < in_edges.size(); i++) {
				Edge e = in_edges[i];
				in_constProLattice = in_constProLattice.join(m[e.num()]);
			}

			ConstProLattice<ConstElem> out_constProLattice = n.CPFlowOp(in_constProLattice);

			vector<Edge> out_edges = n.getOutEdges();
			for (int i = 0; i < out_edges.size(); i++) {
				Edge e = out_edges[i];
				ConstProLattice<ConstElem> new_info = out_constProLattice.join(m[e.num()]);
				if (new_info != m[e.num()]) {
					m[e.num()] = new_info;
					worklist.push_back(e.dst());
				}				
			}
		}
	}
private:
	vector<Node> worklist;
	map<int, ConstProLattice<ConstElem>> m; 
};