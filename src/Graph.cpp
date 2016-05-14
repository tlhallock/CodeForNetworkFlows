/*
 * Graph.cpp
 *
 *  Created on: Apr 29, 2016
 *      Author: thallock
 */

#include "Graph.h"

#include <cstdlib>
#include <iomanip>

Graph::Graph(int n) :
	n{n},
	nodes{(unsigned int) n}
{
	int i=0;
	const auto e = nodes.end();
	for (auto it = nodes.begin(); it!=e; ++it)
		it->setIndex(i++);
}


void Graph::reset()
{
	const auto e = nodes.end();
	for (auto it = nodes.begin(); it!=e; ++it)
		it->reset();
}

Graph::~Graph() {
//	for (int i=0;i<n;i++)
//		delete adjs[i];
//	delete[] adjs;
}

void Graph::resize(int newN) {
	throw 1;
}

std::ostream& Graph::write(std::ostream& out) const {
	out << std::setprecision(11) << std::scientific;
	out << std::setw(4) << n << ' ' << std::setw(4) << getM() << '\n';

	int index = 0;

	const auto end = nodes.end();
	for (auto it = nodes.begin(); it != end; ++it)
	{
		auto e = it->outs().end();
		for (auto i = it->outs().begin(); i != e; ++i)
			out << std::setw(4) << index << ' ' << std::setw(4) << i->first << " " << i->second << '\n';

		index++;
	}
	return out;
}

Graph *readGraph(std::istream& in) {

	int n, m;
	in >> n;
	in >> m;

	Graph *g = new Graph{n};

	for (int i = 0; i < m; i++)
	{
		int start, stop;
		double cost;

		in >> start;
		in >> stop;
		in >> cost;

		g->addEdge(start, stop, cost);
	}

	return g;
}

void Graph::addEdge(int i1, int i2, double cost) {
	if (i1 == i2)
		return;
	nodes[i1].send(i2, cost);
	nodes[i2].receive(i1, cost);
}


int Graph::getM() const {
	int sum = 0;

	for (int i=0;i<n;i++)
		sum += nodes[i].outDegree();

	return sum;
}

bool Graph::adjcent(int i1, int i2) {
	return nodes[i1].isAdjacent(i2);
}

void Graph::randomlyAdd(int m) {
	for (int i=0;i<m;i++)
	{
		int head = (int) (n * (rand() / (double) RAND_MAX));
		int tail = (int) (n * (rand() / (double) RAND_MAX));
		double cost = rand() / (double) RAND_MAX;

		addEdge(tail, head, cost);
	}
}
