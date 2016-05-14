/*
 * dfs.h
 *
 *  Created on: Apr 29, 2016
 *      Author: thallock
 */

#ifndef SRC_DFS_H_
#define SRC_DFS_H_

#include "Graph.h"
#include "Path.h"

double depth_first_search(Graph& graph, Path& path, int s, int t);

#endif /* SRC_DFS_H_ */
