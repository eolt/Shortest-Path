#pragma once
#define INT_MAX 2147483647
#include "linkedList.h"
#include <fstream>
#include <sstream>
#include<iostream>
#include<vector>
#include<queue>
#include<string>
using namespace std;

class graph
{
private:
	void printPath(int*, int j, string&);
protected:
	linkedList<pair<int, int>>* adjacentVertices;
	int numVertices;
	int maxNumVertices;

public:
	graph(int n = 100); //Constructor, initializes the parameters with maximum vertices given, default to be 100
	bool isEmpty() const;
	//Function to determine whether the graph is empty. Returns true if it is, otherwise, returns false;
	void createGraph(string file_name);
	//Function to create a graph based on a file, whose name is file_name.
	void clearGraph();
	
	string findShortestPath(int start, int end);

	~graph();
	//Destructor. The storage occupied by the vertices is deallocated.
};


inline void graph::printPath(int* parent, int j, string& result)
{
	if (parent[j] == -1)
		return;
	printPath(parent, parent[j], result);
	result += to_string(j) + " ";
}

inline graph::graph(int n){
   if(n > 100 or n < 0)
      n = 100;
   maxNumVertices = n;
   numVertices = 0;
   adjacentVertices = new linkedList<pair<int, int>>[n]; 
}

inline bool graph::isEmpty() const
{
	return numVertices == 0;
}

inline void graph::createGraph(string file_name){
	ifstream my_file;
	my_file.open(file_name);
	if (!my_file) {
		cerr << "Cannont open file." << endl;
		return;
	}

	string line{};
	int vertex{}, adjacent{}, weight{};
	
	my_file >> numVertices;
	while(getline(my_file, line)){
		my_file >> vertex;
   	my_file >> adjacent;
		my_file >> weight;
		adjacentVertices[vertex].insertLast(make_pair(adjacent, weight));
		}
}

inline void graph::clearGraph(){
	for (int i{}; i < numVertices; ++i)
		adjacentVertices[i].destroyList();
	numVertices = 0;
}

inline string graph::findShortestPath(int start, int end)
{
   if(isEmpty())
		return "The target and the source are not connected.";

	if ((start > numVertices and start < 0) and (end > numVertices and end < 0))
		return "The target and the source are not connected.";
	
	if(adjacentVertices[start].begin() == NULL)
		return "The target and the source are not connected.";	
	
	string result = to_string(start) + " ";
	priority_queue<pair<int, int>, vector<pair<int,int>>, greater<pair<int,int>>> q;
	vector<int> dist(numVertices, INT_MAX);
	int* parent = new int[numVertices];
	parent[start] = -1;
	q.push(make_pair(0, start));
	dist[start] = 0;
	
	while (!q.empty()) {
		int u = q.top().second;
		q.pop();
		auto i = adjacentVertices[u].begin();

		while (i != NULL) {
				int v = (*i).info.first;
				int weight = (*i).info.second;

				if (dist[u] + weight < dist[v]) {
					dist[v] = dist[u] + weight;
					q.push(make_pair(dist[v], v));
					parent[v] = u;
				}
				i = i->link;
		}
	}
	if (dist[end] < 0)
		return "The target and the source are not connected.";
	printPath(parent, end, result);
	return result;
}

inline graph::~graph()
{
	clearGraph();
}
