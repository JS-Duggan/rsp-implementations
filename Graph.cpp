#include <iostream>
#include <vector>
#include <stdexcept>

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
	std::vector<std::vector<Edge>> edges;
	std::vector<int> outDegree;
public:
	Graph(int n, int v, bool d);
	void readGraph();
	void insertEdge(int x, int y, int w);
	void printGraph();
};

void Graph::readGraph() {
	int x, y, w;
	for (int i = 0; i < nedges; i++) {
		std::cin >> x >> y;
		insertEdge(x, y, w);
	}
}

void Graph::insertEdge(int x, int y, int w) {
	if (x >= 0 && x < nvertices && y >= 0 && y < nvertices) {
		edges[x].push_back(Edge(y, w));
		if (directed) edges[y].push_back(Edge(x, w));
	} else {
		throw std::out_of_range("Index of vertex out of range");
	}
}

void Graph::printGraph() {
	for (int i = 0; i < nvertices; i++) {
		if(edges[i].size() > 0) {
			std::cout << i << ":";
			for (int j = 0; j < edges[i].size(); j++) {
				std::cout << "	" << edges[i][j].y << edges[i][j].weight << std::endl;
			}
		}
	}
}