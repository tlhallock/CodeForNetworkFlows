/*
 * Graph.h
 *
 *  Created on: Apr 29, 2016
 *      Author: thallock
 */

#ifndef SRC_GRAPH_H_
#define SRC_GRAPH_H_


#include "UnionFind.h"

#include "Node.h"

#include <map>
#include <vector>
#include <iostream>
#include <limits>

class Graph {
	int n;
	std::vector<NodeData> nodes;

public:
	Graph(int n);
	virtual ~Graph();

	void addEdge(int i1, int i2, double cost);

	void resize(int newN);
	std::ostream& write(std::ostream& out) const;

	int getM() const;
	int getN() const { return n; }

	bool adjcent(int i1, int i2);

	void randomlyAdd(int m);

	NodeData& getNode(int node) { return nodes[node]; }

	void reset();

	void checkOptimality()
	{
		for (int i=0;i<n;i++)
		{
			NodeData& node = getNode(i);
			// Test forward..
			int tnum = 0;
			if (node.isLabelledByOtherThread(tnum == 0 ? 1 : 0))
			{
				double thisCost = node.getCost(tnum);

				const auto e = node.ins().end();
				for (auto it = node.ins().begin(); it != e; ++it)
				{
					double otherCost = getNode(it->first).getCost(tnum);
					double edgeCost = it->second;
					if (otherCost + edgeCost < thisCost)
					{
						std::cout << "Error with label to " << i << " from " << it->first << std::endl;
						std::cout << "Costs " << otherCost << " + " << edgeCost << " > " << thisCost << std::endl;
						throw 1;
					}
				}
			}

			tnum = 1;
			if (node.isLabelledByOtherThread(tnum == 0 ? 1 : 0))
			{
				double thisCost = node.getCost(tnum);

				const auto e = node.outs().end();
				for (auto it = node.outs().begin(); it != e; ++it)
				{
					double otherCost = getNode(it->first).getCost(tnum);
					double edgeCost = it->second;
					if (otherCost + edgeCost < thisCost)
					{
						std::cerr << "Error with label to " << i << " from " << it->first << std::endl;
						std::cerr << "Costs " << otherCost << " + " << edgeCost << " > " << thisCost << std::endl;
						throw 1;
					}
				}
			}
		}
	}

};


Graph * readGraph(std::istream& in);

#endif /* SRC_GRAPH_H_ */
