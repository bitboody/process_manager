#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>
#include <tlhelp32.h>

#include "util.h"

void prompt();
int process_list();
int process_kill(DWORD pid);

int main()
{
    prompt();
    return 0;
}

void prompt()
{
    char input[64];
    input[0] = '\0';

    while (strcmp(input, "exit") != 0)
    {
        printf("$ ");
        read_input(input, sizeof(input));

        if (strcmp(input, "ls") == 0)
            process_list();

        if (strcmp(input, "kill") == 0)
        {
            printf("Enter PID to Terminate: ");
            read_input(input, sizeof(input));
            process_kill((DWORD)atoi(input));
        }
    }

    return;
}

int process_list()
{
    HANDLE hSnapshot;
    hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE)
    {
        printf("Failed to take snapshot.\n");
        return -1;
    }

    PROCESSENTRY32 process;
    ZeroMemory(&process, sizeof(process));
    process.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(hSnapshot, &process))
    {
        do
        {
            printf("Process ID: %u | Executable: %s\n", process.th32ProcessID, process.szExeFile);
        } while (Process32Next(hSnapshot, &process));
    }
    else
    {
        printf("Failed to get process information.\n");
    }

    CloseHandle(hSnapshot);
    return 0;
}

int process_kill(DWORD pid)
{
    HANDLE process = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
    if (process == NULL)
    {
        printf("Failed to open process: %lu\n", GetLastError());
        return -1;
    }

    printf("Killing process %lu...\n", pid);

    if (TerminateProcess(process, 0))
    {
        printf("Process terminated successfully\n");
    }
    else
    {
        printf("Failed to terminate process: %lu\n", GetLastError());
        return -1;
    }

    CloseHandle(process);
    return 0;
}