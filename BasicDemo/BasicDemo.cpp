#include<AppFrame.hpp>
#include<GamePhysics.hpp>

#ifdef _WIN32
#include<Windows.h>
#include<stdlib.h>
int main(int argc, char **argv);
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int nShow)
{
	return main(__argc, __argv);
}
int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR szCmdLine, int nShow)
{
	return main(__argc, __argv);
}
#endif

using namespace GLFWApp;
using namespace GamePhysics;

class BasicDemo : public AppFrame
{
public:
	GPWorld World;

	BasicDemo() : World (){}

	void OnRender(double Time, int ClientWidth, int ClientHeight) override
	{

	}

	void OnUpdate(double Time) override
	{

	}
};

int main(int argc, char **argv)
{
	BasicDemo App;
	App.RunLoop();
}
