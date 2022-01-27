#include <windows.h>
#include <iostream>
#include <chrono>
#include <string>

#define FORKS 5
#define PHILOSOPHERS 5
using namespace std;
using namespace std::chrono;
HANDLE mutexF[FORKS];
int main()
{
    STARTUPINFO startInfo[PHILOSOPHERS]{};
    PROCESS_INFORMATION processInfo[PHILOSOPHERS]{};

    for (int i = 0; i < PHILOSOPHERS; i++)
    {
        ZeroMemory(startInfo + i, sizeof(startInfo[i])); // fills memory blocks with zeros
        startInfo[i].cb = sizeof(startInfo[i]);
        ZeroMemory(processInfo + i, sizeof(processInfo[i])); // fills memory blocks with zeros
    }

    for (int i = 0; i < FORKS; i++)
        mutexF[i] = CreateMutexA(NULL, FALSE, (LPCSTR)std::to_string(i + 1).data()); // create mutex to each one

    for (int i = 0; i < PHILOSOPHERS; i++)
    {
        std::wstring pName(L"Mutex2.exe "); 

        pName.append(std::to_wstring(i + 1));
        CreateProcess(NULL, const_cast<WCHAR*>(pName.data()), NULL, NULL, FALSE, 0, NULL, NULL, startInfo + i, processInfo + i);
        Sleep(5);
    }

    for (int i = 0; i < PHILOSOPHERS; i++)
        WaitForSingleObject(processInfo[i].hProcess, INFINITE);

    system("Pause");
    return 0;
}