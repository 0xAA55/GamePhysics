#include"AppFrame.hpp"
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<stdexcept>
using namespace std;
using namespace GLFWApp;

static void ErrorCallback(int Error, const char *Description)
{
	throw exception(Description);
}

static void KeyCallback(GLFWwindow *Window, int Key, int Scancode, int Action, int Mods)
{
	AppFrame *App = static_cast<AppFrame *>(glfwGetWindowUserPointer(Window));
	if (!App) throw exception("Unexpected call to `KeyCallback()`");
	if ((Action & GLFW_PRESS) == GLFW_PRESS)
	{
		App->OnKeyDown(static_cast<AppKeyCode>(Key));
	}
	else
	{
		App->OnKeyUp(static_cast<AppKeyCode>(Key));
	}
}

AppFrame::AppFrame() : AppFrame(640, 480, "Simple sample")
{
}

AppFrame::AppFrame(int WindowWidth, int WindowHeight, const char *WindowTitle)
{
	if (!glfwInit()) throw exception("glfwInit() failed.");
	glfwSetErrorCallback(ErrorCallback);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	GLFWwindow *window = glfwCreateWindow(WindowWidth, WindowHeight, WindowTitle, NULL, NULL);
	if (!window) throw exception("glfwCreateWindow() failed.");
	Internal = window;
	glfwSetWindowUserPointer(window, this);
	glfwSetKeyCallback(window, KeyCallback);
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) throw exception("glewInit() failed.");

	glfwSwapInterval(-1);
	if (glfwGetError(NULL) == GLFW_PLATFORM_ERROR)
		glfwSwapInterval(1);
}

void AppFrame::OnKeyDown(AppKeyCode KeyCode)
{
	KeyState[KeyCode] = true;
}

void AppFrame::OnKeyUp(AppKeyCode KeyCode)
{
	KeyState[KeyCode] = false;
}

void AppFrame::SwapBuffers()
{
	GLFWwindow *Window = static_cast<GLFWwindow *>(Internal);
	glfwSwapBuffers(Window);
}

void AppFrame::OnLoadResources()
{
}

void AppFrame::OnUnLoadResources()
{
}

void AppFrame::OnRender(double Time, int ClientWidth, int ClientHeight)
{
	glViewport(0, 0, ClientWidth, ClientHeight);
	glClearColor((GLclampf)sin(Time), (GLclampf)cos(Time), (GLclampf)sin(Time * 0.5), 0);
	glClear(GL_COLOR_BUFFER_BIT);
	SwapBuffers();
}

void AppFrame::OnUpdate(double Time)
{
}

void AppFrame::RunLoop()
{
	GLFWwindow *Window = static_cast<GLFWwindow *>(Internal);
	OnLoadResources();
	while (!glfwWindowShouldClose(Window))
	{
		int ClientWidth, ClientHeight;
		double Seconds = glfwGetTime();
		glfwGetFramebufferSize(Window, &ClientWidth, &ClientHeight);
		OnUpdate(Seconds);
		OnRender(Seconds, ClientWidth, ClientHeight);
		glfwPollEvents();
	}
	OnUnLoadResources();
}

AppFrame::~AppFrame()
{
	GLFWwindow *Window = static_cast<GLFWwindow *>(Internal);
	glfwDestroyWindow(Window);
	glfwTerminate();
}
