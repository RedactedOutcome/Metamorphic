#include "Morphic/pch.h"
#include "Morphic/Display/Window.h"

namespace Morphic{
    Window::Window(WindowAPI window) MORPHIC_NOEXCEPT : m_API(window){

    }

    Window::~Window(){

    }

    void Window::Create(WindowProps&& props){

    }
}