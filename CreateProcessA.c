    LPSTARTUPINFOA si = new STARTUPINFOA();
    LPPROCESS_INFORMATION pi = new PROCESS_INFORMATION();
    CreateProcessA(NULL, (LPSTR)"notepad.exe", NULL, NULL, TRUE, 0, NULL, NULL, si, pi);