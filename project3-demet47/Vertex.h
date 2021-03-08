#include <vector>
using namespace std;

#ifndef VERTEX_H
#define VERTEX_H

class Vertex {
public:
	Vertex(int ID);
	int ID;
	int indegree;
	int outdegree;
	vector<Vertex*> successors;
	//int* available = outdegree;
	int totalAdjacencies;
};

#endif