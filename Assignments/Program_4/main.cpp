//****************************************************************************
// Title: Spanning Trees (not really)
// Files: 
// Semester: Spring 2018
// Author: Yujin Yoshimura
// Email: yujinyoshimura@gmail.com
// Description: This program allows to do following. 
//		- Fully connect your cities by adding edges between cities.
//		- Each vertex has a max degree of 3.
//		- Each edge represents one of three closest cities to that vertex.
//****************************************************************************

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include "graph.h"

using namespace std;

vertex* setRoot(string state, graph G, string &city, vector<vertex*> &V);
vertex* setPRRoot(string state, graph G, string &city, vector<vertex*> &V);
void swapCity(double &prevd, double &distance, vertex &prevc, vertex &city);
void updateDistance(int count, double &distance, vertex city, graph &G, vertex* root, int &edges, double &miles, queue<vertex*> Q);

int main(int argc, char **argv) {
	string state;
	ofstream outfile;
	outfile.open("output.txt", fstream::app);
	int loop = 1;

	if (argc > 1 && argc<3) {
		state = argv[1];
	}
	else {
		cout << "Please enter argument." << endl;
		exit(0);
	}
	if (state == "ALL" || state == "All")
		loop = 6;

	for (int j = 0; j < loop; j++) {
		vector<vertex*> V;
		queue<vertex*> Q;
		graph G;
		vertex* root;
		vertex city1, city2, city3;
		string city;
		double distance1 = DBL_MAX, distance2 = DBL_MAX, distance3 = DBL_MAX;
		double total_distance = 0;
		int edges = 0;

		if (loop == 6) {
			switch (j) {
			case 1: state = "FL";	break;
			case 2: state = "TX";	break;
			case 3: state = "MA";	break;
			case 4: state = "OR";	break;
			case 5: state = "PR";	break;
			default: state = "KS";	break;
			}
		}

		if (state != "PR") {
			G = loadGraphCSV("filtered_cities.csv");
			root = setRoot(state, G, city, V);
		}
		else {
			G = loadPRGraphCSV("filtered_cities.csv");
			root = setPRRoot(state, G, city, V);
		}
		Q.push(root);

		while (!V.empty()) {
			root = V.front();
			Q.pop();
			if (root->E.size() < 3) {
				for (unsigned int i = 0; i < V.size(); i++) {
					if (V[i]->ID == root->ID) {
						V.erase(V.begin() + i);
						i--;
					}
					else if (G.vertexList[V[i]->ID]->E.size() >= 3) {
						V.erase(V.begin() + i);
						i--;
					}
					else {
						double prevd = distanceEarth(root->loc.lat, root->loc.lon, V[i]->loc.lat, V[i]->loc.lon);
						vertex prevc = *V[i];
						swapCity(prevd, distance1, prevc, city1);
						swapCity(prevd, distance2, prevc, city2);
						swapCity(prevd, distance3, prevc, city3);
					}
				}
				int count = 3 - root->E.size();
				updateDistance(count, distance1, city1, G, root, edges, total_distance, Q);
				updateDistance(count, distance2, city2, G, root, edges, total_distance, Q);
				updateDistance(count, distance3, city3, G, root, edges, total_distance, Q);
			}
		}
		if (state == "PR") {
			ofstream out;
			out.open("graph.txt");
			out << G.graphViz();
		}

		outfile << " - " << city << ", " << state << endl;
		outfile << "   " << total_distance << " miles, " << edges << " edges" << endl;
		total_distance = 0;
		edges = 0;
	}
	return 0;
}

//************************************************************************
// Function Name:	setRoot
// Parameter:		string state, graph G, string city, vector<vertex*> V
// Returns:			pointer to vertex
// Called by:		main
// Description:
// 		set the root city according to the choice of the state.
//		Default is KS.
//************************************************************************
vertex* setRoot(string state, graph G, string &city, vector<vertex*> &V) {
	vertex* root = NULL;

	if (state == "FL" || state == "TX" || state == "MA" || state == "OR") {
		for (unsigned int i = 0; i < G.vertexSize(); i++)
		{
			if (state == "FL" && G.city(i) == "Miami Beach" && G.state(i) == "FL") {
				city = "Miami Beach";
				root = G.getVertex(i);
			}
			else if (state == "TX" && G.city(i) == "Lake Dallas" && G.state(i) == "TX") {
				city = "Lake Dallas";
				root = G.getVertex(i);
			}
			else if (state == "MA" && G.city(i) == "Boston" && G.state(i) == "MA") {
				city = "Boston";
				root = G.getVertex(i);
			}
			else if (state == "OR" && G.city(i) == "Oregon City" && G.state(i) == "OR") {
				city = "Oregon City";
				root = G.getVertex(i);
			}
		}
		V = G.vertexList;
	}
	else {
		city = "Lebanon";
		state = "KS";
		G.addVertex(city, state, 39.809734, -98.55562);
		V = G.vertexList;
		root = V.back();
	}
	return root;
}

//************************************************************************
// Function Name:	setPRRoot
// Parameter:		string state, graph G, string city, vector<vertex*> V
// Returns:			pointer to vertex
// Called by:		main
// Description:
// 		set the root city in PR.
//************************************************************************
vertex* setPRRoot(string state, graph G, string &city, vector<vertex*> &V) {
	vertex* root = NULL;
	for (unsigned int i = 0; i < G.vertexList.size(); i++)
	{
		if (G.vertexList[i]->state == "PR"&&G.vertexList[i]->city == "San Juan")
		{
			root = G.vertexList[i];
			city = "San Juan";
			break;
		}
	}
	V = G.vertexList;
	return root;
}

//************************************************************************
// Function Name:	swapCity
// Parameter:		double prevd, double distance, vertex prevc, vertex city
// Returns:			none
// Called by:		main
// Description:
// 		if the distance is less than the previous one, swap.
//************************************************************************
void swapCity(double &prevd, double &distance, vertex &prevc, vertex &city) {
	double tempd;
	vertex tempc;
	if (prevd < distance) {
		tempd = distance;
		distance = prevd;
		prevd = tempd;

		tempc = city;
		city = prevc;
		prevc = tempc;
	}
}

//************************************************************************
// Function Name:	updateDistance
// Parameter:		int count, double distance, vertex city, graph G,
//					vertex root, int edges, double total_distance, queue<vertex*> Q
// Returns:			none
// Called by:		main
// Description:
// 		adds an edge and updates distance according to the added edge.
//************************************************************************
void updateDistance(int count, double &distance, vertex city, graph &G, vertex* root, int &edges, double &total_distance, queue<vertex*> Q) {
	if (count > 0 && !(distance == DBL_MAX))
	{
		G.addEdge(root->ID, city.ID, distance);
		edges++;
		total_distance += distance;
		if (G.vertexList[city.ID]->E.size() < 3)
			Q.push(G.vertexList[city.ID]);
	}
	distance = DBL_MAX;
}
