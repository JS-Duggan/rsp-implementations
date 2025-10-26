#include <iostream>
#include <vector>

struct Edge {
	int y;
	int weight;

	Edge(int y, int w): y(y), weight(w){};
};

class Graph {
private:
	int nvertices;
	int nedges;
	bool directed;
	std::vector<std::vector<int>> edges;
	std::vector<int> outDegree;
public:
	Graph(int n, int v, bool d): nvertices(n), nedges(v), directed(d){};
	void readGraph();
	void insertEdge(int x, int y);
	void printGraph();
};