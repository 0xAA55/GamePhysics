#pragma once
#include<unordered_map>

namespace GLFWApp
{
	enum class AppKeyCode
	{
		/* Printable keys */
		APP_KEY_SPACE              = 32,
		APP_KEY_APOSTROPHE         = 39,  /* ' */
		APP_KEY_COMMA              = 44,  /* , */
		APP_KEY_MINUS              = 45,  /* - */
		APP_KEY_PERIOD             = 46,  /* . */
		APP_KEY_SLASH              = 47,  /* / */
		APP_KEY_0                  = 48,
		APP_KEY_1                  = 49,
		APP_KEY_2                  = 50,
		APP_KEY_3                  = 51,
		APP_KEY_4                  = 52,
		APP_KEY_5                  = 53,
		APP_KEY_6                  = 54,
		APP_KEY_7                  = 55,
		APP_KEY_8                  = 56,
		APP_KEY_9                  = 57,
		APP_KEY_SEMICOLON          = 59,  /* ; */
		APP_KEY_EQUAL              = 61,  /* = */
		APP_KEY_A                  = 65,
		APP_KEY_B                  = 66,
		APP_KEY_C                  = 67,
		APP_KEY_D                  = 68,
		APP_KEY_E                  = 69,
		APP_KEY_F                  = 70,
		APP_KEY_G                  = 71,
		APP_KEY_H                  = 72,
		APP_KEY_I                  = 73,
		APP_KEY_J                  = 74,
		APP_KEY_K                  = 75,
		APP_KEY_L                  = 76,
		APP_KEY_M                  = 77,
		APP_KEY_N                  = 78,
		APP_KEY_O                  = 79,
		APP_KEY_P                  = 80,
		APP_KEY_Q                  = 81,
		APP_KEY_R                  = 82,
		APP_KEY_S                  = 83,
		APP_KEY_T                  = 84,
		APP_KEY_U                  = 85,
		APP_KEY_V                  = 86,
		APP_KEY_W                  = 87,
		APP_KEY_X                  = 88,
		APP_KEY_Y                  = 89,
		APP_KEY_Z                  = 90,
		APP_KEY_LEFT_BRACKET       = 91,  /* [ */
		APP_KEY_BACKSLASH          = 92,  /* \ */
		APP_KEY_RIGHT_BRACKET      = 93,  /* ] */
		APP_KEY_GRAVE_ACCENT       = 96,  /* ` */
		APP_KEY_WORLD_1            = 161, /* non-US #1 */
		APP_KEY_WORLD_2            = 162, /* non-US #2 */
		APP_KEY_ESCAPE             = 256,
		APP_KEY_ENTER              = 257,
		APP_KEY_TAB                = 258,
		APP_KEY_BACKSPACE          = 259,
		APP_KEY_INSERT             = 260,
		APP_KEY_DELETE             = 261,
		APP_KEY_RIGHT              = 262,
		APP_KEY_LEFT               = 263,
		APP_KEY_DOWN               = 264,
		APP_KEY_UP                 = 265,
		APP_KEY_PAGE_UP            = 266,
		APP_KEY_PAGE_DOWN          = 267,
		APP_KEY_HOME               = 268,
		APP_KEY_END                = 269,
		APP_KEY_CAPS_LOCK          = 280,
		APP_KEY_SCROLL_LOCK        = 281,
		APP_KEY_NUM_LOCK           = 282,
		APP_KEY_PRINT_SCREEN       = 283,
		APP_KEY_PAUSE              = 284,
		APP_KEY_F1                 = 290,
		APP_KEY_F2                 = 291,
		APP_KEY_F3                 = 292,
		APP_KEY_F4                 = 293,
		APP_KEY_F5                 = 294,
		APP_KEY_F6                 = 295,
		APP_KEY_F7                 = 296,
		APP_KEY_F8                 = 297,
		APP_KEY_F9                 = 298,
		APP_KEY_F10                = 299,
		APP_KEY_F11                = 300,
		APP_KEY_F12                = 301,
		APP_KEY_F13                = 302,
		APP_KEY_F14                = 303,
		APP_KEY_F15                = 304,
		APP_KEY_F16                = 305,
		APP_KEY_F17                = 306,
		APP_KEY_F18                = 307,
		APP_KEY_F19                = 308,
		APP_KEY_F20                = 309,
		APP_KEY_F21                = 310,
		APP_KEY_F22                = 311,
		APP_KEY_F23                = 312,
		APP_KEY_F24                = 313,
		APP_KEY_F25                = 314,
		APP_KEY_KP_0               = 320,
		APP_KEY_KP_1               = 321,
		APP_KEY_KP_2               = 322,
		APP_KEY_KP_3               = 323,
		APP_KEY_KP_4               = 324,
		APP_KEY_KP_5               = 325,
		APP_KEY_KP_6               = 326,
		APP_KEY_KP_7               = 327,
		APP_KEY_KP_8               = 328,
		APP_KEY_KP_9               = 329,
		APP_KEY_KP_DECIMAL         = 330,
		APP_KEY_KP_DIVIDE          = 331,
		APP_KEY_KP_MULTIPLY        = 332,
		APP_KEY_KP_SUBTRACT        = 333,
		APP_KEY_KP_ADD             = 334,
		APP_KEY_KP_ENTER           = 335,
		APP_KEY_KP_EQUAL           = 336,
		APP_KEY_LEFT_SHIFT         = 340,
		APP_KEY_LEFT_CONTROL       = 341,
		APP_KEY_LEFT_ALT           = 342,
		APP_KEY_LEFT_SUPER         = 343,
		APP_KEY_RIGHT_SHIFT        = 344,
		APP_KEY_RIGHT_CONTROL      = 345,
		APP_KEY_RIGHT_ALT          = 346,
		APP_KEY_RIGHT_SUPER        = 347,
		APP_KEY_MENU               = 348,
		APP_KEY_LAST
	};

	class AppFrame
	{
	protected:
		void *Internal;
		void SwapBuffers();

	public:
		std::unordered_map<AppKeyCode, bool> KeyState;

		AppFrame() noexcept(false);
		AppFrame(int WindowWidth, int WindowHeight, const char *WindowTitle) noexcept(false);

		virtual void OnLoadResources() noexcept(false);
		virtual void OnUnLoadResources() noexcept(false);
		virtual void OnKeyDown(AppKeyCode KeyCode);
		virtual void OnKeyUp(AppKeyCode KeyCode);
		virtual void OnRender(double Time, int ClientWidth, int ClientHeight) noexcept(false);
		virtual void OnUpdate(double Time) noexcept(false);

		void RunLoop() noexcept(false);
		virtual ~AppFrame();
	};
}
