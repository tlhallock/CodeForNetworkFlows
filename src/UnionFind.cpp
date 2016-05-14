/*
 * UnionFind.cpp
 *
 *  Created on: Apr 29, 2016
 *      Author: thallock
 */

#include "UnionFind.h"

int UnionFind::find(int index) {
	if (parents[index] < 0)
		return index;
	return parents[index] = find(parents[index]);
}

UnionFind::UnionFind(int num) :
	num{num},
	parents{new int[num]}
{
	for (int i=0;i<num;i++)
		parents[num] = -1;
}

UnionFind::~UnionFind() {
	delete[] parents;
}

void UnionFind::join(int i1, int i2) {
	parents[find(i2)] = i1;
}

bool UnionFind::same(int i1, int i2) {
	return find(i1) == find(i2);
}
