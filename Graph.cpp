#include <iostream>
#include <vector>
#include <stdexcept>

struct Edge {
	int y;
	int weight;

	Edge(): y(0), weight(0){};
	Edge(int y, int w): y(y), weight(w){};
};

class Graph {
private:
	int nvertices;
	int nedges;
	bool directed;

	std::vector<std::vector<Edge>> edges;
	std::vector<int> outDegree;

	void readGraph();
	void insertEdge(int x, int y, int w);

public:
	Graph(int v, int n, bool d);
	void printGraph();
};

Graph::Graph(int v, int n, bool d) {
	nedges = n;
	nvertices = v;
	directed = d;

	edges = std::vector<std::vector<Edge>>(n);
	outDegree = std::vector<int>(n, 0);

	readGraph();
}

void Graph::readGraph() {
	int x, y, w;
	for (int i = 0; i < nedges; i++) {
		std::cin >> x >> y >> w;
		insertEdge(x, y, w);
	}
}

void Graph::insertEdge(int x, int y, int w) {
	if (x < 0 || x >= nvertices || y < 0 || y >= nvertices) {
		throw std::out_of_range("Index of vertex out of range");
	}

	edges[x].push_back(Edge(y, w));
	outDegree[x]++;
	if (directed) {
		edges[y].push_back(Edge(x, w));
		outDegree[y]++;
	}
}

void Graph::printGraph() {
	Edge e;
	for (int i = 0; i < nvertices; i++) {
		if(edges[i].size() > 0) {
			std::cout << i << ":";
			for (int j = 0; j < edges[i].size(); j++) {
				e = edges[i][j];
				std::cout << "	" << e.y << ", weight: " << e.weight << std::endl;
			}
		}
	}
}
