/*
 * dijkstra.h
 *
 *  Created on: Apr 29, 2016
 *      Author: thallock
 */

#ifndef SRC_DIJKSTRA_H_
#define SRC_DIJKSTRA_H_

#include "Path.h"
#include "Graph.h"

bool find_minimal_path(Graph& graph, Path& p, int s, int t, bool parallel=true);

#endif /* SRC_DIJKSTRA_H_ */
