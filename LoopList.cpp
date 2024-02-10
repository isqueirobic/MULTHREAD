#include "LoopList.h"


	void ThreadPool::SetThread(int id) {
		void (*f)(); // cath fuctions
		while (true) { // keep the thread awake
			if (Work[id] == true && !Queue.empty()) { // see if can work and if our Queue is not empyt
				 f = Queue.back(); // get function form the qeue
				 if (f != nullptr) {
					 f(); // do it my soon
				 }
				
				 Queue.pop_back(); // we dont need this function on our queue after we finish it
				 Work[id] = false; // me no wana work anymo
			}
		}
	}

	ThreadPool::ThreadPool(int numThreads) { // init 
		NumThreads = numThreads;
		Work = new bool[NumThreads];
		THREADS = new std::thread[NumThreads];
		for (int i = 0; i <= NumThreads-1; i++) { // set threads to keep awake
			Work[i] = false;
			THREADS[i] = std::thread(&ThreadPool::SetThread, this, i);
		}
	}

	ThreadPool::~ThreadPool() { // destroy 
		Work = nullptr;
		//THREADS = new std::thread[NumThreads];
		for (int i = 0; i <= NumThreads-1; i++) {
			THREADS[i].join();
		}
		Queue.clear();
		Queue.~vector();
	}

	void ThreadPool::AllocFunct(void (*f)()) {
		Queue.push_back(f);
	}

	void ThreadPool::RunQueue() {
		int atualsize = Queue.size();
		IsWorking = true;
		for (int i = 0; i <= atualsize-1; i++) {
			int t = 0;
			while (true) {
				if (Work[t] == false) {
					Work[t] = true;
					break;
				}
				
				if (t > NumThreads) {
					t = 0;
				}
				else {
					t++;
				}

				if (i >= atualsize) {
					break;
				}
			}
		}
		bool h = true;
		while (h) {
			h = false;
			for (int i = 0; i <= NumThreads; i++) {
				if (Work[i] == true) {
					h = true;
				}
			}
		}
		
		Queue.clear();
		IsWorking = false;
	}
