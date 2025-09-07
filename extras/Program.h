#pragma once

#include <unordered_map>
#include <string>
#include <glm/glm.hpp>

class Program
{
	unsigned int mProgramID;
	std::string mVertexShaderSource;
	std::string mFragmentShaderSource;
public:
	Program();
	Program(const char* vertexSource, const char* fragmentSource);

	void setVertexAndFragmentSources(const char* vertexSource, const char* fragmentSource);
	void setVertexAndFragmentSources(const std::string& vertexSource, const std::string& fragmentSource);

	std::string getVertexShaderSource() const;
	std::string getFragmentShaderSource() const;

	void useProgram() const;

	void setUniform1integer(const char* name, int value);
	void setUniform1float(const char* name, float value);
	void setUniform3floats(const char* name, float v0, float v1, float v2);
	void setUniformVector3floats(const char* name, const glm::vec3& vec);
	void setUniformMatrix3floats(const char* name, const glm::mat3& matrix);
	void setUniform4floats(const char* name, float v0, float v1, float v2, float v3);
	void setUniformMatrix4floats(const char* name, const glm::mat4& matrix);
};