#include "framework.h"
#include "MainWindow.h"

#include <string>
#include <sstream>

INT WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd)
{
    wchar_t szWindowName[MAX_LOAD_STRING];
    LoadString(hInstance, IDS_APP_TITLE, szWindowName, MAX_LOAD_STRING);

#ifdef _SINGLE_INSTANCE_ONLY
    std::wstringstream mutexName;
    mutexName <<  szWindowName << L"_Instance";

    HANDLE mutex = CreateMutex(nullptr, TRUE, mutexName.str().c_str());

    if (GetLastError() == ERROR_ALREADY_EXISTS) {
        std::wstringstream ss;
        ss << L"An instance of " << szWindowName << L" is already running";
        MessageBox(nullptr, ss.str().c_str(), szWindowName, MB_ICONEXCLAMATION);
        return 8;
    }
#endif

    MainWindow mainWindow;

    if (!mainWindow.Create(szWindowName, WS_OVERLAPPEDWINDOW)) {
        return 0;
    }

    mainWindow.Show(nShowCmd);

    auto* const hAccelerators =
            LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MAIN_MENU));

    MSG msg = {};

    while (GetMessage(&msg, nullptr, 0, 0)) {
        if (!TranslateAccelerator(msg.hwnd, hAccelerators, &msg)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

#ifdef _SINGLE_INSTANCE_ONLY
    ReleaseMutex(mutex);
    CloseHandle(mutex);
#endif

    return 0;
}
