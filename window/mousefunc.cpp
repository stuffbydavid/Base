#include "window/mousefunc.hpp"
#include "apphandler.hpp"


bool Base::mouseInBox(ScreenArea box)
{
    ScreenPos mouse = appHandler->mainWindow->mouse;
    return (mouse.x >= box.pos.x && mouse.x < box.pos.x + box.width
         && mouse.y >= box.pos.y && mouse.y < box.pos.y + box.height);
}


bool Base::mouseLeftDown()
{
    return appHandler->mainWindow->mouseDown[GLFW_MOUSE_BUTTON_LEFT];
}


bool Base::mouseLeftPressed()
{
    return appHandler->mainWindow->mousePressed[GLFW_MOUSE_BUTTON_LEFT];
}


bool Base::mouseLeftReleased()
{
    return appHandler->mainWindow->mouseReleased[GLFW_MOUSE_BUTTON_LEFT];
}


bool Base::mouseRightDown()
{
    return appHandler->mainWindow->mouseDown[GLFW_MOUSE_BUTTON_RIGHT];
}


bool Base::mouseRightPressed()
{
    return appHandler->mainWindow->mousePressed[GLFW_MOUSE_BUTTON_RIGHT];
}


bool Base::mouseRightReleased()
{
    return appHandler->mainWindow->mouseReleased[GLFW_MOUSE_BUTTON_RIGHT];
}


void Base::mouseClear()
{
    Window* window = appHandler->mainWindow;
    for (uint m = 0; m < GLFW_MOUSE_BUTTON_LAST; m++) {
        window->mouseDown[m] = false;
        window->mousePressed[m] = false;
        window->mouseReleased[m] = false;
    }
}


void Base::mouseSetCursor(Cursor cursor)
{
    if (cursor == ARROW) {
        appHandler->mainWindow->currentCursor =appHandler->mainWindow->cursorArrow;
    }
    else if (cursor == HANDPOINT) {
        appHandler->mainWindow->currentCursor = appHandler->mainWindow->cursorHandpoint;
    }
}