#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <iostream>

using namespace std;

int main() {

	HANDLE hSnapshot = INVALID_HANDLE_VALUE;
	PROCESSENTRY32 processInfo = { 0 };
	processInfo.dwSize = sizeof(PROCESSENTRY32); //initializing as said in win32 docs
	int processCount = 0;
	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hSnapshot == INVALID_HANDLE_VALUE) {
		cout << "Snapshot creation failed with error code : " << GetLastError() << endl;
	}
	cout << "Snapshot created" << endl;

	BOOL firstProcess = Process32First(hSnapshot, &processInfo);

	if (!firstProcess) {
		CloseHandle(hSnapshot);
		return 0;
	}

	do{
		cout << "---------------------------------------------" << endl;
		cout << "Process " << ++processCount << ": " << endl;
		cout << "---------------------------------------------" << endl;
		cout << "Number of threads in the process : " << processInfo.cntThreads << endl;
		cout << "Size : " << processInfo.dwSize << endl;
		cout << "Priority class: " << processInfo.pcPriClassBase << endl;
		_tprintf(TEXT("Executable link:  %s"), processInfo.szExeFile);
		cout <<endl<< "Parent process ID: " << processInfo.th32ParentProcessID << endl;
		cout << "Process ID: " << processInfo.th32ProcessID << endl;

	} while (Process32Next(hSnapshot, &processInfo) != FALSE);

	if (hSnapshot) {
		CloseHandle(hSnapshot);
	}

	return 0;

}