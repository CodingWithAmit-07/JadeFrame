#include "BaseApp.h"
#include <iostream>
#include "GUI.h"
#include "math/Math.h"
#include <stdint.h>

BaseApp* BaseApp::instance = nullptr;
BaseApp::BaseApp() {}

BaseApp::~BaseApp() {
}

auto BaseApp::init_app(const std::string& title, Vec2 size) -> void {
	instance = this;
	m_window.init(title, size);
	m_shader.init();
	m_renderer.init(&m_shader);

	//m_input.setWindowInstance(m_window.get_handle());
}



auto print_GPU_variable_info() -> void {

	auto& m_shader = BaseApp::get_app_instance()->m_shader;

	std::cout << "Uniforms: ";
	for (auto uniform : m_shader.m_uniforms) {
		std::cout << uniform.name << " ";
	} std::cout << std::endl;

	std::cout << "Attribs : ";
	for (auto attributes : m_shader.m_attributes) {
		std::cout << attributes.name << " ";
	} std::cout << std::endl;
}


auto BaseApp::run_app() -> void {

	DISPLAY_DEVICEW display_device_info;



	GUI_init(get_window().m_window_handle);

	print_GPU_variable_info();
	static Vec3 camPos = { 0, 10, 10 };

	cam.perspective(
		camPos,
		to_radians(45.0f),
		m_window.get_width() / m_window.get_height(),
		0.1f,
		100.0f
	);
	m_renderer.matrix_stack.projection_matrix = cam.get_projection_matrix();


	m_renderer.gl_cache.set_clear_color({ 0.2f, 0.2f, 0.2f, 1.0f });
	HDC device_context = GetDC(m_window.m_window_handle);
	

	glEnable(GL_DEPTH_TEST);
	while (get_window().m_is_running) {
		SwapBuffers(device_context);


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		this->poll_events();


		GUI_new_frame();

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		{

			{
				m_renderer.start(PRIMITIVE_TYPE::LINES);
				cam.move();
				cam.update();
				m_renderer.matrix_stack.view_matrix = cam.get_view_matrix();

				for (float i = -10; i <= 10; i += 1.0f) {
					m_renderer.set_color({ 0.5f, 0.8f, 0.5f, 1.0f }); MeshManager::make_line({ i, -10, 0 }, { i, 10, 0 }).send_to_buffer(); // RED X
				}
				for (float i = -10; i <= 10; i += 1.0f) {
					m_renderer.set_color({ 0.8f, 0.5f, 0.5f, 1.0f }); MeshManager::make_line({ -10, i, 0 }, { 10, i, 0 }).send_to_buffer(); // RED X
				}

				m_renderer.set_color({ 1.0f, 0.0f, 0.0f, 1.0f }); MeshManager::make_line({ 0, 0, 0 }, { 10, 0, 0 }).send_to_buffer(); // RED X
				m_renderer.set_color({ 0.0f, 1.0f, 0.0f, 1.0f }); MeshManager::make_line({ 0, 0, 0 }, { 0, 10, 0 }).send_to_buffer(); // GREEN Y
				m_renderer.set_color({ 0.0f, 0.0f, 1.0f, 1.0f }); MeshManager::make_line({ 0, 0, 0 }, { 0, 0, 10 }).send_to_buffer(); // BLUE Z

				m_renderer.set_color({ 0.5f, 0.0f, 0.0f, 1.0f }); MeshManager::make_line({ 0, 0, 0 }, { -10, 0, 0 }).send_to_buffer(); // RED X
				m_renderer.set_color({ 0.0f, 0.5f, 0.0f, 1.0f }); MeshManager::make_line({ 0, 0, 0 }, { 0, -10, 0 }).send_to_buffer(); // GREEN Y
				m_renderer.set_color({ 0.0f, 0.0f, 0.5f, 1.0f }); MeshManager::make_line({ 0, 0, 0 }, { 0, 0, -10 }).send_to_buffer(); // BLUE Z

				m_renderer.end();
			}


			{
				PRIMITIVE_TYPE pt = PRIMITIVE_TYPE::TRIANGLES;

				m_renderer.start(pt);
				cam.move();
				cam.update();
				m_renderer.matrix_stack.view_matrix = cam.get_view_matrix();

				static Vec3 cubePos;
				ImGui::SliderFloat("cubePosX", &cubePos.x, -30, 30);
				ImGui::SliderFloat("cubePosY", &cubePos.y, -30, 30);
				ImGui::SliderFloat("cubePosZ", &cubePos.z, -30, 30);
				//if (m_input_manager.is_key_press(EKey::B))
				{
					m_renderer.set_color({ 0.0f, 0.0, 0.0f, 1.0f }); MeshManager::make_cube(cubePos, { 1.0f, 1.0f, 1.0f }).send_to_buffer(); // RED X


					m_renderer.set_color({ 1.0f, 0.0, 0.0f, 1.0f }); MeshManager::make_cube({ 5, 5, 5 }, { 1.0f, 1.0f, 100.0f }).send_to_buffer(); // RED X
					m_renderer.set_color({ 1.0f, 1.0, 0.0f, 1.0f }); MeshManager::make_cube({ 5, -5, 5 }, { 1.0f, 1.0f, 100.0f }).send_to_buffer(); // YELLOW X
					m_renderer.set_color({ 1.0f, 0.0, 1.0f, 1.0f }); MeshManager::make_cube({ -5, 30, 5 }, { 1.0f, 1.0f, 100.0f }).send_to_buffer(); // VIOLET X
					m_renderer.set_color({ 1.0f, 1.0, 1.0f, 1.0f }); MeshManager::make_cube({ -5, -5, 5 }, { 1.0f, 1.0f, 100.0f }).send_to_buffer(); // WHITE X


				}

				m_renderer.end();
			}
		}
		GUI_render();

		get_window().display_FPS();

	}
}


auto BaseApp::poll_events() -> void {
	m_input_manager.handle_input();



	MSG message;
	while (PeekMessageW(&message, NULL, 0, 0, PM_REMOVE)) {
		if (message.message == WM_QUIT) {
			m_window.m_is_running = false;
			return;
		}
		TranslateMessage(&message);
		DispatchMessageW(&message);
	}
}