#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include "Vertex.h"
#include<queue>
#include <stack>
#include <chrono>

using namespace std;
int edge = 0;
int numOfVertices = 0;

void print(vector<int>** eulerianHashMap, int currentID, bool* hashMapOfIndexesWithSubtours, ofstream& output) {
	hashMapOfIndexesWithSubtours[currentID] = false;
	for (auto i = eulerianHashMap[currentID]->begin(); i != eulerianHashMap[currentID]->end(); i++) {
		int l = *i;
		if (hashMapOfIndexesWithSubtours[l] == true) {
			print(eulerianHashMap, l , hashMapOfIndexesWithSubtours, output);
		}
		else output << l << " ";
	}
}

bool isEulerian(vector<Vertex>& roads) {
	for (Vertex v : roads)
		if (v.indegree != v.outdegree) 
			return false;
	return true;
}


Vertex* findFirstAvailableVertex(vector<int>** hashMapOfSubtours, int ID, bool* hashMapOfIndexesWithSubtours, vector<Vertex>& roads) {
	hashMapOfIndexesWithSubtours[ID] = false;
	for (int i=0; i<hashMapOfSubtours[ID]->size(); i++) {
		int l = (*hashMapOfSubtours[ID])[i];
		if(roads[l].outdegree > 0) return &roads[l];
		if (hashMapOfIndexesWithSubtours[l] == true) {
			hashMapOfIndexesWithSubtours[l] = false;
			Vertex* v = findFirstAvailableVertex(hashMapOfSubtours, l, hashMapOfIndexesWithSubtours, roads);
			if(v != nullptr) return v;
		}
	}
	return nullptr;
}


vector<int>** EulerianCircuit(vector<Vertex>& roads, int ID, bool* hashMapOfIndexesWithSubtours, vector<int>** hashMapOfSubtours) {
	Vertex* current = &roads[ID];
	int  count = 0;
	while (count < edge) {
		vector<int>* subtour = new vector<int>();
		do{
			subtour->push_back(current->ID);
			current = current->successors[current->totalAdjacencies - current->outdegree--];
			count++;
		}while(current->outdegree > 0);
		subtour->push_back(current->ID);

		hashMapOfIndexesWithSubtours[subtour->front()] = true;
		hashMapOfSubtours[subtour->front()] = subtour;

		bool copyHashMap[numOfVertices];
		for(int i=0; i<numOfVertices; i++)
			copyHashMap[i] = hashMapOfIndexesWithSubtours[i];

		current = findFirstAvailableVertex(hashMapOfSubtours, ID, copyHashMap, roads);
		
	}
	
	return hashMapOfSubtours;
}

int main(int args, char* argv[])
{
	ifstream input;
	input.open(argv[1]);
	ofstream output;
	output.open(argv[2]);
	
	int startVertexID;
	input >> numOfVertices;

	vector<Vertex> vertexes;
	for (int i = 0; i < numOfVertices; i++)
		vertexes.push_back(Vertex(i));

	for (int i = 0; i < numOfVertices; i++) {
		int outs;
		int vId;
		input >> vId;
		input >> outs;
		Vertex& v = vertexes[vId];
		v.outdegree = outs;
		v.totalAdjacencies = outs;
		edge += outs;
		while (outs > 0) {
			int adj;
			input >> adj;
			v.successors.push_back(&vertexes[adj]);
			vertexes[adj].indegree++;
			outs--;
		}
	}
	
	input >> startVertexID;

	if (!isEulerian(vertexes)) output << "no path";
	else {
		bool hashMapOfIndexesWithSubtours[numOfVertices];
		for(int i=0; i<numOfVertices; i++)
			hashMapOfIndexesWithSubtours[i] = false;	
		vector<int>** hashMapOfSubtours = (vector<int>**) malloc(numOfVertices * __SIZEOF_POINTER__);
		print(EulerianCircuit(vertexes, startVertexID, hashMapOfIndexesWithSubtours, hashMapOfSubtours), startVertexID, hashMapOfIndexesWithSubtours, output);
	}

	return 0;
}
