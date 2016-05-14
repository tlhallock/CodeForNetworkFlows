/*
 * test_bnh.cpp
 *
 *  Created on: Apr 29, 2016
 *      Author: thallock
 */

#include "BinaryHeap.h"
#include "Graph.h"
#include "Barrier.h"

#include "dfs.h"
#include "dijkstra.h"
#include <sys/time.h>


#include "constants.h"

#include "graph_generators.h"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <thread>

void printStuff(Barrier& b)
{
	for (int i=0;i<10;i++)
	{
		std::cout << "Printing " << i << std::endl;
		b.block(i);
	}
}
void testBarrier()
{
	Barrier barrier {4};
	std::thread t1{printStuff, std::ref(barrier)};
	std::thread t2{printStuff, std::ref(barrier)};
	std::thread t3{printStuff, std::ref(barrier)};
	std::thread t4{printStuff, std::ref(barrier)};

	t1.join(); t2.join(); t3.join(); t4.join();
}







void testBinaryHeap()
{
	constexpr int size = 0;
	BinaryHeap heap { size };

	heap.print(std::cout);

	int key = 0;
	int tnum = 0;

	for (int j=0;j<5000;j++)
	{
		int nAdd = (int) (10 * (rand() / (double) RAND_MAX));
		std::cout << "===== Adding " << nAdd << " total" << std::endl;

		while (/* heap.getSize() < size && */ nAdd --> 0)
		{
			NodeData *data = new NodeData{};
			data->setIndex(key++);
			data->setCost(rand() / (double) RAND_MAX, tnum);
			heap.dbgCheckHeap();
			heap.prettyPrint(std::cout);
		}

		int nRem = (int) (10 * (rand() / (double) RAND_MAX));
		std::cout << "===== Removing " << nRem << std::endl;

		double prev = -2;
		while (heap.getSize() > 0 && nRem --> 0)
		{
			NodeData *data = heap.pop();
			heap.prettyPrint(std::cout);
			if (prev > data->getCost(tnum))
			{
				std::cout << "Not good." << std::endl;
				throw 1;
			}
			prev = data->getCost(tnum);
			heap.dbgCheckHeap();
		}
//		std::cout << "\n" << std::endl;
	}

	while (heap.getSize() > 0)
	{
		delete heap.pop();
	}

//	for (int i = 0; i < 10; i++) {
//		heap.add(20 - i, i);
//		heap.print(std::cout);
//	}
}






















void testGraph()
{
	Graph *graph = new Graph{5};
	graph->randomlyAdd(10);

	graph->write(std::cout);

	delete graph;
}

void writeSmallGraphs()
{
	generate_long_graph(
			"long_graph.txt", // output file
			3, // width
			5, // stages
			.5, // percent other edges to add
			1.5 // look back ratio
			);
	generate_random_graph("random_graph.txt", 10, .5);
	generate_complete_graph("complete_graph.txt", 10);
}

void writeGraphs()
{
	generate_long_graph(
			"long_graph.txt", // output file
			10, // width
			20, // stages
			.25, // percent other edges to add
			1.5 // look back ratio
			);
	generate_random_graph("random_graph.txt", 150, .5);
	generate_complete_graph("complete_graph.txt", 10);
}
void writeBigGraphs()
{
	std::cout << "Writing graphs." << std::endl;
	generate_long_graph(
			"long_graph.txt", // output file
			25, // width
			10000, // stages
			.25, // percent other edges to add
			1.0 // look back ratio
			);
	std::cout << "1/3" << std::endl;
	generate_random_graph("random_graph.txt", 10000, .01);
	std::cout << "2/3" << std::endl;
	generate_complete_graph("complete_graph.txt", 1500);
	std::cout << "3/3" << std::endl;
}

















