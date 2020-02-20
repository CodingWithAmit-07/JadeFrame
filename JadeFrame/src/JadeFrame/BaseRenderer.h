#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "BaseShader.h"

#include <vector>
#include <array>
#include <iostream>
#include "math/Vec3.h"
#include "math/Vec2.h"
#include "math/Mat4.h"
#include "Mesh.h"
#include <stack>

class Camera2 {
public:
	Camera2();
};
class TimeManager2 {
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

class BaseRenderer {
public:
	BaseRenderer();
	void init(BaseShader* shader);
	void start();
	void end();

	//private:
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
		void resetCounters();
	};
	BufferData bufferData;
	BaseShader* currentShader = nullptr;

	//Drawing API
public:
	void setColor(const Color& color);
	void setClearColor(const Color& color);
private:
	Color currentColor = { 0.5f, 0.5f, 0.5f, 1.0f };
public:
	void updateMatrices();
	void ortho(float left, float right, float buttom, float top, float zNear, float zFar);
	void perspective(float fovy, float aspect, float zNear, float zFar);
	void translate(float x, float y, float z);
	void rotate(float angle, float x, float y, float z);
	void scale(float x, float y, float z);
	//private:
	Mat4 modelMatrix;
	Mat4 viewMatrix;
	Mat4 projectionMatrix;
	Mat4* currentMatrix;
	Mat4 transformMatrix;
	bool useTransformMatrix;
public:
	void pushMatrix();
	void popMatrix();
private:
	std::stack<Mat4> matrixStack;


public:
	Camera2 camera;
	TimeManager2 timeManager;
};