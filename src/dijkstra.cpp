/*
 * dijkstra.cpp
 *
 *  Created on: Apr 29, 2016
 *      Author: thallock
 */

#include "dijkstra.h"

#include "BinaryHeap.h"
#include "ThreadCommunication.h"

#include <thread>
#include <chrono>





#define STOP_AS_SOON_AS_POSSIBLE 1




class ThreadArgs
{
public:
	ThreadCom& com;
	Graph& graph;
	int start;
	int stop;
	bool forward;
	int tnum;
	bool found;
	int hitNode;
	BinaryHeap heap;
	Path p;

	ThreadArgs(
			ThreadCom& com,
			Graph& graph,
			int s,
			int t,
			int tnum) :
				com{com},
				graph{graph},
				start{s},
				stop{t},
				forward{tnum == 0 ? true : false},
				tnum{tnum},
				found{false},
				hitNode{-1},
				heap{tnum, graph.getN()},
				p{}
	{}

	~ThreadArgs() {}
};













void search(ThreadArgs& args)
{
	args.com.startSearch();

	int s, t;
	if (args.tnum == 0)
	{
		s=args.start;
		t=args.stop;
	}
	else
	{
		s=args.stop;
		t=args.start;
	}

	NodeData *seeking = &args.graph.getNode(t);
	args.graph.getNode(s).setCost(0, args.tnum);

	args.heap.add(args.graph.getNode(s));

	while (args.heap.getSize() > 0)
	{
		if (args.com.shouldStop())
		{
//			if (args.tnum) std::cout << '\t';
//		    std::cout << "Thread " << args.tnum << "Sure... I will stop! " << std::endl;

			args.com.stopSearch();
			return;
		}

		NodeData *node = args.heap.pop();

//		std::cout << "Looking at node " << node->index() << std::endl;

//		if (args.tnum) std::cout << '\t';
//		std::cout << "Thread " << args.tnum << ": Just popped " << node->index() << std::endl;
//	    std::this_thread::sleep_for (std::chrono::milliseconds(rand() % 200));
//		if (args.tnum) std::cout << '\t';
//	    std::cout << "Thread " << args.tnum << ": Done sleeping... " << std::endl;


		node->setLabelled(args.tnum);
		if (node == seeking)
		{
//			if (args.tnum) std::cout << '\t';
//		    std::cout << "Thread " << args.tnum << ": I made it all the way!!! " << std::endl;

			args.found = true;
			if (STOP_AS_SOON_AS_POSSIBLE)
			{
				args.com.stopSearch();
				return;
			}
		}

		auto daList = args.forward ? node->outs() : node->ins();
		auto e = daList.end();
		for (auto i = daList.begin(); i != e; i++) {
			NodeData& other = args.graph.getNode(i->first);
			double nCost = node->getCost(args.tnum) + i->second;

			if (nCost >= other.getCost(args.tnum))
				continue;
			other.setCost(nCost, args.tnum);
			other.setPrev(node, args.tnum);
			args.heap.updateNode(other);
		}

		if (node->isLabelledByOtherThread(args.tnum))
		{
//			if (args.tnum) std::cout << '\t';
//		    std::cout << "Thread " << args.tnum << ": HIT ALREADY LABELLED NODE" << std::endl;

		    args.hitNode = node->index();
			args.com.stopSearch();
			return;
		}
	}

	if (STOP_AS_SOON_AS_POSSIBLE)
	{
		std::cout << "Graph is not connected!!!" << std::endl;
		throw 1;
	}
	else
	{
		args.com.stopSearch();
	}
}












void addPath(Path& p, NodeData *node, int stop, int direction)
{
	int idx = node->index();
	while (idx != stop)
	{
		node = node->getPrev(direction);
		if (node == nullptr)
		{
			std::cout << "Null next!!!!" << std::endl;
			std::cout << "So far: " << std::endl;
			p.print(std::cout) << std::endl;
			throw 1;
		}
		p.add(idx = node->index());
	}
}
void setPath(Path& path, NodeData *node, int s, int t)
{
	path.clear();
	addPath(path, node, s, 0);
	path.reverse();
	path.add(node->index());
	addPath(path, node, t, 1);
}

void checkNode(ThreadArgs& args, NodeData *node)
{
	if (!node->isLabelledByOtherThread(args.tnum))
		return;

	double cost = node->getCost(args.tnum) + node->getOtherCost(args.tnum);
	if (!args.com.updateMinCost(cost, &args.p))
		return;

	setPath(args.p, node, args.start, args.stop);
//	std::cout << "Found the following path: " << cost << "=" << args.p.getCost(args.graph) << "\n";
//	args.p.print(std::cout);
//	std::cout << std::endl;
//	if (!numbers_are_the_same(cost, args.p.getCost(args.graph)))
//	{
//		std::cout << "Already doesn't match" << std::endl;
//		throw 1;
//	}
//	if (cost != args.p.getCost(args.graph))
//	{
//		std::cout << "That was it." << std::endl;
//		throw 1;
//	}
}

void merge(ThreadArgs& args)
{
	if (args.found)
	{
		args.com.stopMerge();
		return;
	}

	if (args.hitNode >= 0)
		checkNode(args, &args.graph.getNode(args.hitNode));

	const int size = args.heap.getSize();
	for (int i=0; i<size; i++)
	{
		checkNode(args, args.heap.getNode(i));
	}

	args.com.stopMerge();
}


void threadMethod(ThreadArgs& args)
{
	search(args);
	merge(args);
}



void emptyMethod(ThreadArgs& args)
{
	args.com.runThreads();
}


bool find_minimal_path(Graph& graph, Path& p, int s, int t, bool parallel)
{
	ThreadCom com{};
	ThreadArgs args1 { com, graph, s, t, 0 };
	ThreadArgs args2 { com, graph, s, t, 1 };

    std::thread t1{           threadMethod,               std::ref(args1)};
    std::thread t2{parallel ? threadMethod : emptyMethod, std::ref(args2)};

    com.runThreads();

    t1.join();
    t2.join();

    if (args1.found)
    {
    	setPath(p, &graph.getNode(t), s, t);
//    	std::cout << "Thread " << 0 << " found the whole path!!!" << std::endl;
    	p.print(std::cout) << std::endl;
    }
    else if (args2.found)
    {
    	setPath(p, &graph.getNode(s), s, t);
//    	std::cout << "Thread " << 1 << " found the whole path!!!" << std::endl;
    	p.print(std::cout) << std::endl;
    }
    else
    {
    	com.setMinPath(p);
    }

    return true;
}










//
//void addPath(Graph& g, Path& p, int s, int t, int tnum)
//{
//	if (s == t)
//	{
//		p.add(s);
//		return;
//	}
//
//	NodeData *prev = g.getNode(t).getPrev(tnum);
//	if (prev == nullptr)
//		std::cout << "Null previous!!!!" << std::endl;
//	else
//		addPath(g, p, s, prev->index(), tnum);
//	p.add(t);
//}
//
//void addForwardPath(Path& p, NodeData *node, int start)
//{
//	int idx = node->index();
//	if (idx != start)
//	{
//		NodeData *prev = node->getPrev(0);
//		if (prev == nullptr)
//		{
//			std::cout << "Null previous!!!!" << std::endl;
//			throw 1;
//		}
//		addForwardPath(p, prev, start);
//	}
//	p.add(idx);
//
//	int idx;
//	do
//	{
//		node = node->getPrev(0);
//		if (node == nullptr)
//		{
//			std::cout << "Null next!!!!" << std::endl;
//			throw 1;
//		}
//		p.add(idx = node->index());
//	} while (idx != start);
//	p.reverse();
//}