void testMethods(const std::string& filename, int s, int t, std::ostream&output, bool runDFS = false)
{
	Graph *g;
	{
		verify_graph(filename);

		std::cout << "Reading graph " << filename << std::endl;
		std::ifstream instream {filename};
		g = readGraph(instream);
		instream.close();
		std::cout << "Read: " << filename << ":" << std::endl;
	}

//	std::list<int> oList;
//	createOptimalPath(oList);
//	Path optimalPath;
//	optimalPath.assign(oList);
//
//	std::cout << "There is a path of length " << optimalPath.getCost(*g) << "." << std::endl;
//	{
//		std::ofstream otest {"test.sh"};
//
//		auto daEnd = oList.end();
//		auto daIt = oList.begin();
//		int prevNode = *daIt;
//		for (++daIt; daIt != daEnd; ++daIt)
//		{
//			otest << "a=$(grep " << prevNode << " arcs.csv | grep " << *daIt << ")" << std::endl;
//			otest << "[[ \"$a\" ]] || echo Missing " << std::endl;
//			prevNode = *daIt;
//		}
//
//		if (1) return;
//		otest.close();
//	}




	std::clock_t start;


//
//	int s = 53481;
//	int t = 31120; //31120; // ; //31120; //;// 83534; // rand() % 4000;
	std::cout << t << std::endl;


	// RUN DEPTH FIRST SEARCH


	std::cout << "\tDFS:" <<std::endl;
	Path pDfs;
	double dCost;
	if (runDFS) {
		start = std::clock();
		dCost = depth_first_search(*g, pDfs, s, t);
		auto duration = (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000) ;
		std::cout << "\t\tTime: " << duration << " ms" << std::endl;
	}
	if (runDFS && dCost != pDfs.getCost(*g))
		throw 1;
	if (runDFS) std::cout << "\t\tLength: " << pDfs.length() << std::endl;
	if (runDFS) std::cout << "\t\tMinimum cost: " << dCost << std::endl;
	if (runDFS) pDfs.print(std::cout);





	// RUN PARALLEL DIJSKTRA
	g->reset();


	std::cout << "\tBFS:" <<std::endl;
	Path pBfs;
	double bCost;
	{
//		struct timeval start_C,end_C;
//		int duration_musec;
//		gettimeofday(&start_C,NULL);
		start = std::clock();
		find_minimal_path(*g, pBfs, s, t);
//		gettimeofday(&end_C,NULL);
//		duration_musec =
//				((end_C.tv_sec * 1000000 + end_C.tv_usec)
//						  - (start_C.tv_sec * 1000000 + start_C.tv_usec));
//		fprintf(stderr,"Duration musec:%d\n",duration_musec);

		auto duration = (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000) ;
		std::cout << "\t\tTime: " << duration << " ms" << std::endl;

		output << pBfs.length() << "\t" << duration << "\t";
	}

	bCost = pBfs.getCost(*g);
	std::cout << "\t\tLength: " << pBfs.length() << std::endl;
	std::cout << "\t\tMinimum cost: " << bCost << std::endl;
	pBfs.print(std::cout);

	g->checkOptimality();

//
//	std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n" << std::endl;
//
//	pBfs.debug(g);
//
//	std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n" << std::endl;

	if (runDFS && !numbers_are_the_same(dCost, bCost))
	{
		std::cout << "Costs were not the same!!!" << std::endl;
 		throw 1;
	}

	if (runDFS && !(pDfs == pBfs))
	{
		std::cout << "Paths did not match!!!" << std::endl;
	}





	// RUN SINGLE DIJKSTRA
	g->reset();


	std::cout << "\tBFS (Single):" <<std::endl;
	Path pBfsS;
	double bCostS;
	{
		start = std::clock();
		find_minimal_path(*g, pBfsS, s, t, false);
		auto duration = (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000) ;
		std::cout << "\t\tTime: " << duration << " ms" << std::endl;

		output << duration << "\n";
	}

	bCostS = pBfsS.getCost(*g);
	std::cout << "\t\tLength: " << pBfsS.length() << std::endl;
	std::cout << "\t\tMinimum cost: " << bCostS << std::endl;
	pBfsS.print(std::cout);



	g->checkOptimality();

//	if (!numbers_are_the_same(bCostS, bCost))
//	{
//		std::cout << "Costs were not the same!!!" << std::endl;
// 		throw 1;
//	}
//
//	if (!(pBfsS == pBfs))
//	{
//		std::cout << "Paths did not match!!!" << std::endl;
//	}












	delete g;
}



int main(int argc, char ** argv) {
//	srand(time(NULL));
	auto seed = time(NULL);
	std::cout << "Seeding with " << seed << std::endl;
	srand(seed);
	
//	srand(1463011720);

//	testBarrier();
//	if (1) return 0;

//	writeSmallGraphs();
//	writeGraphs();
	writeBigGraphs();

//	if (1) return 0;
	
	std::ofstream output{"alltimes.txt"};

	std::cout << "Running algorithms." << std::endl;

//	testMethods("mine.txt", 53481, 31120  , output);
//	testMethods("mine.txt", 53481, 34113  , output);
//	testMethods("mine.txt", 53481, 35703  , output);
//	testMethods("mine.txt", 53481, 41380  , output);
//	testMethods("mine.txt", 53481, 60886  , output);
//	testMethods("mine.txt", 53481, 66942  , output);
//	testMethods("mine.txt", 53481, 83534  , output);
//	testMethods("mine.txt", 53481, 92507  , output);
//	testMethods("mine.txt", 53481, 104538 , output);
//	testMethods("mine.txt", 53481, 108863 , output);
//	testMethods("mine.txt", 53481, 123200 , output);
//	testMethods("mine.txt", 53481, 130499 , output);
//	testMethods("mine.txt", 53481, 137175 , output);
//	testMethods("mine.txt", 53481, 171424 , output);
//	testMethods("mine.txt", 53481, 190602 , output);
//	testMethods("mine.txt", 53481, 210717 , output);
//	testMethods("mine.txt", 53481, 232786 , output);
//	testMethods("mine.txt", 53481, 264924 , output);
//	testMethods("mine.txt", 53481, 290329 , output);
//	testMethods("mine.txt", 53481, 299395 , output);
//	testMethods("mine.txt", 53481, 320131 , output);





	testMethods("long_graph.txt", 0, 1, output);
 	testMethods("random_graph.txt", 0, 1, output);
 	testMethods("complete_graph.txt", 0, 1, output);

	return 0;
}

