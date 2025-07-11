#include <Window.hpp>

#include <spdlog/spdlog.h>

static void GLFWErrorCallback(int error, const char* description)
{
	spdlog::error("GLFW Error ({}): {}", error, description);
}

static bool s_GLFWInitialized = false;
static bool s_GladInitialized = false;

Window::Window()
{
}

Window::~Window()
{
}

void Window::Init(const WindowProperties& properties)
{
	m_Data.Title = properties.Title;
	m_Data.Width = properties.Width;
	m_Data.Height = properties.Height;
	m_Data.VSync = properties.VSync;

	spdlog::info("Creating window \"{}\" ({}, {}) vsync={}", m_Data.Title, m_Data.Width, m_Data.Height, m_Data.VSync);

	if (!s_GLFWInitialized)
	{
		int success = glfwInit();
		// TODO: Debug assertions
		//ASSERT(success, "Could not initialize GLFW!");
		if (!success)
		{
			spdlog::error("Could not initialize GLFW!");
			return;
		}

		glfwSetErrorCallback(GLFWErrorCallback);
		s_GLFWInitialized = true;
	}

	m_Window = glfwCreateWindow(static_cast<int>(m_Data.Width), static_cast<int>(m_Data.Height), m_Data.Title.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(m_Window);
	glfwMaximizeWindow(m_Window); // TODO: Add to window properties
	if (!s_GladInitialized)
	{
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		// TODO: Debug assertions
		//ASSERT(status, "Failed to initialize Glad!");
		if (!status)
		{
			spdlog::error("Failed to initialize Glad!");
			return;
		}
		s_GladInitialized = true;
	}
	glfwSetWindowUserPointer(m_Window, &m_Data);

	glfwSwapInterval(m_Data.VSync);

	// TODO: Set GLFW callbacks.
	// ...

	// Update window size to actual size.
	{
		int width, height;
		glfwGetWindowSize(m_Window, &width, &height);
		m_Data.Width = static_cast<decltype(m_Data.Width)>(width);
		m_Data.Height = static_cast<decltype(m_Data.Height)>(height);
	}
}

void Window::Shutdown()
{
    glfwDestroyWindow(m_Window);

	if (s_GLFWInitialized)
	{
		glfwTerminate();
	}
	else
	{
		spdlog::warn("Attempted to shut down GLFW, but it was not initialized.");
	}
}

void Window::OnUpdate()
{
	glfwPollEvents();
	glfwSwapBuffers(m_Window);
}
