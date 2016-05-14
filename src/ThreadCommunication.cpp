
#include "ThreadCommunication.h"


#include <limits>

ThreadCom::ThreadCom() :
	barrier{3},
	stop{false},
	mtx{},
	minCost {std::numeric_limits<double>::infinity()},
	minPath{} {}

ThreadCom::~ThreadCom() {}

void ThreadCom::startSearch()
{
	barrier.block(0);
}
void ThreadCom::stopSearch()
{
	stop = true;
	barrier.block(1);
}
bool ThreadCom::shouldStop()
{
	return stop;
}
void ThreadCom::stopMerge()
{
	barrier.block(2);
}

bool ThreadCom::updateMinCost(double newMinCost, Path *p)
{
	if (newMinCost >= minCost)
		return false;

	mtx.lock();

	if (newMinCost >= minCost)
		return false;

	minCost = newMinCost;
	minPath = p;

	mtx.unlock();
	return true;
}

void ThreadCom::runThreads()
{
    barrier.block(0); // start searching...
    barrier.block(1); // stop searching...
    barrier.block(2); // stop merging...
}



//
//ThreadCom::ThreadCom() :
//	mtx{},
//	cv{},
//	count{0},
//	ready{false},
//	stop {false}
//{
//	for (int i=0;i<NUM_THREADS;i++)
//	{
//		heaps[i] = nullptr;
//	}
//}
//
//
//ThreadCom::~ThreadCom() {}
//
//bool ThreadCom::shouldStop()
//{
//	return stop;
//}
//
//void ThreadCom::quit(int tnum, BinaryHeap *heap)
//{
//    std::unique_lock<std::mutex> lck(mtx);
//    stop = true;
//    heaps[tnum] = heap;
//    cv.notify_all();
//    count--;
//}
//
//void ThreadCom::start()
//{
//    std::unique_lock<std::mutex> lck(mtx);
//    cv.wait(lck, [this](){ return ready; });
//    count++;
//}
//
//void ThreadCom::runThreads()
//{
//    std::unique_lock<std::mutex> lck(mtx);
//    ready = true;
//    cv.notify_all();
//    cv.wait(lck, [this](){ return stop && count == 0; });
//}
