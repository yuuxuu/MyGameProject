/**
 * @file GameCore.cpp
 * @brief
 * @author Yu Kimura
 * @date 2025/06/03
 */

#include "GameCore.h"
#include "Window/Winow.h"

namespace MyGameCore
{
	GameCore::GameCore()
	{ }

	GameCore::~GameCore()
	{ }

	bool GameCore::Initialize()
	{
		return false;
	}

	void GameCore::Finalize()
	{

	}

} // namespace

int WINAPI main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszArgs, int nWinMode)
{
	MyGameCore::Window window(MyGameCore::RECT(1280, 720));
	if (!window.Initialize(hInstance, "MyGameProject", "MyGame"))
	{
		MessageBoxA(NULL, "Failed Window::Initialize()", "MessageBox", MB_OK);
		return -1;
	}

	MSG	msg;
	while (1) {
		if (!GetMessage(&msg, NULL, 0, 0)) {
			break;
		}
		else {
			// 文字メッセージへのコンバート
			TranslateMessage(&msg);
			// メッセージをWndProcへ送る
			DispatchMessage(&msg);
		}
	}

	return static_cast<int>(msg.lParam);
}