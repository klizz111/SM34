#include <afxwin.h>
#include <iostream>

// 创建控制台窗口的函数
void CreateConsole()
{
    AllocConsole();
    FILE* pCout;
    freopen_s(&pCout, "CONOUT$", "w", stdout);
}

class CMyApp : public CWinApp
{
public:
    virtual BOOL InitInstance();
};

class CMyFrame : public CFrameWnd
{
public:
    CMyFrame()
    {
        Create(NULL, _T("MFC Console Example"));
    }
};

BOOL CMyApp::InitInstance()
{
    // 创建控制台窗口
    CreateConsole();

    // 使用 std::cout 输出消息
    std::cout << "这是一个输出到控制台的消息。" << std::endl;

    m_pMainWnd = new CMyFrame();
    m_pMainWnd->ShowWindow(SW_NORMAL);
    m_pMainWnd->UpdateWindow();
    return TRUE;
}

CMyApp theApp;