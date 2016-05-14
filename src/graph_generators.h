/*
 * graph_generators.h
 *
 *  Created on: Apr 30, 2016
 *      Author: thallock
 */

#ifndef SRC_GRAPH_GENERATORS_H_
#define SRC_GRAPH_GENERATORS_H_

#include <string>

void generate_long_graph(
		const std::string& outFile,
		const int width,
		const int stages,
		const double percent=.25,
		const double lookBackRatio=1.0);

void generate_random_graph(const std::string& outfile, int size, double frac);

void generate_complete_graph(const std::string& outfile, int size);

void verify_graph(const std::string& inFile);


#endif /* SRC_GRAPH_GENERATORS_H_ */
