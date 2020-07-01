#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>


class Shader {
private:
	unsigned int ID;

	void checkCompileErrors(unsigned int shader, std::string type)
	{
		int success;
		char infoLog[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
	}
public:
	void Use() { glUseProgram(ID); };

	Shader(const char* vShadePath, const char* fShaderPath) {
		std::string vCodeShader;
		std::string fCodeShader;
		std::ifstream vFileShader;
		std::ifstream fFileShader;

		vFileShader.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fFileShader.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try {
			vFileShader.open(vShadePath);
			fFileShader.open(fShaderPath);

			std::stringstream vStringShader, fStringShader;
			vStringShader << vFileShader.rdbuf();
			fStringShader << fFileShader.rdbuf();

			vFileShader.close();
			fFileShader.close();

			vCodeShader = vStringShader.str();
			fCodeShader = fStringShader.str();
		}
		catch (std::ifstream::failure & e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}

		const char* vShader = vCodeShader.c_str();
		const char* fShader = fCodeShader.c_str();

		unsigned int vertexShader, fragmentShader;

		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vShader, NULL);
		glCompileShader(vertexShader);
		checkCompileErrors(vertexShader, "VERTEX");

		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fShader, NULL);
		glCompileShader(fragmentShader);
		checkCompileErrors(vertexShader, "FRAGMENT");

		ID = glCreateProgram();
		//set shaders in programe and Link
		glAttachShader(ID, vertexShader);
		glAttachShader(ID, fragmentShader);
		glLinkProgram(ID);
		checkCompileErrors(vertexShader, "PROGRAM");

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	void SetFloat(std::string& name, float value) const{
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}
};
#endif // !__SHADER_H__

