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

#include "graph.h"

using namespace std;

//************************************************************************
// Struct Name:	edge
// Description:
// 		Represents the edge of a graph.
//************************************************************************
struct edge
{
	int fromID;
	int toID;      // id of vertex edge is going to
	double weight; // weight of edge if any
	bool used;     // was edge used in some traversal

	//************************************************************************
	// Method Name:	edge
	// Parameter:	int id, double w
	// Returns:		none
	// Called by:	upon creation of an object
	// Description:
	// 		Parameterized Constructor.
	//************************************************************************
	edge(int id, double w)
	{
		fromID = -1;
		toID = id;
		weight = w;
		used = false;
	}

	//************************************************************************
	// Method Name:	edge
	// Parameter:	int fid, int tid, double w
	// Returns:		none
	// Called by:	upon creation of an object
	// Description:
	// 		Parameterized Constructor.
	//************************************************************************
	edge(int fid, int tid, double w)
	{
		fromID = fid;
		toID = tid;
		weight = w;
		used = false;
	}
	//************************************************************************
	// Method Name:	operator<<
	// Parameter:	const edge e
	// Returns:		formatted output for an edge
	// Called by:	vertex
	// Description:
	// 		Overload cout for edge.
	//************************************************************************
	friend ostream &operator<<(ostream &output, const edge &e)
	{
		if (e.fromID < 0)
			output << "(To: " << e.toID << " W: " << e.weight << " U: " << e.used << ")";
		else
			output << "(From: " << e.fromID << " To: " << e.toID << " W: " << e.weight << " U: " << e.used << ")";
		return output;
	}
};

//************************************************************************
// Class Name:	Heap
// Description:
// 		Set of edges.
//************************************************************************
class edgeHeap
{
private:
	vector<edge *> H;

	//************************************************************************
	// Method Name:	BubbleUp
	// Parameter:	unsigned int i - index of item to be increased
	// Returns:		none
	// Called by:	Insert
	// Description:
	// 		Bubbles element up from given index.
	//************************************************************************
	void BubbleUp(unsigned int i)
	{
		unsigned int p = Parent(i);
		while (p > 0 && H[i]->weight < H[p]->weight) {
			Swap(i, p);
			i = p;
			p = Parent(i);
		}
	}

	//************************************************************************
	// Method Name:	BubbleDown
	// Parameter:	unsigned int i - index of item to be decreased
	// Returns:		none
	// Called by:	Extract, Heapify
	// Description:
	// 		Bubbles element down from given index.
	//************************************************************************
	void BubbleDown(unsigned int i)
	{
		unsigned int c = PickChild(i);

		while (c > 0) {
			if (H[i]->weight > H[c]->weight) {
				Swap(i, c);
				i = c;
				c = PickChild(i);
			}
			else {
				c = -1;
			}
		}
	}

	//************************************************************************
	// Method Name:	Swap
	// Parameter:	unsigned int p, i - indexes of item to swap with
	// Returns:		none
	// Called by:	BubbleUp, BubbleDown
	// Description:
	// 		Swaps two elements in an array.
	//************************************************************************
	void Swap(unsigned int p, unsigned int i)
	{
		edge *temp = H[p];
		H[p] = H[i];
		H[i] = temp;
	}

	//************************************************************************
	// Method Name:	Parent
	// Parameter:	unsigned int i - index to calculate parent from
	// Returns:		unsigned int index
	// Called by:	BubbleUp
	// Description:
	// 		Returns parent index of a given index.
	//************************************************************************
	unsigned int Parent(unsigned int i)
	{
		return unsigned int(i / 2);
	}

	//************************************************************************
	// Method Name:	LeftChild
	// Parameter:	unsigned int i - index to calculate child from
	// Returns:		unsigned int index
	// Called by:	PickChild
	// Description:
	// 		Returns left index of a given index.
	//************************************************************************
	unsigned int LeftChild(unsigned int i)
	{
		return i * 2;
	}

	//************************************************************************
	// Method Name:	RightChild
	// Parameter:	unsigned int i - index to calculate child from
	// Returns:		unsigned int index
	// Called by:	PickChild
	// Description:
	// 		Returns right index of a given index.
	//************************************************************************
	unsigned int RightChild(unsigned int i)
	{
		return i * 2 + 1;
	}


	//************************************************************************
	// Method Name:	PickChild
	// Parameter:	unsigned int i - index of parent element
	// Returns:		unsigned int index
	// Called by:	BubbleDown
	// Description:
	// 		Return index of child to swap with or -1 to not swap.
	//************************************************************************
	unsigned int PickChild(unsigned int i) {
		if (RightChild(i) >= H.size()) {//No right child
			if (LeftChild(i) >= H.size()) {//No left child
				return -1;
			}
			else {//you have a left no right
				return LeftChild(i);
			}
		}
		else {
			//right child exists
			if (H[RightChild(i)] > H[LeftChild(i)]) {
				return RightChild(i);
			}
			else {
				return LeftChild(i);
			}
		}
	}

public:
	//************************************************************************
	// Method Name:	edgeHeap
	// Parameter:	none
	// Returns:		none
	// Called by:	upon creation of an object
	// Description:
	// 		Default Constructor.
	//************************************************************************
	edgeHeap()
	{

	}

	//************************************************************************
	// Method Name:	Insert
	// Parameter:	edge x [int]
	// Returns:		none
	// Called by:	main
	// Description:
	// 		Insert value into heap.
	//************************************************************************
	void Insert(edge* x)
	{
		H.push_back(x);
		BubbleUp(H.size() - 1);
	}

	//************************************************************************
	// Method Name:	Extract
	// Parameter:	none
	// Returns:		edge [int] - top value in the heap
	// Called by:	main
	// Description:
	// 		Removes top element from heap (whether min or max).
	//************************************************************************
	edge* Extract()
	{

		if (Empty()) {
			return NULL;
		}

		edge* retval = H[1];
		H[1] = H.back();
		H.pop_back();


		if (H.size() > 1) {
			BubbleDown(1);
		}

		return retval;
	}

	//************************************************************************
	// Method Name:	PrintHeap
	// Parameter:	none
	// Returns:		none
	// Called by:	main
	// Description:
	// 		Prints the values currently in the heap array
	//		based on array location, not heap order.
	//************************************************************************
	void PrintHeap()
	{
		for (unsigned int i = 1; i < H.size(); i++)
		{
			cout << *H[i] << endl;
		}
		cout << endl;
	}

	//************************************************************************
	// Method Name:	Size
	// Parameter:	none
	// Returns:		int - size of heap
	// Called by:	main
	// Description:
	// 		Returns the number of items in the heap.
	//************************************************************************
	int Size()
	{
		return H.size();
	}

	//************************************************************************
	// Method Name:	Empty
	// Parameter:	none
	// Returns:		bool - is array empty
	// Called by:	main
	// Description:
	// 		Returns boolean true of array is empty.
	//************************************************************************
	bool Empty()
	{
		return H.size() == 0;
	}

	//************************************************************************
	// Method Name:	Heapify
	// Parameter:	vector<edge> A, int size - array of values to heapify
	// Returns:		none
	// Called by:	main
	// Description:
	// 		Creates a heap out of a given array of nums in no specific order.
	//************************************************************************
	void Heapify(vector<edge *>A, int size)
	{
		H = A;
		for (int j = H.size() / 2; j >= 1; j--) {
			BubbleDown(j);
		}
	}
};