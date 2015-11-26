class Edge {
public:
	int num() {
		return edgeNum;
	}
	Edge() {
		static int numOfEdges = 0;
		edgeNum = numOfEdges++;
	}

private:
	int edgeNum;
};
