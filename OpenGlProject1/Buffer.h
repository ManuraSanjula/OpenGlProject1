#pragma once
#include "glad.h"
#include <iostream>
#include <string>

class Buffer
{
public:
	enum VBOType {
		VERTEX_BUFFER,
		COLOR_BUFFER,
	};
	enum ComponentType {
		XY = 2, XYZ = 3, RGB = 3, RGBA = 4, UV = 2
	};
	enum FillType
	{
		SINGLE = GL_STATIC_DRAW,
		MULTIPLE = GL_DYNAMIC_DRAW
	};
	enum DataType {
		INT = GL_INT, FLOAT = GL_FLOAT, UNSIGNED_INT = GL_UNSIGNED_INT
	};
	enum DrawType {
		POINTS = GL_POINTS,
		TRIANGLES = GL_TRIANGLES,
		LINES = GL_LINES,
	};
public:
	Buffer();
public:
	void CreateBuffer(GLuint totalVertices);

	void FillVBO(VBOType VBOType,
		GLfloat* data,
		GLsizeiptr bufferSize,
		FillType fillType);

	void LinkBuffer(const std::string& attribute,
					VBOType vboType,
					ComponentType componentType,
					DataType dataType);

	void Draw(DrawType drawType);

	void DestroyBuffer();
private:
	GLuint m_VAO;
	GLuint m_vertexVBO;
	GLuint m_colorVBO;
	GLuint m_totalVertices;
};

