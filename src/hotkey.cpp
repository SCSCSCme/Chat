#include "hotkey.h"
#include "settings.h"

#include <thread>
#include <iostream>

#ifdef __linux__
void register_hotkey()
{
    std::thread([](){
        Display* display;
        if (!display)
        {
            std::cerr << "Failed to open X display" << std::endl;
            return;
        }

        Window root = DefaultRootWindow(display);
        XEvent event;

        KeyCode ctrl_key = XKeysymToKeycode(display, XK_Control_L);
        KeyCode alt_key = XKeysymToKeycode(display, XK_Alt_L);
        KeyCode c_key = XKeysymToKeycode(display, XK_c);

        XGrabKey(display, ctrl_key, AnyModifier, root, False, GrabModeAsync, GrabModeAsync);
        XGrabKey(display, alt_key, AnyModifier, root, False, GrabModeAsync, GrabModeAsync);
        XGrabKey(display, c_key, ControlMask | Mod1Mask, root, False, GrabModeAsync, GrabModeAsync);

        XSelectInput(display, root, KeyPressMask);

        while(g_running)
        {
            XNextEvent(display, &event);
            if (event.type == KeyPress)
            {
                g_show_window = !g_show_window;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        XCloseDisplay(display);
    }).detach();
}
#elif defined(_WIN32)
void register_key()
{
    if (!RegisterHotKey(NULL, 1, MOD_CONTROL | MOD_ALT, 'C')) 
    {
        std::cerr << "Failed to register hotkey" << std::endl;
    }
}

void check_windows_messages() {
    MSG msg;
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        if (msg.message == WM_HOTKEY) {
            g_show_window = !g_show_window;
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}
#endif