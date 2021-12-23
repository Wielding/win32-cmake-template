#include "MainWindow.h"
#include "messages.h"

#ifdef _ENABLE_NOTIFICATION_ICON

#include "notificationIcon.h"

#endif

/// @brief Set window class data
/// @param wc Pointer to window class structure
void MainWindow::AmendWindowClass(WNDCLASSEXW* wc)
{
    wc->hIcon = LoadIcon(wc->hInstance, MAKEINTRESOURCE(IDI_MAIN_ICON));
    wc->hIconSm = LoadIcon(wc->hInstance, MAKEINTRESOURCE(IDI_MAIN_ICON));
    wc->lpszMenuName = MAKEINTRESOURCE(IDC_MAIN_MENU);
}

/// @brief return the window class name
/// @return window class name
PCWSTR MainWindow::ClassName() const
{
    LoadString(GetModuleHandle(nullptr), IDC_MAIN_MENU,
            const_cast<LPWSTR>(m_szMainWindowClass), MAX_LOAD_STRING);

    return m_szMainWindowClass;
}

/// @brief Handle windows messages
/// @param uMsg message
/// @param wParam WPARAM
/// @param lParam LPARAM
/// @return result
LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    auto* const hWnd = m_hWnd;

    switch (uMsg) {
        case WM_CREATE:

            // Register message to handle explorer restart. Usually used for putting back notification icon
            // after explorer is restarted
            m_uMsgTaskbarCreated = RegisterWindowMessage(TEXT("TaskbarCreated"));

#ifdef _ENABLE_NOTIFICATION_ICON
            if (FAILED(NotificationIcon::Add(m_hInstance, m_hWnd, IDI_MAIN_ICON))) {
                SendMessage(m_hWnd, WM_DESTROY, 0, 0);
            }
#endif
            break;

        case WM_COMMAND: {
            switch (LOWORD(wParam)) {
                case IDM_ABOUT:
                    DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, AboutDialog::DlgProc);
                    break;

                case IDM_NOTIFY_EXIT:
                case IDM_EXIT:

                    DestroyWindow(hWnd);
                    break;

#ifdef _ENABLE_NOTIFICATION_ICON
                case IDM_NOTIFY_TOGGLE_VISIBILITY:
                    m_isVisible = !m_isVisible;
                    Show(m_isVisible ? SW_SHOW : SW_HIDE);
                    break;
#endif
                default:
                    return DefWindowProc(hWnd, uMsg, wParam, lParam);
            }
        }
            break;

        case WM_DESTROY: {

#ifdef _ENABLE_NOTIFICATION_ICON
            NotificationIcon::Remove();
#endif
            PostQuitMessage(0);
            return 0;
        }

        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            FillRect(hdc, &ps.rcPaint, reinterpret_cast<HBRUSH>((COLOR_WINDOW + 1)));
            EndPaint(hWnd, &ps);
        }
            return 0;

#ifdef _ENABLE_NOTIFICATION_ICON
        case APP_WM_ICON_NOTIFY:
            return NotificationIcon::WndProc(GetModuleHandle(nullptr), hWnd, uMsg, wParam, lParam);
#endif

        default:
#ifdef _ENABLE_NOTIFICATION_ICON
            if (uMsg == m_uMsgTaskbarCreated) {
                // Put the icon back if explorer has been restarted after a manual termination or crash
                NotificationIcon::Add(m_hInstance, m_hWnd, IDI_MAIN_ICON);
            }
#else
;
#endif
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

