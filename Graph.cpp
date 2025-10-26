#include <iostream>
#include <vector>
#include <queue>
#include <stack>
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

	void DFSRecursiveHelper(int start, std::vector<bool> &discovered, std::vector<bool> &processed, std::vector<int> &parent);

public:
	Graph(int v, int n, bool d);				/* init graph */
	void printGraph();							/* print edges and edge weights */
	std::vector<int> BFS(int start);			/* returns parent vector for nodes after BFS */
	std::vector<int> DFSIterative(int start);	/* returns parent vector for nodes after DFS */
	std::vector<int> DFSRecursive(int start);
};

Graph::Graph(int v, int n, bool d) {
	nedges = n;
	nvertices = v;
	directed = d;

	edges = std::vector<std::vector<Edge>>(v);
	outDegree = std::vector<int>(v, 0);

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
	if (!directed) {
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

std::vector<int> Graph::BFS(int start) {
	std::queue<int> q;
	std::vector<bool> discovered(nvertices, false);
	std::vector<bool> processed(nvertices, false);
	std::vector<int> parent(nvertices, -1);

	int x;
	Edge e;

	q.push(start);
	discovered[start] = true;

	while (!q.empty()) {
		x = q.front();
		q.pop();
		/* perform early vertex processing here */
		processed[x] = true;
		for (int i = 0; i < edges[x].size(); i++) {
			e = edges[x][i];
			if (!processed[e.y] || directed) {
				/* perform edge processing here */
			}
			if (!discovered[e.y]) {
				q.push(e.y);
				discovered[e.y] = true;
				parent[e.y] = x;
			}
		}
		/* perform late vertex processing here */
	}

	return parent;
}

std::vector<int> Graph::DFSIterative(int start) {
	std::stack<int> s;
	std::vector<bool> discovered(nvertices, false);
	std::vector<bool> processed(nvertices, false);
	std::vector<int> parent(nvertices, -1);

	int x;
	Edge e;
	bool skip;

	s.push(start);
	discovered[start] = true;

	while (!s.empty()) {
		x = s.top();
		skip = false;

		/* perform early vertex processing here */
		for (int i = 0; i < edges[x].size(); i++) {
			e = edges[x][i];
			if (!discovered[e.y]) {
				parent[e.y] = x;
				/* perform edge processing here */
				s.push(e.y);
				discovered[e.y] = true;
				skip = true;
				break;
			} else if ((!processed[e.y] && parent[x] == e.y) || directed) {
				/* perform edge processing here */
			}
		}

		if (skip) continue;
		/* perform late vertex processing here */
		processed[x] = true;
		s.pop();
	}
	return parent;
}

std::vector<int> Graph::DFSRecursive(int start) {
	std::vector<bool> discovered(nvertices, false);
    std::vector<bool> processed(nvertices, false);
    std::vector<int> parent(nvertices, -1);

    discovered[start] = true;
    DFSRecursiveHelper(start, discovered, processed, parent);
    return parent;
}

void Graph::DFSRecursiveHelper(int start, std::vector<bool> &discovered, std::vector<bool> &processed, std::vector<int> &parent) {
	discovered[start] = true;
	/* perform early vertex processing here */
	Edge e;
	for (int i = 0; i < edges[start].size(); i++) {
		e = edges[start][i];
		if (!discovered[e.y]) {
			parent[e.y] = start;
			/* perform edge processing here */
			DFSRecursiveHelper(e.y, discovered, processed, parent);
		} else if ((!processed[e.y] && parent[start] != e.y) || directed) {
			/* perform edge processing here */
		}
	}
	/* perform late processing here */
	processed[start] = true;
}
