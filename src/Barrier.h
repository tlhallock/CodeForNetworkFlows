/*
 * ThreadCommunication.h
 *
 *  Created on: May 11, 2016
 *      Author: thallock
 */

#ifndef BARRIER_H_
#define BARRIER_H_

#include <iostream>
#include <mutex>
#include <condition_variable>

#include "BinaryHeap.h"
#include "constants.h"

class Barrier
{
private:
	std::mutex mtx;
	std::condition_variable cv;

	int barrier;
	int count;
	int numThreads;

public:
	Barrier(int n);
	~Barrier();

	void block(int barrierNum);
};

#endif /* BARRIER_H_ */

