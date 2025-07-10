#include "Game.hpp"

#include <spdlog/spdlog.h>

Game::Game()
{
	// TODO: Experiment with spdlog::set_pattern and log sinks
	spdlog::set_level(spdlog::level::trace);
	spdlog::trace("Trace example");
	spdlog::debug("Debug example");
	spdlog::info("Info example");
	spdlog::warn("Warning example");
	spdlog::error("Error example");
	spdlog::critical("Critical example");
}

Game::~Game()
{
}

void Game::Run()
{
	while (IsRunning)
	{
		//spdlog::trace("Hello, world!");
		IsRunning = false;
	}
}
