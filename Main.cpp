#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>


#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Grid.h"
#include"Tile_plain.h"
#include"Map.h"
#include"ColorPicker.h"

const unsigned int width = 2880, height = 1620;

// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS     //
	-0.5f, -0.5f,  0.0f,     1.0f, 0.0f, 0.0f,	
	-0.5f,  0.5f,  0.0f,     0.0f, 1.0f, 0.0f,	
	 0.5f, -0.5f,  0.0f,     0.0f, 0.0f, 1.0f,	
	 0.5f,  0.5f,  0.0f,     1.0f, 1.0f, 1.0f,	
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	1, 2, 3,
};

	
void update(GLFWwindow* window, float& red, float& green, float& blue,float delta=1.0/60.0) {
	float speed = 1;
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS&& glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS)
	{
		red += speed*delta;
	}
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS)
	{
		red -= speed * delta;
	}

	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS)
	{
		green += speed * delta;
	}
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS)
	{
		green -= speed * delta;
	}

	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS)
	{
		blue += speed * delta;
	}
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS)
	{
		blue -= speed * delta;
	}
	blue = std::max(blue, 0.0f);
	green = std::max(green, 0.0f);
	red = std::max(red, 0.0f);
	blue = std::min(blue, 1.0f);
	green = std::min(green, 1.0f);
	red = std::min(red, 1.0f);
}

void onclick(GLFWwindow* window) {

	double mouseX;
	double mouseY;
	// Fetches the coordinates of the cursor
	glfwGetCursorPos(window, &mouseX, &mouseY);

}

int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		
	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(width, height, "3D editor", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, width, height);



	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");
	Shader gridShader("Grid.vert", "Grid.frag");
	Shader tileShaderOn("default.vert", "default.frag");
	
	Map world(height,width,-1,-1,9.0/16.0,1,75,75,tileShaderOn, tileShaderOn);
	Grid grid(51,-1,9.0/16.0*2-1,-1,1);
	ColorPicker picker(height, width, 1.0/8.0, -1, 7.0 / 16.0, 6.0/9.0, 100, 100, "default.vert", "default.frag");
	picker.setRainbow();
	ColorPicker picker_white(height, width, 1.0/8.0, 1.0/3.0, 7.0 / 16.0, 1.0/9.0, 100, 1, "default.vert", "default.frag");
	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	

	//glEnable(GL_DEPTH_TEST);
	float rotation = 0;
	double prevTime = glfwGetTime();

	float red = 1, green = 0, blue = 0;
	Color curColor(1, 1, 1),pColor(1,1,1);
	
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(curColor.r, curColor.g, curColor.b, 1.0f);
		//glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		//shaderProgram.Activate();
		tileShaderOn.Activate();
		

		world.Update(window, curColor.r, curColor.g, curColor.b);
		world.Update(window, curColor.r, curColor.g, curColor.b);
		world.Update(window, curColor.r, curColor.g, curColor.b);
		world.Update(window, curColor.r, curColor.g, curColor.b);
		//std::cout << curColor.r << ' ' << curColor.g << ' ' << curColor.b << std::endl;
		
		world.Draw_On();

		picker.Draw();
		pColor = picker.getColor(window);
		picker_white.setWhite(pColor);
		curColor = picker_white.getColor(window);
		picker_white.Draw();
		
		gridShader.Activate();
		grid.Draw(gridShader);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}



	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	gridShader.Delete();
	
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}