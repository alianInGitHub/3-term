#include <iostream>
#include <random>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <Windows.h>

using namespace std;

mutex lockprint;
mutex lockqueue;
condition_variable queuecheck;
queue<int> events;
bool done = false;
bool notified;
CRITICAL_SECTION cs;
unsigned long uThrID;


void threadFunc(void* pParams)
{
	mt19937 generator((unsigned int)chrono::system_clock::now().time_since_epoch().count());
	// start message
	{
		unique_lock<mutex> locker(lockprint);
		cout << "[thread " << GetCurrentThreadId() << "]\trunning..." << endl;
	}
	//simulation of work
	while (!done)
	{
		this_thread::sleep_for(chrono::seconds(1 + generator() % 6));
		// simulation of event
		int event = GetCurrentThreadId() * 100 + 1;
		{
			unique_lock<mutex> locker(lockprint);
			cout << "[thread " << GetCurrentThreadId() << "]\t message: " << event << endl;
		}
		// message the event
		{
			EnterCriticalSection(&cs);
			unique_lock<mutex> locker(lockqueue);
			events.push(event);
			notified = true;
			queuecheck.notify_one();
			LeaveCriticalSection(&cs);
		}
	}
}


void loggerFunc(void* pParams)
{
	// start message
	{
		unique_lock<mutex> locker(lockprint);
		cout << "[logger" << GetCurrentThreadId() << "]\trunning..." << endl;
	}
	// while haven't recieve a sygnal
	while (!done)
	{
		unique_lock<mutex> locker(lockqueue);
		while (!notified)
		{
			queuecheck.wait(locker);
		}
		while (!events.empty())
		{
			EnterCriticalSection(&cs);
			unique_lock<mutex> locker(lockprint);
			cout << "[logger" << GetCurrentThreadId() << "]\tprocessing event " << events.front() << endl;
			events.pop();
			LeaveCriticalSection(&cs);
		}
		notified = false;
	}
}


int main()
{
	InitializeCriticalSection(&cs);
	done = false;
	//start of registrator
	HANDLE loggerThread1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)loggerFunc, NULL, 0, &uThrID);
	HANDLE loggerThread2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)loggerFunc, NULL, 0, &uThrID);
	SetThreadPriority(loggerThread1, BELOW_NORMAL_PRIORITY_CLASS);
	SetThreadPriority(loggerThread2, BELOW_NORMAL_PRIORITY_CLASS);

	//start workers
	HANDLE* threads = new HANDLE[3];

	for (int i = 0; i < 3; i++)
	{
		threads[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threadFunc, NULL, 0, &uThrID);
		SetThreadPriority(threads[i], NORMAL_PRIORITY_CLASS);
	}

	while (1)
	{
		done = false;
	}
	done = true;
	//delete pointers to threads
	delete [] threads;
	system("PAUSE");
}