#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<vector>

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
	-0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.10f, 0.2f,  0.02f, // Lower left corner
	 0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.13f, 0.4f,  0.02f, // Lower right corner
	 0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f,     0.16f, 0.6f,  0.32f, // Upper corner
	-0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.19f, 0.8f, 0.17f, // Inner left
	 0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.22f, 0.10f, 0.17f, // Inner right
	 0.0f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.25f, 0.12f,  0.02f  // Inner down
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

	 VAO1.LinkAttrVBO(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	 VAO1.LinkAttrVBO(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	 VAO1.Unbind();
	 VBO1.Unbind();
	 EBO1.Unbind();

	 GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	 glfwSwapBuffers(window);

	 while (!glfwWindowShouldClose(window)) {
		 glClearColor(0.08f, 0.13f, 0.17f, 1.0f);
		 glClear(GL_COLOR_BUFFER_BIT);
		 shaderProgram.Activate();
		 glUniform1f(uniID, 0.4f);

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