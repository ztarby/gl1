#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<glad/glad.h>

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<cerrno>

std::string get_file_contents(const char* filename);

class Shader {
public:
	GLuint ID;
	Shader(const char* vertexfile, const char* fragmentfile);

	void Activate();
	void Delete();
};
#endif // !SHADER_CLASS_H

