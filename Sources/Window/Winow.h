/**
 * @file CWinow.h
 * @brief
 * @author Yu Kimura
 * @date 2025/06/09
 */

#pragma once

#include "math/math.h"

namespace MyGameCore 
{
    class Window 
    {
    private:
        HWND        m_hwnd;
        HINSTANCE   m_hInstance;
        const char* m_className;

        RECT        m_windowSize;
        RECT        m_clientSize;

    private:
        static LRESULT CALLBACK	WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

        void ChangeSizeWindow(const int posx, const int posy, const int width, const int height);

    public:
        Window(RECT windowRect);
        ~Window();

        bool Initialize(HINSTANCE hInstance, const std::string& className, const std::string& titleName);

        HWND GetHwnd() const { return m_hwnd; }

        RECT GetWindowSize() const { return m_windowSize; }

        RECT GetClientSize() const { return m_clientSize; }

        HINSTANCE GethInstance() const { return m_hInstance; }
    };
} // namespace
