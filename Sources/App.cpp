/**
 * @file App.cpp
 * @brief
 * @author Yu Kimura
 * @date 2018/12/15
 */

#include "App.h"

int WINAPI main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszArgs, int nWinMode)
{

    // ToDo:ダブルバッファリングで画面のちらつきをなくす
    HANDLE hFrontBuffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, nullptr, CONSOLE_TEXTMODE_BUFFER, 0);
    if (hFrontBuffer == INVALID_HANDLE_VALUE)
    {
        throw "error:Failed_FrontBuffer_CreateConsoleScreenBuffer";
        return -1;
    }
    HANDLE hBackBuffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, nullptr, CONSOLE_TEXTMODE_BUFFER, 0);
    if (hBackBuffer == INVALID_HANDLE_VALUE)
    {
        throw "error:Failed_BackBuffer_CreateConsoleScreenBuffer";
        return -1;
    }

    std::vector<HANDLE> handles{ hFrontBuffer, hBackBuffer };
    for (auto& handle : handles)
    {
        CONSOLE_CURSOR_INFO info = {};
        GetConsoleCursorInfo(handle, &info);

        info.bVisible = false;
        SetConsoleCursorInfo(handle, &info);
    }
    int index = 0;

    DWORD buffer;
    const int width = 5;
    const int height = 5;
    const DWORD bufSize = width * height;
    std::string frontBuffer = "◇◇◇□□□";
    std::string backBuffer = "◇◇◇□□□";
    std::array<short, 2> player = { 0, 0 };
    short _map[height][width] =
    {
        1, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
    };
    WCHAR map[height][width];

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if (_map[i][j] == 1)
            {
                map[i][j] = '〇';
            }
            else
            {
                map[i][j] = '□';
            }
        }
    }

    while (1)
    {
        if (GetKeyState(VK_ESCAPE) & 0x8000)
        {
            break;
        }

        if (GetKeyState(VK_RIGHT) & 0x8000)
        {
            auto posY = player.at(0);
            auto posX = player.at(1);

            map[posY][posX] = '□';

            posX++;
            if (posX > width - 1)
            {
                posX = width - 1;
            }
            map[posY][posX] = '〇';

            player[1] = posX;
        }
        if (GetKeyState(VK_LEFT) & 0x8000)
        {
            auto posX = player.at(0);
            auto posY = player.at(1);

            map[posY][posX] = '□';

            posX--;
            if (posX < 0)
            {
                posX = 0;
            }
            map[posY][posX] = '〇';

            player[1] = posX;
        }

        auto& handle = handles.at(index);

        if (SetConsoleActiveScreenBuffer(handle))
        {
            index = (handle == handles.front()) ? index + 1 : index - 1;
        }

        for (int i = 0; i < height; ++i)
        {
            COORD rect{ 0, (SHORT)i };
            SetConsoleCursorPosition(handle, rect);

            DWORD size = sizeof(WCHAR) * width;

            if (index == 0)
            {
                WriteConsole(handle, &map[i][0], size, &buffer, NULL);
            }
            else
            {
                WriteConsole(handle, &map[i][0], size, &buffer, NULL);
            }
        }
    }

    for (auto& handle : handles)
    {
        CloseHandle(handle);
    }

    return 0;
}