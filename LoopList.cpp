#include "LoopList.h"


	void ThreadPool::SetThread(int id) {
		void (*f)(); // cath fuctions
		while (true) { // keep the thread awake
			if (Work[id] == true) { // see if can work and if our Queue is not empyt
				 f = Workersqueu.at(id); // get function form the qeue
				 if (f != nullptr) {
					 f(); // do it my soon
				 }
				 Work[id] = false; // me no wana work anymo
			}

		}
	}

	ThreadPool::ThreadPool(int numThreads) { // init 
		NumThreads = numThreads;
		Work = new bool[NumThreads];
		THREADS = new std::thread[NumThreads];
		Workersqueu.resize(numThreads);
		for (int i = 0; i <= NumThreads-1; i++) { // set threads to keep awake
			Work[i] = false;
			THREADS[i] = std::thread(&ThreadPool::SetThread, this, i);
		}
	}

	ThreadPool::~ThreadPool() { // destroy 
		delete[] Work;
		//THREADS = new std::thread[NumThreads];
		for (int i = 0; i <= NumThreads-1; i++) {
			THREADS[i].join();
		}
		delete[] THREADS;
		Queue.clear();
		Queue.~vector();
	}

	void ThreadPool::AllocFunct(void (*f)()) { // aloc our function if u asking
		Queue.push_back(f); // put on the last index of our vector if u may ask
	}

	void ThreadPool::RunQueue() {
		int atualsize = Queue.size(); // get the number of fucntions we have to do
		IsWorking = true; // just put here for good pratice
		for (int i = 0; i <= atualsize-1; i++) { // remenber we start couting on zero so that's why the -1
			int t = 0; // our beloved index to loop troght our threads
			while (true) {
				if (Work[t] == false) { // set our poor worker to work or not if he is alredy working
					Workersqueu.insert(Workersqueu.begin() + t, Queue.back()); //get the function or thing to do
					Queue.pop_back(); // we alredy get it byebye
					Work[t] = true; // work
					break; // we got the thread working then we dont need muck around here anymopre
				}
				
				if (t > NumThreads) { // oh fuck! all threads are working, so we loop troght then again if there is any mf that can work
					t = 0; // rest our index
				}
				else {
					t++; // add to the index 
				}

				if (i >= atualsize) { // we alredy work to much i no wana work anymore(when "i" rech his limit) does nothing if u ask me
					break;
				}
			}
		}
		bool h = true; // gotta see if mfs stop working
		while (h) { // let's see
			h = false; // maybe they stop
			for (int i = 0; i <= NumThreads; i++) { // cheking if they stop
				if (Work[i] == true) { // they dont
					h = true; // we continues
				}
			}
		}
		
		Queue.clear(); // gotta stay the place clean for new visitors
		IsWorking = false; // bye bye
	}
