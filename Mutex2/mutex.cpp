#include <windows.h>
#include <iostream>
#include <chrono>
#include <string>

#define EATS_NUM 1000000
#define FORKS 2
using namespace std;
using namespace std::chrono;

int main(int argc, char* argv[])
{
    auto begin = high_resolution_clock::now(); 

    int pNum = atoi(argv[1]); // to int

    HANDLE first = OpenMutexA(MUTEX_ALL_ACCESS, FALSE, std::to_string(pNum).data());

    int secondNum = 0;
    if (pNum == 5)
        secondNum = 1;
    else
        secondNum = pNum + 1; 

    HANDLE second = OpenMutexA(MUTEX_ALL_ACCESS, FALSE, std::to_string(secondNum).data());

    const HANDLE forks[] = { first, second };

    WaitForMultipleObjects(FORKS, forks, TRUE, INFINITE);
    for (int i = 0; i < EATS_NUM; i++) 
    {
        // eating
    }
    if (first != 0)
    ReleaseMutex(first);

    if (second != 0)
    ReleaseMutex(second);

    auto end = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(end - begin); 

    cout << "[I] (" << pNum << ") Time taken using processes (mutex) : " << duration.count() << " microseconds" << endl;
    return 0;
}
