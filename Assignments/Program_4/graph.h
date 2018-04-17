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
#pragma once
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include "edge_heap.h"
#include "distance.h"
#include "csv.h"

using namespace std;

// Might use as a lookup from city name to ID.
// And to filter duplicate cities.
typedef map<string, int> strMapInt;

typedef map<int, int> intint;

//************************************************************************
// Struct Name:	latlon
// Description:
// 		Represents latitude and longitude of a vertex.
//************************************************************************
struct latlon
{
	double lat;
	double lon;

	//************************************************************************
	// Method Name:	latlon
	// Parameter:	none
	// Returns:		none
	// Called by:	upon creation of an object
	// Description:
	// 		Default Constructor.
	//************************************************************************
	latlon()
	{
		lat = 0.0;
		lon = 0.0;
	}

	//************************************************************************
	// Method Name:	latlon
	// Parameter:	double y, double x
	// Returns:		none
	// Called by:	upon creation of an object
	// Description:
	// 		Parameterized Constructor.
	//************************************************************************
	latlon(double y, double x)
	{
		lat = y;
		lon = x;
	}

	//************************************************************************
	// Method Name:	operator=
	// Parameter:	const latlon ll
	// Returns:		reference to assignment for chaining (e.g. a = b = c )
	// Called by:	vertex
	// Description:
	// 		Overload assignment for latlon.
	//************************************************************************
	latlon &operator=(const latlon &ll)
	{
		// do the copy
		lat = ll.lat;
		lon = ll.lon;

		// return the existing object so we can chain this operator
		return *this;
	}

	//************************************************************************
	// Method Name:	operator<<
	// Parameter:	const latlon ll
	// Returns:		formatted output for a latlon
	// Called by:	vertex
	// Description:
	// 		Overload cout for latlon.
	//************************************************************************
	friend ostream &operator<<(ostream &output, const latlon &ll)
	{
		output << "(" << ll.lat << "," << ll.lon << ")";
		return output;
	}
};

//************************************************************************
// Struct Name:	vertex
// Description:
// 		Represents a vertex in a graph.
//************************************************************************
struct vertex
{
	int ID;
	string city;
	string state;
	latlon loc;
	vector<edge> E;
	bool visited;

	//************************************************************************
	// Method Name:	vertex
	// Parameter:	int id, string c, string s, latlon ll
	// Returns:		none
	// Called by:	upon creation of an object
	// Description:
	// 		Default Constructor.
	//************************************************************************
	vertex(int id = 0, string c = "", string s = "", latlon ll = latlon())
	{
		ID = id;
		city = c;
		state = s;
		loc = ll;
		visited = false;
	}

	//************************************************************************
	// Method Name:	vertex<<
	// Parameter:	const vertex v
	// Returns:		formatted output for a vertex
	// Called by:	
	// Description:
	// 		Overload cout for vertex.
	//************************************************************************
	friend ostream &operator<<(ostream &output, const vertex &v)
	{
		output << "(ID:" << v.ID << " C: " << v.city << " S: " << v.state << " L: " << v.loc << " Edges:" << v.E.size() << ")";
		return output;
	}
};

//************************************************************************
// Class Name:	graph
// Description:
// 		Set of vertices and edges.
//************************************************************************
class graph
{
private:
	int id;                      // id counter for new vertices
	int num_edges;               // edge count
	strMapInt cityLookup;

	//************************************************************************
	// Method Name:	createVertex
	// Parameter:	string city, string state, latlon ll
	// Returns:		pointer to vertex
	// Called by:	addVertex
	// Description:
	// 		Returns a new vertex with unique id.
	//************************************************************************
	vertex *createVertex(string city, string state, latlon ll)
	{
		return new vertex(id++, city, state, ll);
	}

public:
	vector<vertex *> vertexList; // vector to hold vertices

