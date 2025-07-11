#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

struct WindowProperties
{
	std::string Title;
	uint32_t Width;
	uint32_t Height;
	bool VSync;

	WindowProperties(const std::string& title = "Window Title",
		uint32_t width = 1280,
		uint32_t height = 720,
		bool vSync = true)
		: Title(title), Width(width), Height(height), VSync(vSync)
	{
	}

	virtual ~WindowProperties() = default;
};

class Window
{
public:
	Window();
	virtual ~Window();

	void Init(const WindowProperties& properties = WindowProperties());
	void Shutdown();

	void OnUpdate();

	uint32_t GetWidth() const;
	uint32_t GetHeight() const;
	std::pair<uint32_t, uint32_t> GetSize() const;
	std::pair<float, float> GetWindowPosition() const;

	//void SetEventCallback(const void* callback);
	void SetVSync(bool isEnabled);
	bool IsVSync() const;

	void* GetNativeWindow() const;

private:
	GLFWwindow* m_Window;

	struct WindowData
		{
			std::string Title;
			uint32_t Width, Height;
			bool VSync;

			//void* EventCallback;
		};

		WindowData m_Data;
};
