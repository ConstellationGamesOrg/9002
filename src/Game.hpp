#pragma once

 /**
  * @class Game
  * @brief The Game class.
  *
  * Does game stuff.
  *
  */
class Game
{
public:
	Game();
	virtual ~Game();

	/**
	 * @brief Short description.
	 * @details Longer detailed description.
	 *
	 * Blah blah example documentation.
	 *
	 * @param x Example param x.
	 * @param y Example param y.
	 * @note Example note.
	 * @returns void.
	 * @throws Nothing.
	 *
	 */
	void Run();

private:
	bool IsRunning = true;
};
