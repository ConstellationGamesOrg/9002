#include "Game.hpp"

#include <iostream>

Game::Game()
{
	try
	{
		spdlog::set_level(spdlog::level::trace);
		spdlog::trace("Trace example");
		spdlog::debug("Debug example");
		spdlog::info("Info example");
		spdlog::warn("Warning example");
		spdlog::error("Error example");
		spdlog::critical("Critical example");
	}
	catch (const std::exception& e)
	{
		std::cerr << "spdlog error: " << e.what() << std::endl;
	}
}

Game::~Game()
{
	spdlog::shutdown();
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
	// Update
	// ...

	// Render
	glClearColor(1.0f, 0.0f, 140.0f / 255.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	// ...

	m_Window.OnUpdate();
	//m_IsRunning = false;
}
