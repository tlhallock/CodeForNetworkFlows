/*
 * Node.h
 *
 *  Created on: Apr 29, 2016
 *      Author: thallock
 */



#ifndef SRC_NODE_H_
#define SRC_NODE_H_

#include <map>
#include <ostream>

#include "constants.h"

class NodeData
{
private:
	int graphIdx;
	int dijsktraIdx[NUM_THREADS];
	bool labelled[NUM_THREADS];
	double cost[NUM_THREADS];
	NodeData *prevs[NUM_THREADS];
	std::map<int, double> outgoing;
	std::map<int, double> incoming;

public:
	NodeData();
	virtual ~NodeData();

	void reset();

	int index() { return graphIdx; }
	void setIndex(int idx) { graphIdx = idx; }

	std::ostream& print(std::ostream& out);

	double getOtherCost(int tnum) { return cost[tnum == 0 ? 1 : 0]; }
	double getCost(int tnum) { return cost[tnum]; }
	void setCost(double c, int tnum) { cost[tnum] = c; }

	void setPrev(NodeData *prev, int tnum) { prevs[tnum] = prev; }
	NodeData *getPrev(int tnum) { return prevs[tnum]; }


	void setDijsktraIdx(int idx, int tnum) { dijsktraIdx[tnum] = idx; }
	int getDijsktraIdx(int tnum) { return dijsktraIdx[tnum]; }

	bool isAdjacent(int other)
	{
		throw 1;
		return outgoing.find(other) != outgoing.end();
	}

	int outDegree() const
	{
		return outgoing.size();
	}

	void send(int other, double cost) {
		outgoing.insert(std::pair<int, double> { other, cost });
	}
	void receive(int other, double cost) {
		incoming.insert(std::pair<int, double> { other, cost });
	}

	const std::map<int, double>& outs() const
	{
		return outgoing;
	}
	const std::map<int, double>& ins() const
	{
		return incoming;
	}

	double getCostTo(int other, bool forward)
	{
		if (forward)
			return outgoing.find(other)->second;
		else
			return incoming.find(other)->second;
	}

	void setLabelled(int tnum) { labelled[tnum] = true; }
	bool isLabelledByOtherThread(int tnum)
	{
		for (int i=0;i<NUM_THREADS;i++)
			if (tnum != i && labelled[i])
				return true;
		return false;
	}
};


#endif /* SRC_NODE_H_ */
