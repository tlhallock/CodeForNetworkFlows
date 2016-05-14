/*
 * Path.h
 *
 *  Created on: Apr 29, 2016
 *      Author: thallock
 */

#ifndef SRC_PATH_H_
#define SRC_PATH_H_

#include <list>
#include <iostream>
#include <fstream>

#include "Graph.h"

class Path {
private:
	std::list<int> path;
public:
	Path();
	virtual ~Path();

	void add(int j) { path.push_back(j); }
	int pop() { int i=path.back(); path.pop_back(); return i; }

	std::ostream& print(std::ostream& out);
	double getCost(Graph& g/*, bool forward*/);

	Path& operator=(const Path& other);

	bool operator==(const Path& other) const;
	
	void reverse() { path.reverse(); }

	int length() { return path.size(); }

	void clear()
	{
		path.clear();
	}

	void debug(Graph *g)
	{
		double cost = 0;

		std::ofstream out {"script.sh"};

		std::string s = "arcs.csv";
//		std::string s = "mine.txt";

		int prevNode = path.front();
		const auto e = path.end();
		for (auto i = ++path.begin(); i!=e; ++i)
		{
			double c = g->getNode(prevNode).getCostTo(*i, true);
			cost += c;
			out << "a=$(egrep '" << prevNode << "," << *i << ",[0-9]*,[0-9]*," << c << "' " << s << ")" << std::endl;
			out << "[[ \"$a\" ]] || echo missing node" << std::endl;
			out << "echo \"$a\" >> theList.txt" << std::endl;
			out << "#edge " << prevNode << " to " << *i << std::endl;
			out << "#total cost now: " << cost << std::endl;
			out << "#current cost " << c << std::endl;
			prevNode = *i;
		}
	}

	void assign(std::list<int>& vec)
	{
		path = vec;
	}
};



void createOptimalPath(std::list<int>& vec);


#endif /* SRC_PATH_H_ */
