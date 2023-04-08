#include <gtc/matrix_transform.hpp>
#include "Quad.h"
#include "Shader.h"
#include "Input.h"

Quad::Quad()
{
	GLfloat vertices[] = {
		 -1.0f,  1.0f, 0.0f,
		  1.0f,  1.0f, 0.0f,  // tringle 1
		 -1.0f, -1.0f, 0.0f,

		 -1.0f, -1.0f, 0.0f,
		  1.0f,  1.0f, 0.0f, // tringle 2
		  1.0f, -1.0f, 0.0f };

	GLfloat colors[] = {
		1.0f,0.0f,1.0f,
		0.0f,0.0f,1.0f, // tringle 1
		0.0f,1.0f,1.0f,

		0.0f,1.0f,1.0f,
		0.0f,0.0f,1.0f, // tringle 2
		0.0f,1.0f,0.0f
	};
	m_buffer.CreateBuffer(6);
	m_buffer.FillVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), Buffer::SINGLE);
	m_buffer.FillVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), Buffer::SINGLE);

	m_buffer.LinkBuffer("vertexIn",Buffer::VERTEX_BUFFER, Buffer::XYZ, Buffer::FLOAT);
	m_buffer.LinkBuffer("colorIn",Buffer::COLOR_BUFFER, Buffer::RGB, Buffer::FLOAT);

	m_position = glm::vec3(0.0f);

}

Quad::~Quad()
{
	m_buffer.DestroyBuffer();
}

void Quad::Render()
{
	Shader::Instance()->SendUniformData("model", m_model);
	m_buffer.Draw(Buffer::TRIANGLES);
}

void Quad::Update()
{
	if (Input::Instance()->IsKeyPressed()) {
		if (Input::Instance()->GetKeyDown() == 'a') {
			m_position.x -= 0.01f;
		}
		else if (Input::Instance()->GetKeyDown() == 'd') {
			m_position.x += 0.01f;
		}
		else if (Input::Instance()->GetKeyDown() == 'w') {
			m_position.y += 0.01f;
		}
		else if (Input::Instance()->GetKeyDown() == 's') {
			m_position.y -= 0.01f;
		}
	}

	m_model = glm::mat4(1.0f);
	m_model = glm::translate(m_model, m_position);
	//m_model = glm::rotate(m_model, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));


}
