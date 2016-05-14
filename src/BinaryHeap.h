/*
 * BinaryHeap.h
 *
 *  Created on: Apr 29, 2016
 *      Author: thallock
 */

#ifndef SRC_BINARYHEAP_H_
#define SRC_BINARYHEAP_H_


#include "Node.h"

#include <ostream>

class BinaryHeap {

private:
	int size;
	int max;
	int tnum;

	NodeData **nodes;

	void swap(int i1, int i2);
	void prettyPrint(std::ostream& out, int index, int depth) const;
	void resize(int newSize);
	void pull(int idx);
public:
	BinaryHeap(int tnum);
	BinaryHeap(int tnum, int n);
	virtual ~BinaryHeap();

	void add(NodeData& node);
	NodeData *pop();
	void updateNode(NodeData& n);

	int getSize() const;

	std::ostream& print(std::ostream& out) const;
	std::ostream& prettyPrint(std::ostream& out) const;

	void dbgCheckHeap();
	
	bool containsNode(NodeData& node) const
	{
		return node.getDijsktraIdx(tnum) >= 0;
	}
	
	NodeData *getNode(int index) { return nodes[index]; }
};

#endif /* SRC_BINARYHEAP_H_ */
