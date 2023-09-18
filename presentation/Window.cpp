#include "Window.h"

Window::Window(QWidget *parent) {}

void Window::openNewWindow(Window* newWindow) {
    this->hide();
    newWindow->show();
    connect(newWindow, &Window::back, this, &Window::show);
}