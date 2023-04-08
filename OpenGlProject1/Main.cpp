#include <iostream>
#include "Screen.h"
#include "Input.h"
#include "glad.h"
#include "Shader.h"
#include "Quad.h"

bool isAppRunning = true;

int main(int argc, char* argv[]) {

	Screen::Instance()->Initialize();

	Shader::Instance()->CreateProgram();
	Shader::Instance()->CreateShaders();

	Shader::Instance()->CompileShaders("Shaders/Main.vert", Shader::VERTES_SHADER);
	Shader::Instance()->CompileShaders("Shaders/Main.frag", Shader::FRAGMENT_SHADER);

	Shader::Instance()->AttachShaders();
	Shader::Instance()->LinkProgram();

	Quad quad;

	while (isAppRunning) {
		Screen::Instance()->ClearScreen();
		Input::Instance()->Update();

		isAppRunning = !Input::Instance()->IsXClicked();

		quad.Update();
		quad.Render();
		Screen::Instance()->Present();
	}
	
	Shader::Instance()->DetachShaders();
	Shader::Instance()->DestroyShaders();
	Shader::Instance()->DestroyProgram();

	Screen::Instance()->Shutdown();
	return 0;
} 