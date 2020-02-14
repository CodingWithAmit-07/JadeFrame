#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"

#include <vector>
#include <iostream>
#include "math/Vec3.h"
#include "math/Vec2.h"
#include "math/Mat4.h"
#include "Mesh.h"

class Camera {
public:
	Camera();
	void update();
	void ortho(float left, float right, float buttom, float top, float zNear, float zFar);
private:
	Mat4 model;
	Mat4 view;
	Mat4 proj;
	Mat4* currentMatrix;
};
class TimeManager {
public:
	void handleTime();
private:
	double currentTime = 0.0;
	double previousTime = 0.0;
	double drawTime = 0.0;
	double frameTime = 0.0;
	double updateTime = 0.0;
	double targetTime = 0.0;
};


class Renderer {
public:
	Renderer();
	void init(Shader* shader);
	void start();
	void end();

private:
	struct BufferData {
		std::vector<Vertex> vertices;
		std::vector<GLuint> indices;

		GLuint VBO = 0;
		GLuint VAO = 0;
		GLuint IBO = 0;

		GLuint vertexOffset = 0;
		GLuint indexOffset = 0;

		GLuint vertexCount = 0;
		GLuint indexCount = 0;

		void init();
		void add(Mesh& mesh);
		void update();
		void draw();
	};
	BufferData bufferData;
	Shader* currentShader = nullptr;

	//Drawing API
public:
	void setColor(const Color& color);
	void drawRectangle(Vec2 pos, Vec2 size);
	void drawTriangle(Vec3 pos1, Vec3 pos2, Vec3 pos3);
private:
	static Color currentColor;

public:
	Camera camera;
	TimeManager timeManager;
};