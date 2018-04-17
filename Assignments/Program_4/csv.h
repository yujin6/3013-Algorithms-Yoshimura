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
#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

//************************************************************************
// Class Name:	CSVRow
// Description:
// 		Represents a row in csv.
//************************************************************************
class CSVRow
{
public:

	//************************************************************************
	// Method Name:	operator[]
	// Parameter:	size_t index
	// Returns:		string
	// Called by:	
	// Description:
	// 		Overload array for CSVRow.
	//************************************************************************
	string const& operator[](size_t index) const
	{
		return m_data[index];
	}

	//************************************************************************
	// Method Name:	size
	// Parameter:	none
	// Returns:		size_t
	// Called by:	
	// Description:
	// 		Returns size.
	//************************************************************************
	size_t size() const
	{
		return m_data.size();
	}

	//************************************************************************
	// Method Name:	readNextRow
	// Parameter:	istream str
	// Returns:		none
	// Called by:	operator>> 
	// Description:
	// 		Reads next row with the given csv.
	//************************************************************************
	void readNextRow(istream& str)
	{
		string line;
		getline(str, line);

		stringstream lineStream(line);
		string cell;

		m_data.clear();
		while (getline(lineStream, cell, ','))
		{
			m_data.push_back(cell);
		}
		// This checks for a trailing comma with no data after it.
		if (!lineStream && cell.empty())
		{
			// If there was a trailing comma then add an empty element.
			m_data.push_back("");
		}
	}

private:
	vector<string> m_data;
};

//************************************************************************
// Function Name:	operator>>
// Parameter:		istream str, CSVRow data
// Returns:			istream
// Called by:		
// Description:
// 		Overload cin for CSVRow.
//************************************************************************
istream& operator >> (istream& str, CSVRow& data)
{
	data.readNextRow(str);
	return str;
}

//************************************************************************
// Class Name:	CSVIterator
// Description:
// 		Represents an iterator in csv.
//************************************************************************
class CSVIterator
{
public:
	typedef input_iterator_tag	iterator_category;
	typedef CSVRow				value_type;
	typedef size_t				difference_type;
	typedef CSVRow*				pointer;
	typedef CSVRow&				reference;

	//************************************************************************
	// Method Name:	CSVIterator
	// Parameter:	istream str
	// Returns:		none
	// Called by:	upon creation of an object
	// Description:
	// 		Parameterized Constructor.
	//************************************************************************
	CSVIterator(istream& str) :m_str(str.good() ? &str : NULL) { ++(*this); }

	//************************************************************************
	// Method Name:	CSVIterator
	// Parameter:	none
	// Returns:		none
	// Called by:	upon creation of an object
	// Description:
	// 		Default Constructor.
	//************************************************************************
	CSVIterator() :m_str(NULL) {}

	//************************************************************************
	// Method Name:	operator++
	// Parameter:	none
	// Returns:		reference to pre increment for chaining (e.g. a = b = c )
	// Called by:	Constructor
	// Description:
	// 		Overload pre increment for CSVIterator.
	//************************************************************************
	CSVIterator& operator++() { if (m_str) { if (!((*m_str) >> m_row)) { m_str = NULL; } }return *this; }

	//************************************************************************
	// Method Name:	operator++
	// Parameter:	int
	// Returns:		reference to post increment for chaining (e.g. a = b = c )
	// Called by:	Constructor
	// Description:
	// 		Overload post increment for CSVIterator.
	//************************************************************************
	CSVIterator operator++(int) { CSVIterator tmp(*this); ++(*this); return tmp; }

	//************************************************************************
	// Method Name:	operator*
	// Parameter:	none
	// Returns:		CSVRow
	// Called by:	
	// Description:
	// 		Overload reference for CSVIterator.
	//************************************************************************
	CSVRow const& operator*()   const { return m_row; }

	//************************************************************************
	// Method Name:	operator->
	// Parameter:	none
	// Returns:		CSVRow
	// Called by:	
	// Description:
	// 		Overload pointer for CSVIterator.
	//************************************************************************
	CSVRow const* operator->()  const { return &m_row; }

	//************************************************************************
	// Method Name:	operator==
	// Parameter:	CSVIterator rhs
	// Returns:		bool
	// Called by:	
	// Description:
	// 		Overload comparison for CSVIterator.
	//************************************************************************
	bool operator==(CSVIterator const& rhs) { return ((this == &rhs) || ((this->m_str == NULL) && (rhs.m_str == NULL))); }

	//************************************************************************
	// Method Name:	operator!=
	// Parameter:	CSVIterator rhs
	// Returns:		bool
	// Called by:	
	// Description:
	// 		Overload comparison for CSVIterator.
	//************************************************************************
	bool operator!=(CSVIterator const& rhs) { return !((*this) == rhs); }

private:
	istream* m_str;
	CSVRow m_row;
};
