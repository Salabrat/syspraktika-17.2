#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>

int main()
{
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot == INVALID_HANDLE_VALUE) {
        printf("Could not create process snapshot\n");
        return 1;
    }

    PROCESSENTRY32 process;
    process.dwSize = sizeof(process);

    if (!Process32First(snapshot, &process)) {
        printf("Could not get first process\n");
        CloseHandle(snapshot);
        return 1;
    }

    printf("Process List:\n");

    do {
        printf("  ID: %d | Name: %s\n", process.th32ProcessID, process.szExeFile);
    } while (Process32Next(snapshot, &process));

    CloseHandle(snapshot);
    return 0;
}
