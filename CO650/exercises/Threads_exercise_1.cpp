// Create a new C++ console project.
// The first step is to create a thread function that will
// contain the statements to be executed within a new thread.

#include <iostream>
#include <Windows.h>
#include "MyVars.h"

using namespace std;

DWORD WINAPI MessageThread(LPVOID param)
{

    int tab = (int)param;

    for (int n = 0; n < 10; n++)
    {
        for (int i = 0; i < 10000; i++)
        {
            if (tab == 1)
                cout << "\t\t 1: Thread\n";
            else if (tab == 2)
                cout << "\t\t\t\t 2: Thread\n";
            else
                cout << "\t\t\t\t\t\t 3: Thread\n";
        }
        Sleep(500);
    }
    return 0;
}

int main()
{
    cout << "======= W9 Threads ======\n";

    cout << "==== Exercise 1 ====\n\n";

    DWORD threadId;
    HANDLE hdl[3];
    int label = 1;

    hdl[0] = CreateThread(NULL, 0, MessageThread, (LPVOID)label, 0, &threadId);
    SetThreadPriority(hdl[0], THREAD_PRIORITY_IDLE);
    label = 2;
    hdl[1] = CreateThread(NULL, 0, MessageThread, (LPVOID)label, 0, &threadId);
    SetThreadPriority(hdl[1], THREAD_PRIORITY_TIME_CRITICAL);
    label = 3;
    hdl[2] = CreateThread(NULL, 0, MessageThread, (LPVOID)label, 0, &threadId);
    SetThreadPriority(hdl[2], THREAD_PRIORITY_LOWEST);

    // To stop main thread from executing before it reaches the system call,
    // we can include the two lines below just above system("pause")
    HANDLE mainThread = GetCurrentThread();
    SuspendThread(mainThread);

    system("pause");

    return 0;
}