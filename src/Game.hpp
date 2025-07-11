#pragma once

#include <Window.hpp>

class Game
{
public:
	Game();
	virtual ~Game();
	void Run();

	void OnInit();
	void OnShutdown();
	void OnUpdate();

private:
	Window m_Window;
	bool m_IsRunning = true;
};
