/*
 * Node.cpp
 *
 *  Created on: Apr 29, 2016
 *      Author: thallock
 */

#include "Node.h"

#include <limits>

NodeData::NodeData() :
		graphIdx{},
		dijsktraIdx {},
		labelled { },
		cost { },
		prevs { },
		outgoing { },
		incoming { }
{
	reset();
}

NodeData::~NodeData() {}

void NodeData::reset()
{
	for (int i=0;i<NUM_THREADS;i++)
	{
		dijsktraIdx[i] = -1;
		cost[i] = std::numeric_limits<double>::infinity();
		labelled[i] = false;
		prevs[i] = nullptr;
	}
}

std::ostream& NodeData::print(std::ostream& out)
{
	out << '[';

	out << graphIdx << ';';
	
	out << '{';
	for (int i=0;i<NUM_THREADS-1;i++)
		out << dijsktraIdx[i] << ',';
	out << dijsktraIdx[NUM_THREADS-1] << "};";
	
	out << '{';
	for (int i=0;i<NUM_THREADS-1;i++)
		out << labelled[i] << ',';
	out << labelled[NUM_THREADS-1] << "};";
	
	out << '{';
	for (int i=0;i<NUM_THREADS-1;i++)
		out << cost[i] << ',';
	out << cost[NUM_THREADS-1] << "};";
	
	out << "{";
	if (prevs[0] == nullptr)
		out << "null";
	else
		out << prevs[0]->index();
	out << ',';
	if (prevs[1] == nullptr)
		out << "null";
	else
		out << prevs[1]->index();
	out << "};";
	



	out << outgoing.size();

	out << ']';

	return out;
}
