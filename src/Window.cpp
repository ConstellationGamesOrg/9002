#include <Window.hpp>

#include <spdlog/spdlog.h>

static void GLFWErrorCallback(int error, const char* description)
{
	spdlog::error("GLFW Error ({}): {}", error, description);
}

void GLAPIENTRY DebugMessageCallback(
    GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    [[maybe_unused]] GLsizei length,
    const GLchar* message,
    [[maybe_unused]] const void* userParam)
{
    // Ignore certain verbose info messages (particularly ones on Nvidia).
    if (id == 131169 ||
        id == 131185 || // NV: Buffer will use video memory
        id == 131218 ||
        id == 131204 || // Texture cannot be used for texture mapping
        id == 131222 ||
        id == 131154 || // NV: pixel transfer is synchronized with 3D rendering
        id == 0         // gl{Push, Pop}DebugGroup
    )
    return;

    std::stringstream debugMessageStream;
    debugMessageStream << message << '\n';

    switch (source)
    {
        case GL_DEBUG_SOURCE_API: debugMessageStream << "Source: API"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM: debugMessageStream << "Source: Window Manager"; break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: debugMessageStream << "Source: Shader Compiler"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY: debugMessageStream << "Source: Third Party"; break;
        case GL_DEBUG_SOURCE_APPLICATION: debugMessageStream << "Source: Application"; break;
        case GL_DEBUG_SOURCE_OTHER: debugMessageStream << "Source: Other"; break;
    }

    debugMessageStream << '\n';

    switch (type)
    {
        case GL_DEBUG_TYPE_ERROR: debugMessageStream << "Type: Error"; break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: debugMessageStream << "Type: Deprecated Behaviour"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: debugMessageStream << "Type: Undefined Behaviour"; break;
        case GL_DEBUG_TYPE_PORTABILITY: debugMessageStream << "Type: Portability"; break;
        case GL_DEBUG_TYPE_PERFORMANCE: debugMessageStream << "Type: Performance"; break;
        case GL_DEBUG_TYPE_MARKER: debugMessageStream << "Type: Marker"; break;
        case GL_DEBUG_TYPE_PUSH_GROUP: debugMessageStream << "Type: Push Group"; break;
        case GL_DEBUG_TYPE_POP_GROUP: debugMessageStream << "Type: Pop Group"; break;
        case GL_DEBUG_TYPE_OTHER: debugMessageStream << "Type: Other"; break;
    }

    debugMessageStream << '\n';

    switch (severity)
    {
        case GL_DEBUG_SEVERITY_HIGH: debugMessageStream << "Severity: high"; break;
        case GL_DEBUG_SEVERITY_MEDIUM: debugMessageStream << "Severity: medium"; break;
        case GL_DEBUG_SEVERITY_LOW: debugMessageStream << "Severity: low"; break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: debugMessageStream << "Severity: notification"; break;
    }

    spdlog::error("OpenGL Message: {} {}", type, debugMessageStream.str());
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
		// TODO: Debug assertions
		//ASSERT(glfwInit() == GL_FALSE, "GLFW: Unable to initialize");
		if (glfwInit() == GL_FALSE)
		{
			spdlog::error("GLFW: Unable to initialize");
			return;
		}

		glfwSetErrorCallback(GLFWErrorCallback);
		s_GLFWInitialized = true;
	}

	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
	glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);

	//glfwWindowHint(GLFW_SAMPLES, 4); // TODO: Add to window properties

	m_Window = glfwCreateWindow(static_cast<int>(m_Data.Width), static_cast<int>(m_Data.Height), m_Data.Title.c_str(), nullptr, nullptr);
	if (m_Window == nullptr)
    {
        const char* errorDescription = nullptr;
        auto errorCode = glfwGetError(&errorDescription);
        if (errorCode != GLFW_NO_ERROR)
        {
            spdlog::error("GLFW: Unable to create window Details_{}", errorDescription);
        }
        return;
    }
	glfwMakeContextCurrent(m_Window);
	glfwMaximizeWindow(m_Window); // TODO: Add to window properties
	glfwSetWindowUserPointer(m_Window, &m_Data);

	glfwSwapInterval(m_Data.VSync);

	if (!s_GladInitialized)
	{
		int version = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		// TODO: Debug assertions
		//ASSERT(version == 0, "GLAD: Unable to initialize OpenGL context");
		if (version == 0)
		{
			spdlog::error("GLAD: Unable to initialize OpenGL context");
			return;
		}
		glDebugMessageCallback(DebugMessageCallback, nullptr);
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		s_GladInitialized = true;
	}

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
