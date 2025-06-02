#pragma once

#include <memory>

class WindowImpl;
class Window
{
public:
    Window();
    ~Window();

    void showWindow();

private:
    // The pimpl idiom (Pointer to implementation).
    std::unique_ptr<WindowImpl> pImpl;
};
