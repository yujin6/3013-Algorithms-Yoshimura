//****************************************************************************
// Title: Spanning Trees (not really)
// Files: 
// Semester: Spring 2018
// Author: Yujin Yoshimura
// Email: yujinyoshimura@gmail.com
// Description: This program allows to do following. 
//			  Part 1:
//			  - 
//			  Part 2:
//			  - 
//****************************************************************************

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#define PI 3.14159265
using namespace std;

const double RADIUS_OF_EARTH = 3959;

struct vertex{
	int zip;
	double lat;
	double lon;
	string city;
	string state;
	string county;
};

void load(vector<vertex> &v);
vertex parse(string line);
double getDistance(vertex a, vertex b);
double rad(double deg);

int main() {
	vector<vertex> cities;
	load(cities);

	system("pause");
	return 0;
}

//************************************************************************
// Function Name:	load
// Parameter:		reference to vector of vertices
// Returns:			none
// Called by:		
// Description:
// 		Loads cities from one input file into vector of vertices.
//************************************************************************
void load(vector<vertex> &v) {
	string filename = "filtered_cities.csv";
	string line;
	ifstream myfile(filename);
	int i = 0;

	if (myfile.is_open()) {
		while (getline (myfile, line)) {
			v.push_back(parse(line));
			i++;
			if (i % 1000 == 0)
				cout << ".";
		}
		myfile.close();
		cout << " Cities loaded. \n";
	}
	else { cout << "Unable to open file. \n"; }
}

//************************************************************************
// Function Name:	parse
// Parameter:		string of all the city data
// Returns:			vertex
// Called by:		load
// Description:
// 		parse a line of string into 6 parts in order as follows:
//		zip, lat, lon, city, state, county
//************************************************************************
vertex parse(string line) {
	vertex c;
	stringstream ss(line);
	string val;
	int i = 0;
	while (getline(ss, val, ',')) {
		switch (i) {
		case 0: c.zip = stoi(val);	break;
		case 1: c.lat = stod(val);	break;
		case 2: c.lon = stod(val);	break;
		case 3: c.city = val;		break;
		case 4: c.state = val;		break;
		case 5: c.county = val;		break;
		default: break;
		}
		i++;
	}
	return c;
}

//************************************************************************
// Function Name:	getDistance
// Parameter:		two vertices
// Returns:			double
// Called by:		
// Description:
// 		gets distance between two cities in miles.
//		formula for calculating distance is as follows:
//		D = R * arccos(sin ƒÆ1 * sin ƒÆ2 + cos ƒÆ1 * cos ƒÆ2 * cos(ƒÓ2 - ƒÓ1))
//************************************************************************
double getDistance(vertex a, vertex b) {
	return RADIUS_OF_EARTH * acos(sin(rad(a.lat))*sin(rad(b.lat)) + cos(rad(a.lat))*cos(rad(b.lat))*cos(rad(a.lon - b.lon)));
}

//************************************************************************
// Function Name:	rad
// Parameter:		double in degrees
// Returns:			double in radian
// Called by:		getDistance
// Description:
// 		convert from degrees to radian.
//		formula for conversion is as follows:
//		rad = deg * ƒÎ / 180
//************************************************************************
double rad(double deg) {
	return deg * PI / 180;
}
