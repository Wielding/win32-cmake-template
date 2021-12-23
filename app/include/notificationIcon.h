#ifdef _ENABLE_NOTIFICATION_ICON
#pragma once

#include "framework.h"

namespace NotificationIcon {

    HRESULT Add(HINSTANCE hInst, HWND hWndMain, UINT nDesktop);

    HRESULT Remove();

    INT_PTR CALLBACK WndProc(HINSTANCE hInst, HWND hWnd,
            UINT message, WPARAM wParam,
            LPARAM lParam);

    VOID APIENTRY DisplayContextMenu(HINSTANCE hInst, HWND hWnd, POINT point);
}
#endif