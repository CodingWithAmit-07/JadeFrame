#include<JadeFrame.h>


class App : public BaseApp {
public:
public:
	void setup() {}
	void update() {}
	void draw() {}
};


int main(void) {
	//std::string t = "Test";
	//BaseApp* app = new App();
	//app->init_app(t, 1800, 800);
	//app->run_app();

	std::string t = "Test";
	App app;
	app.init_app(t, 1800, 800);
	app.run_app();
	return 0;
}

