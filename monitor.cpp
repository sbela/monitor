// monitor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include <WinUser.h>
#include <Windowsx.h>

HWND GetConsoleHwnd(void)
{
#define MY_BUFSIZE 1024 // Buffer size for console window titles.
    HWND hwndFound;         // This is what is returned to the caller.
    TCHAR pszNewWindowTitle[MY_BUFSIZE]; // Contains fabricated
    // WindowTitle.
    TCHAR pszOldWindowTitle[MY_BUFSIZE]; // Contains original
    // WindowTitle.

// Fetch current window title.

    GetConsoleTitle(pszOldWindowTitle, MY_BUFSIZE);

    // Format a "unique" NewWindowTitle.

    wsprintf(pszNewWindowTitle, L"%d/%d",
        GetTickCount(),
        GetCurrentProcessId());

    // Change current window title.

    SetConsoleTitle(pszNewWindowTitle);

    // Ensure window title has been updated.

    Sleep(40);

    // Look for NewWindowTitle.

    hwndFound = FindWindow(NULL, pszNewWindowTitle);

    // Restore original window title.

    SetConsoleTitle(pszOldWindowTitle);

    return(hwndFound);
}

int main()
{
    MONITORINFOEX target;
    ZeroMemory(&target, sizeof(MONITORINFOEX));
    target.cbSize = sizeof(MONITORINFOEX);

    HMONITOR hMon = MonitorFromWindow(GetConsoleHwnd(), MONITOR_DEFAULTTONULL);
    GetMonitorInfo(hMon, &target);

    std::wcout << target.szDevice << "\n";
}


