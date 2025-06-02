#include "Window.hpp"

#include <iostream>

class WindowImpl
{
public:
    WindowImpl() = default;
    virtual ~WindowImpl() = default; // Minimum required for abstract base class.

    virtual void showWindow() = 0;
};

#if 0
class WindowWin32 : public WindowImpl
{
public:
    void showWindow() override
    {
        std::cout << "WindowWin32::showWindow()" << std::endl;
    }
};
using WindowType = WindowWin32;
#else
class WindowLinux : public WindowImpl
{
public:
    void showWindow() override
    {
        std::cout << "WindowLinux::showWindow()" << std::endl;
    }
};
using WindowType = WindowLinux;
#endif


Window::Window()
{
    pImpl = std::make_unique<WindowType>();
}

Window::~Window() = default;

void Window::showWindow()
{
    pImpl->showWindow();
}
