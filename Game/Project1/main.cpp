#include <easyx.h>
#include <conio.h>
#include <windows.h>
#include "loadresource.h"
#include "game.h"

extern IMAGE img[500];
Games Game1;

int main()
{
    initgraph(1366, 768);
    HWND hWnd = GetHWnd();            // 获取窗口名称句柄
    //SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) - WS_CAPTION);
    //SetWindowPos(hWnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CXSCREEN), SWP_SHOWWINDOW);
    SetWindowTextA(hWnd, "Group5's game");    // 窗口标题名称
    IMAGE loading;
    loadimage(&loading, _T("Resources\\loading.jpg"));
    putimage(0, 0, &loading);
    loadresource();
    cleardevice();
    Game1.Title();
    _getch();            // 运行完等待，不闪退
    closegraph();
}