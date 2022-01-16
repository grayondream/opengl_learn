#ifndef __SHADER_H__
#define __SHADER_H__


#include <iostream>
#include <glad/glad.h>
#include <string>
#include "utils.h"

using std::string;

enum LEARN_GL_SHADER_TYPE {
	LEARN_GL_SHADER_FRAGMENT,
	LEARN_GL_SHADER_VERTEX,
	LEARN_GL_SHADER_PROGRAM
};

class Shader{
public:
	bool open(const char *vertextPath, const char *fragmentPath) {
		string vertexCode = GUtils::read_file(vertextPath);
		string fragCode = GUtils::read_file(fragmentPath);
		
		const char *vertexSourceCode = vertexCode.c_str();
		const char *fragSourceCode = fragCode.c_str();

		unsigned int fragShaderId = -1, vertexShaderId = -1;

		vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShaderId, 1, &vertexSourceCode, NULL);
		glCompileShader(vertexShaderId);
		if (!checkCompileError(vertexShaderId, LEARN_GL_SHADER_VERTEX)) {
			return false;
		}

		fragShaderId = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragShaderId, 1, &fragSourceCode, NULL);
		glCompileShader(fragShaderId);
		if (!checkCompileError(vertexShaderId, LEARN_GL_SHADER_FRAGMENT)) {
			return false;
		}

		mId = glCreateProgram();
		glAttachShader(mId, vertexShaderId);
		glAttachShader(mId, fragShaderId);
		glLinkProgram(mId);
		if (!checkCompileError(mId, LEARN_GL_SHADER_PROGRAM)) {
			return false;
		}

		glDeleteShader(vertexShaderId);
		glDeleteShader(fragShaderId);
		return true;
	}

public:
	unsigned int getID() const {
		return mId;
	}

	void use() {
		glUseProgram(mId);
	}

	void setBool(const string name, bool value) const {
		glUniform1i(glGetUniformLocation(mId, name.c_str()), static_cast<int>(value));
	}

	void setInt(const string name, int value) const {
		glUniform1i(glGetUniformLocation(mId, name.c_str()), (value));
	}

	void setFloat(const string name, float value) const {
		glUniform1f(glGetUniformLocation(mId, name.c_str()), (value));
	}
private:
	bool checkCompileError(unsigned int id, LEARN_GL_SHADER_TYPE type) {
		int issucess = 0;
		char logBuffer[1024];
		switch (type){
		case LEARN_GL_SHADER_FRAGMENT:
			//go through
		case LEARN_GL_SHADER_VERTEX:
		{
			glGetShaderiv(id, GL_COMPILE_STATUS, &issucess);
			if (!issucess) {
				glGetShaderInfoLog(id, sizeof(logBuffer), NULL, logBuffer);
				return false;
			}
		}
			break;
		case LEARN_GL_SHADER_PROGRAM:
		{
			glGetProgramiv(id, GL_LINK_STATUS, &issucess);
			if (!issucess) {
				glGetProgramInfoLog(id, sizeof(logBuffer), NULL, logBuffer);
				return false;
			}
		}
			break;
		default:
			break;
		}

		return true;
	}

private:
	unsigned int mId;
};

#endif 