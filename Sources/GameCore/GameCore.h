/**
 * @file GameCore.h
 * @brief
 * @author Yu Kimura
 * @date 2025/06/03
 */

#pragma once

#include <Windows.h>

namespace MyGameCore
{
	class GameCore
	{
	private:
		GameCore();
		~GameCore();

	public:
		static GameCore Instance()
		{
			static GameCore gameCore;
			return gameCore;
		}

		bool Initialize();
		void Finalize();
	};
} // namespace