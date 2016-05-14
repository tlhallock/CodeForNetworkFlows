
#include "Barrier.h"

Barrier::Barrier(int n) :
		mtx{},
		cv{},
		barrier{0},
		count{n},
		numThreads{n} {}

Barrier::~Barrier() {}

void Barrier::block(int barrierNum)
{
	if (barrierNum != barrier)
	{
		std::cout << "Barrier issue." << std::endl;
		throw 1;
	}

    std::unique_lock<std::mutex> lck(mtx);

    if (--count == 0)
    {
    	count = numThreads;
    	barrier++;
    	cv.notify_all();
    }
    else
    {
    	cv.wait(lck, [this, barrierNum]() {return barrier != barrierNum; });
    }
}
