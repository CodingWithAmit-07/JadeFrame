#include "BaseApp.h"
#include <iostream>
#include "GUI.h"

BaseApp* BaseApp::instance = nullptr;
BaseApp::BaseApp() {}

BaseApp::~BaseApp() {
	glfwTerminate();
}

void BaseApp::initApp(const std::string& title, float width, float height) {
	instance = this;
	window.init(title, width, height);
	shader.init();
	renderer.init(&shader);

	input.setWindowInstance(window.handle);

	glfwSetMouseButtonCallback(window.handle, input.mouseButtonCallback);
	glfwSetCursorEnterCallback(window.handle, input.cursorEnterCallback);
	glfwSetKeyCallback(window.handle, input.keyCallback);
}
static void processInput(GLFWwindow* window) {
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}
class CMesh {
public:
	CMesh(Vec2 pos, Vec2 size) {

	}

	void setPosition(Vec2 pos) {
		isDirty = true;
	}
	void draw() {
		if(isDirty) {
			BaseApp::getAppInstance()->renderer.drawRectangle(pos, size);
		}
	}
//private:
	Vec2 pos, size;
	bool isDirty = false;

};
void BaseApp::runApp() {
	GUIinit(window.handle);

	{
		std::cout << "Uniforms: ";
		for(auto uniform : shader.m_uniforms) {
			std::cout << uniform.name << " ";
		} std::cout << std::endl;
		std::cout << "Attribs : ";
		for(auto attributes : shader.m_attributes) {
			std::cout << attributes.name << " ";
		} std::cout << std::endl;
	}

	std::cout << sizeof(GLuint) << std::endl;
	while(!glfwWindowShouldClose(window.handle)) {
		this->pollEvents();


		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT);


		GUInewFrame();
		renderer.start();

		renderer.camera.ortho(
			0.0f, (float)window.width,
			(float)window.height, 0.0f,
			-1.0f, 1.0f
		);
		static bool isDirty = true;
		static int amount = 600;
		int amount2 = amount;
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		//window.displayFPS();
		ImGui::SliderInt("amount1", &amount, 1, 10);
		ImGui::SliderInt("amount2", &amount, 1, 100);
		ImGui::SliderInt("amount3", &amount, 1, 1000);
		ImGui::SliderInt("amount4", &amount, 1, 10000);
		ImGui::SliderInt("amount5", &amount, 1, 100000);
		if(amount != amount2) {
			isDirty = true;
		}

		//if(isDirty) 
		{
			//Rect rect;
			for(int i = 0; i < amount; i++) {
				for(int j = 0; j < amount; j++) {
					Vec2 pos = { 0.0f, 0.0f };
					Vec2 size = { window.width / amount, window.height / amount };
					Vec2 pos2;
					pos2.x = pos.x + size.x * i;
					pos2.y = pos.y + size.y * j;
					if((i + j) % 2) {
						renderer.setColor({ 1.0f, 1.0f, 1.0f, 1.0f });

					} else {
						renderer.setColor({ 0.0f, 0.0f, 0.0f, 1.0f });

					}

					//Triangle({ pos2.x, pos2.y }, { pos2.x + size.x, pos2.y }, { pos2.x, pos2.y + size.y }).draw();
					//renderer.drawTriangle({ pos2.x, pos2.y }, { pos2.x + size.x, pos2.y }, { pos2.x, pos2.y + size.y });
					Rect(pos2, size).draw();
				}
			}
			isDirty = false;
		}
		//renderer.setColor({ 1.0f, 1.0f, 1.0f, 1.0f });
		//for(int i = 0; i < amount; i++) {
		//	Vec2 pos = { 0.0f, 0.0f };
		//	Vec2 size = { window.width / amount, window.height / amount };
		//	Vec2 pos2;

		//	renderer.drawRectangle(pos2 + size * i, size);

		//}

		renderer.end();

		GUIrender();

		glfwSwapBuffers(window.handle);
	}
}

void BaseApp::pollEvents() {

	processInput(window.handle);
	renderer.timeManager.handleTime();
	glfwPollEvents();
}
