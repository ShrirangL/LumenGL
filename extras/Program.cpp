#include "Program.h"
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

Program::Program()
{
	mProgramID = glCreateProgram();
	setVertexAndFragmentSources(nullptr, nullptr);
}

Program::Program(const char* vertexSource, const char* fragmentSource)
{
	mProgramID = glCreateProgram();

	setVertexAndFragmentSources(vertexSource, fragmentSource);
}

void Program::setVertexAndFragmentSources(const char* vertexSource, const char* fragmentSource)
{
	if (vertexSource || fragmentSource)
	{
		//Create and compile vertex shader
		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

		if (vertexSource)
		{
			glShaderSource(vertexShader, 1, &vertexSource, nullptr);
			glCompileShader(vertexShader);
			mVertexShaderSource = vertexSource;
		}

		//Create and compile fragment shader
		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		if (fragmentSource)
		{
			glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
			glCompileShader(fragmentShader);
			mFragmentShaderSource = fragmentSource;
		}

		//Link shaders into program
		glAttachShader(mProgramID, vertexShader);
		glAttachShader(mProgramID, fragmentShader);
		glLinkProgram(mProgramID);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}
}

void Program::setVertexAndFragmentSources(const std::string& vertexSource, const std::string& fragmentSource)
{
	setVertexAndFragmentSources(vertexSource.c_str(), fragmentSource.c_str());
}

std::string Program::getVertexShaderSource() const
{
	return mVertexShaderSource;
}

std::string Program::getFragmentShaderSource() const	
{
	return mFragmentShaderSource;
}

void Program::useProgram() const
{
	glUseProgram(mProgramID);
}

void Program::setUniform1integer(const char* name, int value)
{
	useProgram();
	glUniform1i(glGetUniformLocation(mProgramID, name), value);
}

void Program::setUniform1float(const char* name, float value) 
{
	useProgram();
	glUniform1f(glGetUniformLocation(mProgramID, name), value);
}

void Program::setUniform3floats(const char* name, float v0, float v1, float v2) 
{
	useProgram();
	glUniform3f(glGetUniformLocation(mProgramID, name), v0, v1, v2);
}

void Program::setUniformVector3floats(const char* name, const glm::vec3& vec)
{
	useProgram();
	glUniform3fv(glGetUniformLocation(mProgramID, name), 1, &vec[0]);
}


void Program::setUniformMatrix3floats(const char* name, const glm::mat3& matrix)
{
	useProgram();
	glUniformMatrix3fv(glGetUniformLocation(mProgramID, name),1, GL_FALSE, &matrix[0][0]);
}

void Program::setUniform4floats(const char* name, float v0, float v1, float v2, float v3)
{
	useProgram();
	glUniform4f(glGetUniformLocation(mProgramID, name), v0, v1, v2, v3);
}

void Program::setUniformMatrix4floats(const char* name, const glm::mat4& matrix)
{
	useProgram();
	glUniformMatrix4fv(glGetUniformLocation(mProgramID, name), 1, GL_FALSE, &matrix[0][0]);
}


