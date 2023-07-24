///////////////////////////////////////////
//*  @file    finddesktophwnd.h
//*  @date    2021/10/02 23:16
//*  @brief   查找桌面窗口句柄
//*
//*  @author  Maye(顽石老师)
//*  @contact zcmaye@gmail.com
//*  @微信公众号 C语言Plus
///////////////////////////////////////////
#ifndef FINDDEKTOPHWND_H
#define FINDDEKTOPHWND_H
#include<qt_windows.h>
class QWidget;
class FindDektopHwnd
{
public:
    FindDektopHwnd();
    static BOOL CALLBACK EnumWindowsProc(_In_ HWND tophandle, _In_ LPARAM topparamhandle);
    /*
    * @return 返回桌面句柄
    */
    static HWND GetDesktopHandle();

    /**
     * @param child 是需要设置为子窗口的控件.
     * @param parent 是空则把child设置为桌面的孩子，否则设置为parent的孩子
     */
    static void SetParent(QWidget*child,HWND parent);

    inline static HWND _workerw = NULL;
};

#endif // FINDDEKTOPHWND_H
