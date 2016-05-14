/*
 * BinaryHeap.cpp
 *
 *  Created on: Apr 29, 2016
 *      Author: thallock
 */

#include "BinaryHeap.h"

#include <iostream>

#define LEFT_CHILD(i)  (2 * i + 1)
#define RIGHT_CHILD(i) (2 * i + 2)
#define PARENT(i)      ((i-1) / 2)
// Careful with this one...
#define MAXIMUM(i, j)  ((i) < (j) ? (j) : (i))

BinaryHeap::BinaryHeap(int tnum, int n) :
	size{0},
	max{MAXIMUM(1, n)},
	tnum{tnum},
	nodes{new NodeData *[MAXIMUM(1, n)]} {}

BinaryHeap::BinaryHeap(int tnum) : BinaryHeap{tnum, 2} {}

BinaryHeap::~BinaryHeap() {
	delete[] nodes;
}

void BinaryHeap::add(NodeData& node) {

	if (size >= max)
		resize(MAXIMUM(1, 2 * max));

	int n = size++;

	nodes[n] = &node;
	node.setDijsktraIdx(n, tnum);

	pull(n);
}

NodeData *BinaryHeap::pop() {
	if (size <= 0)
	{
		std::cout << "Uh oh!" << std::endl;
		throw 1;
	}

	NodeData *returnValue = nodes[0];
	size--;
	swap(0, size);
	returnValue->setDijsktraIdx(-1, tnum);

	int index = 0;
	while (true)
	{
		int li  = LEFT_CHILD(index);
		int ri  = RIGHT_CHILD(index);
		bool vl = li < size && nodes[index]->getCost(tnum) > nodes[li]->getCost(tnum);
		bool vr = ri < size && nodes[index]->getCost(tnum) > nodes[ri]->getCost(tnum);

		if (!vl && !vr) {
			// we are done...
			return returnValue;
		}
		if (vl && !vr) {
			swap(li, index);
			index = li;
			continue;
		}
		if (!vl && vr) {
			swap(ri, index);
			index = ri;
			continue;
		}
		if (nodes[li]->getCost(tnum) < nodes[ri]->getCost(tnum)) {
			swap(li, index);
			index = li;
		} else {
			swap(ri, index);
			index = ri;
		}
	}
}

int BinaryHeap::getSize() const {
	return size;
}

void BinaryHeap::swap(int i1, int i2)
{
	NodeData *tmp = nodes[i1];
	nodes[i1] = nodes[i2];
	nodes[i2] = tmp;

	nodes[i1]->setDijsktraIdx(i1, tnum);
	nodes[i2]->setDijsktraIdx(i2, tnum);
}

std::ostream& BinaryHeap::print(std::ostream& out) const
{
	int index = 0;
	int power = 1;
	while (index < size)
	{
		for (int i=0;i<power && index < size;i++)
			nodes[index++]->print(out);

		out << '\n';
		power *= 2;
	}

	out << '\n';
	return out;
}

void BinaryHeap::prettyPrint(std::ostream& out, int index, int depth) const
{
	if (index >= size)
		return;

	prettyPrint(out, LEFT_CHILD(index), depth + 1);

	for (int i=0;i<depth;i++)
		out << '\t';
	nodes[index]->print(out) << '\n';

	prettyPrint(out, RIGHT_CHILD(index), depth + 1);
}
std::ostream& BinaryHeap::prettyPrint(std::ostream& out) const
{
	out << "Binary heap [size=" << size << ",tnum=" << tnum << "]\n";
	prettyPrint(out, 0, 0);
	out << "-----------------------------------------------------------------\n";
	return out;
}

void BinaryHeap::resize(int newSize)
{
	if (newSize <= size)
	{
		std::cout << "Can't shrink that small..." << std::endl;
		throw 1;
	}

	NodeData **newNodes = new NodeData*[newSize];

	for (int i = 0; i < size; i++)
		newNodes[i] = nodes[i];

	max = newSize;

	delete[] nodes;

	nodes = newNodes;
}

void BinaryHeap::pull(int index)
{
	while (index > 0)
	{
		int parent = PARENT(index);
		if (LEFT_CHILD(parent) != index && RIGHT_CHILD(parent) != index)
		{
			std::cout << "Bad parent identity!" << std::endl;
			return;
		}
		if (nodes[parent]->getCost(tnum) < nodes[index]->getCost(tnum))
		{
			return;
		}
		swap(index, parent);
		index = parent;
	}
}

void BinaryHeap::updateNode(NodeData& n)
{
	if (n.getDijsktraIdx(tnum) < 0)
	{
		add(n);
	}
	else
	{
		pull(n.getDijsktraIdx(tnum));
	}
}

void BinaryHeap::dbgCheckHeap()
{
	for (int i=0;i<size;i++)
	{
		if (LEFT_CHILD(i) < size && nodes[i]->getCost(tnum) > nodes[LEFT_CHILD(i)]->getCost(tnum))
		{
			std::cout << "Failed heap property" << std::endl;
			throw 1;
		}
		if (RIGHT_CHILD(i) < size && nodes[i]->getCost(tnum) > nodes[RIGHT_CHILD(i)]->getCost(tnum))
		{
			std::cout << "Failed heap property" << std::endl;
			throw 1;
		}
	}
}
