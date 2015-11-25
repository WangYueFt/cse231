#include <map>
#include <vector>
using namespace std;



class WorkList {
public:
	WorkList(vector<Node*> nodes, vector<Edge> edges) {
		for (vector<Edge>::iterator it = edges.begin(); it != edges.end(); ++it) {
			m[it->num()] = new LatticeElement;
		}
		for (vector<Node*>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
			worklist.push_back(*it);
		}
	}
	void doWorkList() {
		while (!worklist.empty()) {
			Node* n = worklist.back();
			worklist.pop_back();
			vector<LatticeElement*> info_in;
			for (vector<LatticeElement*>::iterator it = n->incoming_edges->begin(); it != n->incoming_edges->end(); ++it) {
				info_in.push_back(*it)
			}
			vector<LatticeElement*>::iterator info_out = n->F(info_in);
			for (int i = 0; i < info_out.size(); i++) {
				LatticeElement* new_info = info_out[i]->join(m[n->outgoing_edges[i]]);
				if !((*m[n->outgoing_edges[i]->num()] == *new_info)) {
					m[n->outgoing_edges[i]->num()] = new_info;
					worklist.push_back(n->outgoing_edges[i]->dst);
				}
			}
		}
	}
private:
	vector<Node*> worklist;
	map<int, LatticeElement*> m; 
};