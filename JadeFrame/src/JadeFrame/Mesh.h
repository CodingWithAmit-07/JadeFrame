#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

#include "math/Vec2.h"
#include "math/Vec3.h"


class Color {
public:
	float r, g, b, a;
};

struct Vertex {
	Vec3 position;
	Color color;
};




class Mesh {
public:
	inline GLuint vertexBufferSize() const {
		return this->vertices.size() * sizeof(Vertex);
	};
	inline GLuint indexBufferSize() const {
		return this->indices.size() * sizeof(GLuint);
	};
	//public:

	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
};

class MeshManager {
public:
	static Mesh makeRectangle(Vec3 pos, Vec3 size);

	static Mesh makeTriangle(Vec3 pos1, Vec3 pos2, Vec3 pos3);
};
class Rect {
public:
	Rect()
		: position()
		, size() {

	}
	Rect(Vec2 position, Vec2 size)
		: position(position)
		, size(size) {

	}

	void draw();
	Vec2 position;
	Vec2 size;
};
class Triangle {
public:
	Triangle()
		: pos1()
		, pos2()
		, pos3(){

	}
	Triangle(Vec2 pos1, Vec2 pos2, Vec3 pos3)
		: pos1(pos1)
		, pos2(pos2)
		, pos3(pos3){

	}

	void draw();
	Vec2 pos1, pos2, pos3;
};