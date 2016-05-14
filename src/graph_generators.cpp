/*
 * graph_generators.cpp
 *
 *  Created on: Apr 30, 2016
 *      Author: thallock
 */

#include "graph_generators.h"

#include "Graph.h"

#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <iomanip>

void verify_graph(const std::string& inFile)
{
	std::cout << "verifying... ";
	std::cout.flush();

	std::ifstream instream{inFile};

	int nR, mR;
	instream >> nR;
	instream >> mR;

	int n = 0;
	int m = 0;

	while (!instream.eof())
	{
		int start, stop;
		double cost;

		instream >> start;
		if (instream.eof())
			break;
		instream >> stop;
		instream >> cost;

		if (start > n)
			n = start;
		if (stop  > n)
			n = stop;
		m++;
	}

	instream.close();
	
	if (n+1 != nR || m != mR)
	{
		std::cout << "Mismatch: " << n+1 << "=/=" << nR << " or " << m << "=/=" << mR << std::endl;
		throw 1;
	}

	std::cout << "done" << std::endl;
}

void read_nm(const std::string& inFile, int& n, int& m)
{
	std::ifstream instream{inFile};

	n = 0;
	m = 0;

	while (!instream.eof())
	{
		int start, stop;
		double cost;

		instream >> start;
		instream >> stop;
		instream >> cost;

		if (start > n)
			n = start;
		if (stop  > n)
			n = stop;
		m++;
	}

	n = n + 1;
	instream.close();
}

void prependNM(const std::string& inFile, const std::string& outFile, int n, int m)
{
	std::cout << "prepending n,m... ";
	std::cout.flush();

	std::ofstream outstream(outFile);
	outstream << std::setprecision(11) << std::scientific;

	outstream << std::setw(4) << n << ' ' << std::setw(4) << m << '\n';

	std::ifstream instream{inFile};
	for (int i=0;i<m;i++)
	{
		int start, stop;
		double cost;

		instream >> start;
		if (instream.eof())
			break;
		instream >> stop;
		instream >> cost;

		outstream << std::setw(4) << start <<  ' ';
		outstream << std::setw(4) << stop  <<  ' ';
		outstream << std::setw(4) << cost  << '\n';
	}

	instream.close();
	outstream.close();

	std::cout << "done." << std::endl;
}

void prependNM(const std::string& inFile, const std::string& outFile)
{
	int n, m;
	read_nm(inFile, n, m);
	prependNM(inFile, outFile, n, m);
}




void generate_long_graph(
		const std::string& outFile,
		const int width,
		const int stages,
		const double percent,
		const double lookBackRatio)
{
	std::string tmpFile = outFile + ".tmp";
	int m = 0;
	int n = 0; // start and stop nodes are 0 and 1

	{
		int *current = new int[width];

		for (int i = 0; i < width; i++)
			current[i] = i;

		std::ofstream outstream { tmpFile };
		outstream << std::setprecision(11) << std::scientific;

		// Add nodes from 0 to the first stage...
		n += 2;
		n += width;
		m += width;
		for (int i = 0; i < width; i++)
			outstream << std::setw(4) << 0 << ' ' << std::setw(4) << (2 + i) << " " << (rand() / (double) RAND_MAX) << '\n';

		outstream << "\n\n";

		std::vector<std::pair<int, int> > edges;

		const int lookBack = (int) (lookBackRatio * width);
		for (int i = 0; i < stages; i++)
		{
			// Connect nodes in each stage...
			n += width;
			int prevBegin = n - 2 * width;
			int currBegin = n - 1 * width;

			std::random_shuffle(&current[0], &current[width]);

			// ensure there is a path...
			m += width;
			for (int i = 0; i < width; i++)
				outstream << std::setw(4) << (prevBegin + i) << ' ' << std::setw(4) << (currBegin + current[i]) << ' ' << (rand() / (double) RAND_MAX) << '\n';
			outstream << '\n';

			// Make all possible edges to be added...
			edges.clear();
			for (int b = currBegin - lookBack; b<currBegin; b++)
				for (int e=currBegin; e<currBegin+width; e++)
				{
					if (b < 0) continue;
					edges.push_back(std::pair<int, int>{b, e});
				}

			unsigned int numEdges = (int) (percent * edges.size());
			if (numEdges > edges.size())
				numEdges = edges.size();

			std::random_shuffle(edges.begin(), edges.end());

			m += numEdges;
			auto it = edges.begin();
			for (unsigned int j = 0; j<numEdges;j++, ++it)
				outstream << std::setw(4) << it->first << ' ' << std::setw(4) << it->second << ' ' << (rand() / (double) RAND_MAX) << '\n';

//			while (edges.size() < numEdges) // ignoring count of edges already added to stay connected
//			{
//				int tail = currBegin + (int) (lookBack * (rand() / (double) RAND_MAX)) - lookBack;
//				int head = currBegin + (int) (width * (rand() / (double) RAND_MAX));
//				if (tail < 0) tail = 0;
//				edges.(std::pair<int, int>{tail, head});
//				std::cout << edges.size() << "/" << numEdges << " edges." << std::endl;
//			}
//
//			const auto e = edges.end();
//			for (auto it = edges.begin(); it != e; ++it)

			outstream << "\n\n";

			std::cout << i << "/" << stages << " stages complete." << std::endl;
		}

		m += width;
		for (int i=0;i<width;i++)
			outstream << std::setw(4) << (n - width + i) << ' ' << std::setw(4) << 1 << ' ' << (rand() / (double) RAND_MAX) << '\n';

		delete[] current;
		outstream.flush();
		outstream.close();
	}

	prependNM(tmpFile, outFile, n, m);

	verify_graph(outFile);
}


void generate_random_graph(const std::string& outfile, int size, double frac)
{
//	Graph graph{size};
//	graph.randomlyAdd((int) (frac * size * size / (double) 2));
//	std::ofstream outstream { outfile };
//	graph.write(outstream);
//	outstream.close();

	{
		std::vector<std::pair<int, int> > edges;
		std::cout << "creating all edges" << std::endl;

		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				if (i != j)
					edges.push_back(std::pair<int, int> { i, j });

		std::cout << "edges shuffling" << std::endl;
		std::random_shuffle(edges.begin(), edges.begin());

		unsigned int numEdges = (int) (edges.size() * frac);
		if (numEdges > edges.size())
			numEdges = edges.size();

		std::ofstream outstream { outfile };
		outstream << std::setprecision(11) << std::scientific;
		outstream << std::setw(4) << size << ' ';
		outstream << std::setw(4) << numEdges << '\n';

		auto it = edges.begin();
		for (unsigned int i = 0; i < numEdges; i++, ++it)
			outstream << std::setw(4) << it->first << ' ' << std::setw(4) << it->second << ' ' << (rand() / (double) RAND_MAX) << '\n';

		outstream.close();
	}

	verify_graph(outfile);
}


void generate_complete_graph(const std::string& outfile, int size)
{
	std::ofstream outstream { outfile };
	outstream << std::setprecision(11) << std::scientific;
	outstream << std::setw(4) << size << ' ';
	outstream << std::setw(4) << size * (size-1) << '\n';

	for (int i=0;i<size;i++)
		for (int j=0;j<size;j++)
			if (i!=j)
				outstream << std::setw(4) << i << ' ' << std::setw(4) << j << ' ' << (rand() / (double) RAND_MAX) << '\n';

	outstream.close();

	verify_graph(outfile);
}

