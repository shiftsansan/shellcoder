//Add .def Entry Point
//LIBRARY "dllmain"
//EXPORTS
//wow

// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <stdlib.h>
#include <iostream>


int wow() {
	MessageBox(0, TEXT("OK1"), TEXT("OK"), MB_OK);
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	if (!
		CreateProcess
		(
			TEXT("C:\\Users\\Jupi\\source\\repos\\Dll2\\x64\\Debug\\a.bat"),
			NULL, NULL, NULL, FALSE,
			CREATE_NEW_CONSOLE,
			NULL, NULL,
			&si,
			&pi
		)
		)
		std::cout << "Unable to execute.";

	return TRUE;
}

BOOL APIENTRY dllmain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{


    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        wow();
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