	//************************************************************************
	// Method Name:	graph
	// Parameter:	none
	// Returns:		none
	// Called by:	upon creation of an object
	// Description:
	// 		Default Constructor.
	//************************************************************************
	graph()
	{
		id = 0;
		num_edges = 0;
	}

	//************************************************************************
	// Method Name:	graph
	// Parameter:	const graph G
	// Returns:		none
	// Called by:	upon creation of an object
	// Description:
	// 		Copy Constructor.
	//************************************************************************
	graph(const graph &G)
	{
		id = G.id;
		num_edges = 0;
		vertexList = G.vertexList;
		cityLookup = G.cityLookup;
	}

	//************************************************************************
	// Method Name:	addVertex
	// Parameter:	string city, string state, double lat, double lon
	// Returns:		int ID
	// Called by:	loadGraphCSV, loadPRGraphCSV
	// Description:
	// 		Adds a vertex to the graph.
	//************************************************************************
	int addVertex(string city, string state, double lat = 0.0, double lon = 0.0)
	{
		if (cityLookup.find(city) == cityLookup.end())
		{
			// Add the city as a key to the map.
			cityLookup[city] = 0;
		}
		else
		{
			return -1;
		}

		vertex *temp = createVertex(city, state, latlon(lat, lon));
		vertexList.push_back(temp);

		//update the value that city points to.
		cityLookup[city] = temp->ID;
		return temp->ID;
	}

	//************************************************************************
	// Method Name:	addEdge
	// Parameter:	int fromID, int toID, double weight, bool directed
	// Returns:		none
	// Called by:	addEdge(overload)
	// Description:
	// 		Adds a relationship between two vertices to the graph.
	//************************************************************************
	void addEdge(int fromID, int toID, double weight = 0, bool directed = false)
	{
		edge e1(toID, weight);
		vertexList[fromID]->E.push_back(e1);
		num_edges++;

		//cout<<"adding "<<fromID<<" to "<<toID<<endl;

		if (!directed)
		{
			edge e2(fromID, weight);
			vertexList[toID]->E.push_back(e2);

			//cout<<"adding "<<toID<<" to "<<fromID<<endl;

			num_edges++;
		}
	}

	//************************************************************************
	// Method Name:	addEdge
	// Parameter:	string fromCity, string toCity, double weight, bool directed
	// Returns:		none
	// Called by:	randomEdges
	// Description:
	// 		Adds a relationship between two vertices to the graph.
	//************************************************************************
	void addEdge(string fromCity, string toCity, double weight = 0, bool directed = false)
	{
		int fromId = cityLookup[fromCity];
		int toID = cityLookup[toCity];
		addEdge(fromId, toID, weight, directed);
	};


	//************************************************************************
	// Method Name:	printGraph
	// Parameter:	none
	// Returns:		none
	// Called by:	main
	// Description:
	// 		Prints the graph out for debugging purposes.
	//************************************************************************
	void printGraph()
	{

		vector<vertex *>::iterator vit;
		vector<edge>::iterator eit;

		for (vit = vertexList.begin(); vit != vertexList.end(); vit++)
		{
			cout << *(*vit) << endl;

			if ((*vit)->E.size() > 0)
			{
				for (eit = (*vit)->E.begin(); eit != (*vit)->E.end(); eit++)
				{
					cout << "\t" << (*eit) << endl;
				}
			}
		}
	}

	//************************************************************************
	// Method Name:	printVids
	// Parameter:	none
	// Returns:		none
	// Called by:	GraphViz
	// Description:
	// 		prints for GraphViz.
	//************************************************************************
	void printVids() {
		vector<vertex *>::iterator vit;
		vector<edge>::iterator eit;

		for (vit = vertexList.begin(); vit != vertexList.end(); vit++)
		{
			cout << (*vit)->ID << endl;
		}
	}

