#pragma once

class Game
{
public:
	Game();
	virtual ~Game();

	void Run();

private:
	bool IsRunning = true;
};
