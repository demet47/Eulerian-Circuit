#include <vector>
#include "Vertex.h"
using namespace std;

Vertex::Vertex(int ID) {
	this->ID = ID;
	indegree = 0;
	outdegree = 0;
	totalAdjacencies = 0;
}