	//************************************************************************
	// Method Name:	graphViz
	// Parameter:	bool directed
	// Returns:		string
	// Called by:	GraphViz
	// Description:
	// 		prints for GraphViz.
	//************************************************************************
	string graphViz(bool directed = true) {
		vector<vertex *>::iterator vit;
		vector<edge>::iterator eit;

		// [label="hi", weight=100];

		string viz = "";
		string labels = "";
		string conns = "";
		double weight = 0;
		string arrow = "";

		if (directed) {
			viz = "digraph G {\n";
			arrow = "->";

		}
		else {
			viz = "graph G {\n";
			arrow = "--";
		}

		for (vit = vertexList.begin(); vit != vertexList.end(); vit++)
		{
			if ((*vit)->E.size() > 0)
			{
				labels += "\t" + to_string((*vit)->ID) + " [label=\"" + (*vit)->city + ", " + (*vit)->state + "\"]\n";

				for (eit = (*vit)->E.begin(); eit != (*vit)->E.end(); eit++)
				{


					labels += "\t" + to_string(eit->toID) + " [label=\"" + vertexList[eit->toID]->city + ", " + vertexList[eit->toID]->state + "\"]\n";

					weight = eit->weight;
					if ((*vit)->ID > eit->toID) {
						conns += "\t" + to_string((*vit)->ID) + arrow
							+ to_string(eit->toID) + " [weight=" + to_string(weight) + ", label=" + to_string(weight) + "]\n";
					}
				}
			}
		}

		viz += labels;
		viz += conns;
		viz += "}\n";

		return viz;
	}

	//************************************************************************
	// Method Name:	maxID
	// Parameter:	none
	// Returns:		int
	// Called by:	main
	// Description:
	// 		Returns the max id assigned to any vertex.
	//************************************************************************
	int maxID()
	{
		return id;
	}

	//************************************************************************
	// Method Name:	graphSize
	// Parameter:	none
	// Returns:		int
	// Called by:	main
	// Description:
	// 		Returns the number of vertices and edges.
	//************************************************************************
	int* graphSize() {
		int* vals = new int[2];
		vals[0] = vertexList.size();
		vals[1] = num_edges;
		return vals;
	}

	//************************************************************************
	// Method Name:	operator=
	// Parameter:	const graph g
	// Returns:		graph reference to assignment for chaining (e.g. a = b = c )
	// Called by:	main
	// Description:
	// 		Overload assignment for Graph.
	//************************************************************************
	graph &operator=(const graph &g)
	{
		// do the copy
		vertexList = g.vertexList;
		id = g.id;

		// return the existing object so we can chain this operator
		return *this;
	}

	//************************************************************************
	// Method Name:	vertexSize
	// Parameter:	none
	// Returns:		int i
	// Called by:	randomEdges, main
	// Description:
	// 		Returns size of the vertices.
	//************************************************************************
	int vertexSize() {
		return vertexList.size();
	}

	//************************************************************************
	// Method Name:	city
	// Parameter:	int i
	// Returns:		string city
	// Called by:	main
	// Description:
	// 		Returns city of the given index.
	//************************************************************************
	string city(int i)
	{
		return vertexList[i]->city;
	}

	//************************************************************************
	// Method Name:	state
	// Parameter:	int i
	// Returns:		string state
	// Called by:	main
	// Description:
	// 		Returns state of the given index.
	//************************************************************************
	string state(int i)
	{
		return vertexList[i]->state;
	}

	//************************************************************************
	// Method Name:	state
	// Parameter:	int i
	// Returns:		pointer to vertex
	// Called by:	main
	// Description:
	// 		Returns vertex of the given index.
	//************************************************************************
	vertex* getVertex(int i)
	{
		return vertexList[i];
	}
};

//************************************************************************
// Function Name:	randomEdges
// Parameter:		graph g, int numEdges
// Returns:			none
// Called by:		main
// Description:
// 		Picks random Edges.
//************************************************************************
void randomEdges(graph &g, int numEdges) {
	int r1, r2;
	latlon from;
	latlon to;
	double d;
	for (int i = 0; i<numEdges; i++) {
		r1 = rand() % g.vertexSize();
		r2 = rand() % g.vertexSize();
		from = g.vertexList[r1]->loc;
		to = g.vertexList[r2]->loc;
		d = distanceEarth(from.lat, from.lon, to.lat, to.lon);
		g.addEdge(r1, r2, (int)d, true);
	}
}

