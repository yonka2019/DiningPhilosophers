#include <windows.h>
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

#define SLEEP_TIME 5
#define NUMBER_OF_PHILOSOPHER 5
#define EATS_NUM 1000000

DWORD WINAPI doWork(int* phiphilosopher);

CRITICAL_SECTION ghCARITICALSection1;
CRITICAL_SECTION ghCARITICALSection2;
CRITICAL_SECTION ghCARITICALSection3;
CRITICAL_SECTION ghCARITICALSection4;
CRITICAL_SECTION ghCARITICALSection5;

int main()
{
    int index = 0;

    HANDLE WINAPI th1 = NULL,
                  th2 = NULL,
                  th3 = NULL,
                  th4 = NULL,
                  th5 = NULL;

    HANDLE threads[NUMBER_OF_PHILOSOPHER] = { th1, th2, th3, th4, th5 };

    CRITICAL_SECTION* sections[NUMBER_OF_PHILOSOPHER] = { &ghCARITICALSection1 , &ghCARITICALSection2 , &ghCARITICALSection3 , &ghCARITICALSection4 , &ghCARITICALSection5 };

    int philosopher1 = 1,
        philosopher2 = 2,
        philosopher3 = 3,
        philosopher4 = 4,
        philosopher5 = 5;

    int* philosophers[5] = { &philosopher1 , &philosopher2 , &philosopher3 , &philosopher4 , &philosopher5 };

    for (auto i : sections)
    {
        InitializeCriticalSection(i);
    }

    for (auto i : threads)
    {
        i = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)doWork, philosophers[index], 0, NULL);
        index++;
        Sleep(SLEEP_TIME);
    }

    for (auto i : threads)
    {
        WaitForSingleObject(i, INFINITE);
        CloseHandle(i);
    }

    return 0;
}

DWORD WINAPI doWork(int* phiphilosopher)
{
    auto start = high_resolution_clock::now();

    switch (*phiphilosopher)
    {
        case 1:
            if (TryEnterCriticalSection(&ghCARITICALSection1)) {
                if (TryEnterCriticalSection(&ghCARITICALSection2)) {
                    cout << "phiphilosopher " << *phiphilosopher << "'s turn" << endl;

                    for (int i = 0; i < EATS_NUM; i++) {}

                    LeaveCriticalSection(&ghCARITICALSection2);
                }
                LeaveCriticalSection(&ghCARITICALSection1);
            }
            break;
        case 2:
            if (TryEnterCriticalSection(&ghCARITICALSection2)) {
                if (TryEnterCriticalSection(&ghCARITICALSection3)) {
                    cout << "phiphilosopher " << *phiphilosopher << "'s turn" << endl;

                    for (int i = 0; i < EATS_NUM; i++) {}

                    LeaveCriticalSection(&ghCARITICALSection3);
                }
                LeaveCriticalSection(&ghCARITICALSection2);
            }
            break;
        case 3:
            if (TryEnterCriticalSection(&ghCARITICALSection3)) {
                if (TryEnterCriticalSection(&ghCARITICALSection4)) {
                    cout << "phiphilosopher " << *phiphilosopher << "'s turn" << endl;

                    for (int i = 0; i < EATS_NUM; i++) {}

                    LeaveCriticalSection(&ghCARITICALSection4);
                }
                LeaveCriticalSection(&ghCARITICALSection3);
            }
            break;
        case 4:
            if (TryEnterCriticalSection(&ghCARITICALSection4)) {
                if (TryEnterCriticalSection(&ghCARITICALSection5)) {
                    cout << "phiphilosopher " << *phiphilosopher << "'s turn" << endl;

                    for (int i = 0; i < EATS_NUM; i++) {}

                    LeaveCriticalSection(&ghCARITICALSection5);
                }
                LeaveCriticalSection(&ghCARITICALSection4);
            }
            break;
        default:
            if (TryEnterCriticalSection(&ghCARITICALSection5)) {
                if (TryEnterCriticalSection(&ghCARITICALSection1)) {
                    cout << "phiphilosopher " << *phiphilosopher << "'s turn" << endl;

                    for (int i = 0; i < EATS_NUM; i++) {}

                    LeaveCriticalSection(&ghCARITICALSection1);
                }
                LeaveCriticalSection(&ghCARITICALSection5);
            }
            break;
    }

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    cout << "[I] Time taken using threads (critical section): " << duration.count() << " microseconds" << endl;

    return 0;
}