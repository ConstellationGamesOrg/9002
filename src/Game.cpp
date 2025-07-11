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
	OnInit();
	while (m_IsRunning)
	{
		OnUpdate();
	}
	OnShutdown();
}

void Game::OnInit()
{
	m_Window.Init({"9002 Game", 1280u, 720u, true});
}

void Game::OnShutdown()
{
	m_Window.Shutdown();
}

void Game::OnUpdate()
{
	m_Window.OnUpdate();
    glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0f, 0.0f, 140.0f / 255.0f, 1.0f);
	//m_IsRunning = false;
}
