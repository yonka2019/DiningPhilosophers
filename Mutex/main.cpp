/*
* Some interesting information:
* Mutex is slower than threads because in threads there are in the same process
* Mutexes each one is a different proces, which means, that it needs to switch between 
* different processes and use new resources everytime
* which takes more time.
* >>> In conclcusion:
* Threads faster than mutex. =O
*/

#include <windows.h>
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

#define SLEEP_TIME 5
#define NUMBER_OF_FORKS 5
#define NUMBER_OF_PHILOSOPHER 5
#define EATS 1000000

DWORD WINAPI doWork(int* philosopherNumber);
HANDLE mutexForks[NUMBER_OF_FORKS];

int main()
{
    int index = 0;

    HANDLE WINAPI philosophers[NUMBER_OF_PHILOSOPHER];

    for (auto i : mutexForks)
    {
        i = CreateMutex(NULL, FALSE, NULL);
    }

    for (int i = 0; i < NUMBER_OF_PHILOSOPHER; i++)
    {
        philosophers[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)doWork, &i, 0, NULL);
        Sleep(SLEEP_TIME);
    }

    for (auto i : philosophers)
    {
        WaitForSingleObject(i, INFINITE);
    }

    for (auto i : mutexForks)
    {
        CloseHandle(i);
    }

    for (auto i : philosophers)
    {
        CloseHandle(i);
    }

    return 0;
}

DWORD WINAPI doWork(int* philosopherNumber)
{
    auto start = high_resolution_clock::now();

    int firstFork = 0;
    int secondFork = 0;

    if (*philosopherNumber == 4)
    {
        firstFork = *philosopherNumber;
        secondFork = 0;
    }
    else
    {
        firstFork = *philosopherNumber;
        secondFork = *philosopherNumber + 1;
    }

    WaitForSingleObject(mutexForks[firstFork], INFINITE);
    WaitForSingleObject(mutexForks[secondFork], INFINITE);

    cout << "phiphilosopher " << *philosopherNumber + 1 << "'s turn" << endl;

    for (int i = 0; i < EATS; i++) {}

    ReleaseMutex(mutexForks[firstFork]);
    ReleaseMutex(mutexForks[secondFork]);

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    cout << "[I] Time taken using processes (mutex): " << duration.count() << " microseconds" << endl;

    return 0;
}