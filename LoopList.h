#ifndef LOOP
#define LOOP
#include <thread>
#include <iostream>
#include <vector>

class ThreadPool {
	std::thread* THREADS;
	bool* Work;
	int NumThreads = 0;
	int AtualIndex = 0;
	std::vector<void (*)()> Queue;
	std::vector<void (*)()> Workersqueu;
public:
	bool IsWorking = false;
	void SetThread(int id);
	ThreadPool(int numThreads);
	~ThreadPool();
	void AllocFunct(void (*f)());
	void RunQueue();


};
#endif // !LOOP