//************************************************************************
// Function Name:	loadGraphCSV
// Parameter:		string filename, int max
// Returns:			graph
// Called by:		main
// Description:
// 		Loads a graph with the given csv.
//************************************************************************
graph loadGraphCSV(string filename, int max = 0)
{
	int zip;
	double lat;
	double lon;
	string city;
	string state;

	strMapInt cityCheck;

	int i = 0;

	graph G;

	ifstream file(filename);

	for (CSVIterator loop(file); loop != CSVIterator(); ++loop)
	{
		zip = stoi((*loop)[0]);
		if ((*loop)[1].length() > 0)
		{
			lat = stod((*loop)[1]);
		}
		else
		{
			lat = 0.0;
		}

		if ((*loop)[2].length() > 0)
		{
			lon = stod((*loop)[2]);
		}
		else
		{
			lon = 0.0;
		}

		city = (*loop)[3];
		state = (*loop)[4];

		if (cityCheck.find(city) == cityCheck.end())
		{
			// Add the city as a key to the map.
			cityCheck[city] = 0;

			if (state != "PR") {
				G.addVertex(city, state, lat, lon);
				i++;
			}
		}

		if (i > max && max != 0) {
			return G;
		}

	}

	return G;
}

//************************************************************************
// Function Name:	loadPRGraphCSV
// Parameter:		string filename, int max
// Returns:			graph
// Called by:		main
// Description:
// 		Loads a graph with the given csv with cities from Puerto Rico.
//************************************************************************
graph loadPRGraphCSV(string filename, int max = 0)
{
	int zip;
	double lat;
	double lon;
	string city;
	string state;

	strMapInt cityCheck;

	int i = 0;

	graph G;

	ifstream file(filename);

	for (CSVIterator loop(file); loop != CSVIterator(); ++loop)
	{
		zip = stoi((*loop)[0]);
		if ((*loop)[1].length() > 0)
		{
			lat = stod((*loop)[1]);
		}
		else
		{
			lat = 0.0;
		}

		if ((*loop)[2].length() > 0)
		{
			lon = stod((*loop)[2]);
		}
		else
		{
			lon = 0.0;
		}

		city = (*loop)[3];
		state = (*loop)[4];

		if (cityCheck.find(city) == cityCheck.end())
		{
			// Add the city as a key to the map.
			cityCheck[city] = 0;

			if (state == "PR") {
				G.addVertex(city, state, lat, lon);
				i++;
			}
		}

		if (i > max && max != 0) {
			return G;
		}

	}

	return G;
}

//************************************************************************
// Function Name:	filterDups
// Parameter:		string filename, string outfile
// Returns:			graph
// Called by:		main
// Description:
// 		Filters out duplicate cities and creates new output file.
//************************************************************************
void filterDups(string filename, string outfile)
{
	int zip;
	double lat;
	double lon;
	string city;
	string state;

	strMapInt cityCheck;

	int i = 0;


	ifstream file(filename);
	ofstream out(outfile);

	for (CSVIterator loop(file); loop != CSVIterator(); ++loop)
	{
		zip = stoi((*loop)[0]);
		if ((*loop)[1].length() > 0)
		{
			lat = stod((*loop)[1]);
		}
		else
		{
			lat = 0.0;
		}

		if ((*loop)[2].length() > 0)
		{
			lon = stod((*loop)[2]);
		}
		else
		{
			lon = 0.0;
		}

		city = (*loop)[3];
		state = (*loop)[4];

		if (cityCheck.find(city) == cityCheck.end())
		{
			// Add the city as a key to the map.
			cityCheck[city] = 0;
			out << zip << "," << lat << "," << lon << "," << city << "," << state << "\n";

		}


	}

}
