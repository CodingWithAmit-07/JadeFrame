#pragma once
#include "../extern/glad/glad.h"
#include "../extern/GLFW/glfw3.h"
//#include "../extern/glm/glm.hpp"
#include <array>
#include "math/Vec2.h"


enum class INPUT_ACTION {
	PRESS = GLFW_PRESS,
	RELEASE = GLFW_RELEASE,
	REPEAT = GLFW_REPEAT,
	UNKNOWN = GLFW_KEY_UNKNOWN
};
enum class KEY {
	SPACE = 32,
	ESCAPE = 256,
	ENTER = 257,
	TAB = 258,
	BACKSPACE = 259,
	INSERT = 260,
	DELET = 261,
	RIGHT = 262,
	LEFT = 263,
	DOWN = 264,
	UP = 265,
	PAGE_UP = 266,
	PAGE_DOWN = 267,
	HOME = 268,
	END = 269,
	CAPS_LOCK = 280,
	SCROLL_LOCK = 281,
	NUM_LOCK = 282,
	PRINT_SCREEN = 283,
	PAUSE = 284,
	F1 = 290,
	F2 = 291,
	F3 = 292,
	F4 = 293,
	F5 = 294,
	F6 = 295,
	F7 = 296,
	F8 = 297,
	F9 = 298,
	F10 = 299,
	F11 = 300,
	F12 = 301,
	LEFT_SHIFT = 340,
	LEFT_CONTROL = 341,
	LEFT_ALT = 342,
	RIGHT_SHIFT = 344,
	RIGHT_CONTROL = 345,
	RIGHT_ALT = 346,
	GRAVE = 96,
	SLASH = 47,
	BACKSLASH = 92,

	ZERO = 48,
	ONE = 49,
	TWO = 50,
	THREE = 51,
	FOUR = 52,
	FIVE = 53,
	SIX = 54,
	SEVEN = 55,
	EIGHT = 56,
	NINE = 57,
	A = 65,
	B = 66,
	C = 67,
	D = 68,
	E = 69,
	F = 70,
	G = 71,
	H = 72,
	I = 73,
	J = 74,
	K = 75,
	L = 76,
	M = 77,
	N = 78,
	O = 79,
	P = 80,
	Q = 81,
	R = 82,
	S = 83,
	T = 84,
	U = 85,
	V = 86,
	W = 87,
	X = 88,
	Y = 89,
	Z = 90,
};
enum class MOUSE {
	LEFT_BUTTON = 0,
	RIGHT_BUTTON = 1,
	MIDDLE_BUTTON = 2,
};


class Input {
	friend class Window;
	friend class MainLoop;
public:
	Input()
		: m_windowInstance(nullptr) {}
	~Input() {}

	void handleInput();

	void setWindowInstance(GLFWwindow* window) { m_windowInstance = window; }
	GLFWwindow* getWindowInstance() const { return m_windowInstance; }

private:
	GLFWwindow* m_windowInstance;

	// Key Input
public:
	bool isKeyDown(KEY key) const;
	bool isKeyUp(KEY key) const;
	bool isKeyPressed(KEY key) const;
	bool isKeyReleased(KEY key) const;

	char getDownKey(void) const;
	char getUpKey(void) const;
	char getPressedKey(void) const;
	char getReleasedKey(void) const;

	//private:
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static std::array<INPUT_ACTION, 512> m_currentKeyState;
	static std::array<INPUT_ACTION, 512> m_previousKeyState;



	// Mouse Input
public:
	bool isButtonDown(const MOUSE key) const;
	bool isButtonUp(const MOUSE key) const;
	bool isButtonPressed(const MOUSE key) const;
	bool isButtonReleased(const MOUSE key) const;

	char getDownButton() const;
	char getUpButton() const;
	char getPressedButton() const;
	char getReleasedButton() const;

	//private:
	static void mouseButtonCallback(GLFWwindow* window, int button, int state, int mods);
	static std::array<INPUT_ACTION, 3> m_currentButtonState;
	static std::array<INPUT_ACTION, 3> m_previousButtonState;

	// Mouse Position
public:
	float getMouseX() const;
	float getMouseY() const;
	Vec2 getMousePosition() const;
	//private:
	static void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);
	static Vec2 m_currentMousePosition;

	// Mouse Enter
public:
	bool isMouseInside() const;
	//private:
	static void cursorEnterCallback(GLFWwindow* window, int entered);
	static bool m_isCursorInside;
};