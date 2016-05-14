/*
 * dfs.cpp
 *
 *  Created on: Apr 29, 2016
 *      Author: thallock
 */

#include "dfs.h"

#include <set>
#include <limits>

void depth_first_search(
		Graph& graph,
		Path& cPath,
		Path& bPath,
		int cNode,
		int t,
		double cCost,
		double& bCost,
		std::set<int>& visited)
{
	if (t == cNode)
	{
		if (cCost < bCost)
		{
			bCost = cCost;
			bPath = cPath;
		}
		return;
	}
	if (cCost >= bCost)
		return;

	NodeData& node = graph.getNode(cNode);

	auto end = node.outs().end();
	for (auto it = node.outs().begin(); it != end; ++it)
	{
		int nextNode = it->first;
		if (visited.find(nextNode) != visited.end())
			continue;

		visited.insert(nextNode);
		cPath.add(nextNode);
		depth_first_search(graph, cPath, bPath, nextNode, t, cCost + it->second, bCost, visited);
		if (cPath.pop() != nextNode)
			throw 1;
		visited.erase(nextNode);
	}
}


double depth_first_search(Graph& graph, Path& bPath, int s, int t)
{
	double bCost = std::numeric_limits<double>::max();
	Path cPath;

	cPath.add(s);

	std::set<int> visited;

	depth_first_search(graph, cPath, bPath, s, t, 0.0, bCost, visited);

	return bCost;
}
