#include "Shader.h"

#include <EGL/egl.h>
#include <stdlib.h>
#include <GLES3/gl3.h>
#include <android/log.h>

Shader::Shader(const char* _pVertexSource, const char* _pFragmentSource)
	: m_iRendererID(0)
{
	GLuint vertexShader = CreateShader(_pVertexSource, GLShader::VERTEX);
	GLuint fragmenShader = CreateShader(_pFragmentSource, GLShader::FRAGMENT);
	CreateProgram(vertexShader, fragmenShader);
}

Shader::~Shader()
{
	glDeleteProgram(m_iRendererID);
}

void Shader::Bind()
{
	glUseProgram(m_iRendererID);
}

void Shader::Unbind()
{
	glUseProgram(0);
}

void Shader::SetUniform1i(const std::string& _sName, int _iV)
{
	glUniform1i(GetUniformLocation(_sName), _iV);
}

void Shader::SetUniform2f(const std::string& _sName, float _fV1, float _fV2)
{
	glUniform2f(GetUniformLocation(_sName), _fV1, _fV2);
}

void Shader::SetUniform4f(const std::string& _sName, float _fV1, float _fV2, float _fV3, float _fV4)
{
	glUniform4f(GetUniformLocation(_sName), _fV1, _fV2, _fV3, _fV4);
}

void Shader::SetUniformMatrix4(const std::string& _sName, Matrix4& _matrix)
{
	glUniformMatrix4fv(GetUniformLocation(_sName), 1, GL_FALSE, reinterpret_cast<float*>(&_matrix));
}

unsigned int Shader::CreateShader(const char* _pSource, GLShader _eShaderType)
{
	GLuint iShader = glCreateShader(_eShaderType == GLShader::VERTEX ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);

	if (!iShader)
	{
		__android_log_print(ANDROID_LOG_ERROR, "CREA", "Error creating %s shader", _eShaderType == GLShader::VERTEX ? "vertex" : "fragment");
        return 0;
	}

	glShaderSource(iShader, 1, &_pSource, NULL);
	GLint iCompiled = GL_FALSE;
	glCompileShader(iShader);
	glGetShaderiv(iShader, GL_COMPILE_STATUS, &iCompiled);

	if (!iCompiled)
	{
        GLint infoLogLen = 0;
        glGetShaderiv(iShader, GL_INFO_LOG_LENGTH, &infoLogLen);
        if (infoLogLen > 0) {
            GLchar* infoLog = (GLchar*)malloc(infoLogLen);
            if (infoLog) {
                glGetShaderInfoLog(iShader, infoLogLen, NULL, infoLog);
                __android_log_print(ANDROID_LOG_ERROR, "COMP", "Error compiling %s shader: \n%s", _eShaderType == GLShader::VERTEX ? "vertex" : "fragment", infoLog);
                free(infoLog);
            }
        }
		glDeleteShader(iShader);
        return 0;
	}

	return iShader;
}

void Shader::CreateProgram(unsigned int _iVertexShader, unsigned int _iFragmentShader)
{
	m_iRendererID = glCreateProgram();

	if (!m_iRendererID)
	{
		glDeleteShader(_iVertexShader);
		glDeleteShader(_iFragmentShader);
		return;
	}

	glAttachShader(m_iRendererID, _iVertexShader);
	glAttachShader(m_iRendererID, _iFragmentShader);
	glLinkProgram(m_iRendererID);
	GLint iLinked = GL_FALSE;
	glGetProgramiv(m_iRendererID, GL_LINK_STATUS, &iLinked);

	if (!iLinked)
	{
        __android_log_print(ANDROID_LOG_ERROR, "LINK", "Error linking");
	}

	glDeleteShader(_iVertexShader);
	glDeleteShader(_iFragmentShader);
}

int Shader::GetUniformLocation(const std::string& _sName)
{
	if (m_mUniformLocations.find(_sName) != m_mUniformLocations.end())
	{
		return m_mUniformLocations[_sName];
	}

	int iLocation = glGetUniformLocation(m_iRendererID, _sName.c_str());
	m_mUniformLocations[_sName] = iLocation;
	return iLocation;
}
