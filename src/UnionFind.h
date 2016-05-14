/*
 * UnionFind.h
 *
 *  Created on: Apr 29, 2016
 *      Author: thallock
 */

#ifndef SRC_UNIONFIND_H_
#define SRC_UNIONFIND_H_

class UnionFind {
	int num;
	int *parents;

	int find(int index);
public:
	UnionFind(int num);
	virtual ~UnionFind();

	void join(int i1, int i2);
	bool same(int i1, int i2);
};

#endif /* SRC_UNIONFIND_H_ */
