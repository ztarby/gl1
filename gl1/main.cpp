#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"VBO.h"
#include"VAO.h"
#include"EBO.h"
#include"shaderClass.h"


int main(){
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	 GLFWwindow* window = glfwCreateWindow(800,800,"tst",NULL,NULL);
	 if (window == NULL) {
		 std::cout << "fail :CCC";
		 return -1 ;
		 glfwTerminate();
	 }

	 GLfloat vertices[] =
	 {
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
		 - 0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, 
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, 
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f
	 };
	 GLuint indices[] =
	 {
		 0, 3, 5, // Lower left triangle
		 3, 2, 4, // Lower right triangle
		 5, 4, 1 // Upper triangle
	 };

	 glfwMakeContextCurrent(window);
	 gladLoadGL();
	 glViewport(0,0,800,800);

	 Shader shaderProgram("default.vert", "default.frag");

	 VAO VAO1;
	 VAO1.Bind();

	 VBO VBO1(vertices, sizeof(vertices));

	 EBO EBO1(indices, sizeof(indices));

	 VAO1.LinkVBO(VBO1, 0);

	 VAO1.Unbind();
	 VBO1.Unbind();
	 EBO1.Unbind();



	 glfwSwapBuffers(window);

	 while (!glfwWindowShouldClose(window)) {
		 glClearColor(0.08f, 0.13f, 0.17f, 1.0f);
		 glClear(GL_COLOR_BUFFER_BIT);
		 shaderProgram.Activate();
		 VAO1.Bind();
		 glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		 glfwSwapBuffers(window);

		 glfwPollEvents();
	 }


	 VAO1.Delete();
	 VBO1.Delete();
	 EBO1.Delete();
	 shaderProgram.Delete();

	 glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}