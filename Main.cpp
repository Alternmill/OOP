#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<boost/di.hpp>

#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Grid.h"
#include"Tile_plain.h"
#include"Map.h"
#include"ColorPicker.h"
#include"WhiteColorPicker.h"
#include"Manager.h"
const unsigned int width = 2880, height = 1620;

int main()
{

	glfwInit();

	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		

	GLFWwindow* window = glfwCreateWindow(width, height, "3D editor", NULL, NULL);
	
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent(window);

	gladLoadGL();
	
	glViewport(0, 0, width, height);

	Shader gridShader("Grid.vert", "Grid.frag");
	Shader tileShaderOn("default.vert", "default.frag");
	
	Grid grid(51,-1,9.0/16.0*2-1,-1,1);
	
	Manager* manager = Manager::GetInstance(
		new Map(window, height, width, -1, -1, 9.0 / 16.0, 1, 50, 50, tileShaderOn, tileShaderOn),
		new ColorPicker(window, height, width, 1.0 / 8.0, -1, 7.0 / 16.0, 6.0 / 9.0, 100, 100, "default.vert", "default.frag"),
		new WhiteColorPicker(window, height, width, 1.0 / 8.0, 1.0 / 3.0, 7.0 / 16.0, 1.0 / 9.0, 100, 1, "default.vert", "default.frag"));
	Color curColor(1, 1, 1),pColor(1,1,1);

	double mousex, mousey;
	while (!glfwWindowShouldClose(window))
	{
		
		glClearColor(curColor.r, curColor.g, curColor.b, 1.0f);
		
		glClear(GL_COLOR_BUFFER_BIT);
		
		
		glfwGetCursorPos(window, &mousex, &mousey);
		
		manager->update(mousex, mousey,curColor,pColor);
		((WhiteColorPicker*)manager->get_whiteness_picker())->setWhite(pColor);
		curColor = ((WhiteColorPicker*)manager->get_whiteness_picker())->getColor();

		tileShaderOn.Activate();
		manager->draw();
		
		gridShader.Activate();
		grid.Draw(gridShader);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	tileShaderOn.Delete();
	gridShader.Delete();
	
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}