#include "Shader.h"
#include "GLCore.h"

#include <fstream>
#include <iostream>
#include <string>

Shader::Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath) {
	std::string vertexCode;
	std::string fragmentCode;

	std::ifstream vertexStream(vertexPath);
	std::ifstream fragmentStream(fragmentPath);

	std::string currLine;
	while (std::getline(vertexStream, currLine)) {
		vertexCode += currLine;
		vertexCode += '\n';
	}
	vertexCode += '\0';
	vertexStream.close();

	while (std::getline(fragmentStream, currLine)) {
		fragmentCode += currLine;
		fragmentCode += '\n';
	}
	fragmentCode += '\0';
	fragmentStream.close();

	const char* vertexCodeC = vertexCode.c_str();
	const char* fragCodeC = fragmentCode.c_str();

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexCodeC, NULL);
	glCompileShader(vertexShader);
	LOG_INFO("Compiled vertex shader from " + std::string(vertexPath) + "!");

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragCodeC, NULL);
	glCompileShader(fragmentShader);
	LOG_INFO("Compiled fragment shader from " + std::string(fragmentPath) + "!");

	unsigned int geometryShader = -1;
	if (geometryPath != nullptr) {
		std::string geometryCode;
		std::ifstream geometryStream(geometryPath);

		while (std::getline(geometryStream, currLine)) {
			geometryCode += currLine;
			geometryCode += '\n';
		}
		geometryCode += '\0';
		geometryStream.close();

		const char* geomCodeC = geometryCode.c_str();

		geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometryShader, 1, &geomCodeC, NULL);
		glCompileShader(geometryShader);
		LOG_INFO("Compiled geometry shader from " + std::string(geometryPath) + "!");
	}

	this->id = glCreateProgram();
	glAttachShader(this->id, vertexShader);
	glAttachShader(this->id, fragmentShader);
	if (geometryShader != -1) glAttachShader(this->id, geometryShader);
	glLinkProgram(this->id);
	LOG_INFO("Linked shader program!");

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	if (geometryPath != nullptr) {
		glDeleteShader(geometryShader);
	}
}

void Shader::free() {
	glDeleteProgram(this->id);
}

void Shader::activate() const {
	glUseProgram(this->id);
}

void Shader::setBool(const char* name, bool value) const {
	int location = glGetUniformLocation(this->id, name);
	glUniform1i(location, value);
}

void Shader::setInt(const char* name, int value) const {
	int location = glGetUniformLocation(this->id, name);
	glUniform1i(location, value);
}

void Shader::setFloat(const char* name, float value) const {
	int location = glGetUniformLocation(this->id, name);
	glUniform1f(location, value);
}

void Shader::setVec3f(const char* name, float value1, float value2, float value3) {
	int location = glGetUniformLocation(this->id, name);
	glUniform3f(location, value1, value2, value3);
}

void Shader::setVec3f(const char* name, glm::vec3& vec) {
	int location = glGetUniformLocation(this->id, name);
	glUniform3f(location, vec.x, vec.y, vec.z);
}

void Shader::setVec4f(const char* name, float value1, float value2, float value3, float value4) {
	int location = glGetUniformLocation(this->id, name);
	glUniform4f(location, value1, value2, value3, value4);
}

void Shader::setMat3f(const char* name, bool transpose, const glm::f32* value) {
	int location = glGetUniformLocation(this->id, name);
	glUniformMatrix3fv(location, 1, transpose, value);
}

void Shader::setMat4f(const char* name, bool transpose, const glm::f32* value) {
	int location = glGetUniformLocation(this->id, name);
	glUniformMatrix4fv(location, 1, transpose, value);
}