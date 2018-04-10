#include "MWindowBase.hpp"

class MyWindowClass : public MWindowBase
{
public:
    DECLARE_DYNAMIC(MyWindowClass);

    MyWindowClass()
    {
    }

    virtual ~MyWindowClass()
    {
    }

    static BOOL RegisterDx()
    {
        MyWindowClass mwc;
        return mwc.RegisterClassDx();
    }

    virtual LPCTSTR GetWndClassNameDx() const
    {
        return TEXT("MyWindowClass");
    }

    virtual VOID ModifyWndClassDx(WNDCLASSEX& wcx)
    {
        static HBRUSH hbr = CreateSolidBrush(RGB(255, 0, 0));
        wcx.hbrBackground = hbr;
    }

    BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
    {
        return TRUE;
    }

    virtual LRESULT CALLBACK
    WindowProcDx(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg)
        {
        HANDLE_MSG(hwnd, WM_CREATE, OnCreate);
        default:
            return DefaultProcDx();
        }
    }
};
IMPLEMENT_DYNAMIC(MyWindowClass);

void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
    switch (id)
    {
    case IDOK:
        EndDialog(hwnd, IDOK);
        break;
    case IDCANCEL:
        EndDialog(hwnd, IDCANCEL);
        break;
    }
}

INT_PTR CALLBACK
DialogProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        HANDLE_MSG(hwnd, WM_COMMAND, OnCommand);
    }
    return 0;
}

INT WINAPI
WinMain(HINSTANCE   hInstance,
        HINSTANCE   hPrevInstance,
        LPSTR       lpCmdLine,
        INT         nCmdShow)
{
    MyWindowClass::RegisterDx();
    DialogBox(hInstance, MAKEINTRESOURCE(1), NULL, DialogProc);
    return 0;
}
