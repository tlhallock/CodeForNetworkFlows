/*
 * ThreadCommunication.h
 *
 *  Created on: May 11, 2016
 *      Author: thallock
 */

#ifndef SRC_THREADCOMMUNICATION_H_
#define SRC_THREADCOMMUNICATION_H_

#include <iostream>
#include <mutex>

#include "BinaryHeap.h"
#include "constants.h"
#include "Barrier.h"
#include "Path.h"

class ThreadCom
{
	Barrier barrier;

	bool stop;


	std::mutex mtx;
	double minCost;
	Path *minPath;

public:
	ThreadCom();
	~ThreadCom();

	void startSearch();
	void stopSearch();
	bool shouldStop();

	void stopMerge();
	bool updateMinCost(double newMinCost, Path *p);
	void runThreads();

	void setMinPath(Path& p)
	{
		if (minPath == nullptr)
			return;
	    p = *minPath;
	}
};

#endif /* SRC_THREADCOMMUNICATION_H_ */

