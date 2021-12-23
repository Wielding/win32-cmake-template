#pragma once

#include "aboutdialog.h"
#include "BaseWindow.h"

class MainWindow : public BaseWindow<MainWindow> {
protected:
    void AmendWindowClass(WNDCLASSEXW* wc) override;

    [[nodiscard]] PCWSTR ClassName() const override;

public:
    virtual ~MainWindow() = default;

    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;

    WCHAR m_szMainWindowClass[MAX_LOAD_STRING]{0};
    BOOL m_isVisible{TRUE};
    UINT m_uMsgTaskbarCreated{};
};
