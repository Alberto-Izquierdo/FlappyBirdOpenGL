//
// Created by Alberto on 15/02/2018.
//

#include "Renderer.h"
#include <EGL/egl.h>
#include <stdlib.h>
#include <GLES3/gl3.h>
#include <android/log.h>

Renderer::Renderer()
{
    m_vIndices[0] = 0;
    m_vIndices[1] = 1;
    m_vIndices[2] = 2;
    m_vIndices[3] = 2;
    m_vIndices[4] = 3;
    m_vIndices[5] = 0;

	const char* VertexSource =
		"#version 300 es\n"
		"layout (location = 0) in vec2 aPos;\n"
		"layout (location = 1) in vec4 aColor;\n"
		"out vec4 vertexColor;\n"
		"void main () {\n"
			"gl_Position = vec4(aPos, 0.0, 1.0);\n"
			"vertexColor = aColor;\n"
		"}\n";

	GLuint vertexShader = CreateShader(VertexSource, GLShader::VERTEX);

	if (!vertexShader)
	{
		return;
	}

	const char* FragmentSource =
		"#version 300 es\n"
		"in vec4 vertexColor;\n"
		"out vec4 fragColor;\n"
		"void main () {\n"
			"fragColor = vertexColor;\n"
		"}\n\0";

	GLuint fragmentShader = CreateShader(FragmentSource, GLShader::FRAGMENT);

	if (!fragmentShader)
	{
		glDeleteShader(vertexShader);
		return;
	}

	CreateProgram(vertexShader, fragmentShader);
	InitBuffers();
	InitAttribPointers();
}

Renderer::~Renderer()
{
	DeleteBuffers();
	glDeleteProgram(m_iProgram);
}

void Renderer::PreRender()
{
    glClearColor(0.678431373f, 0.847058824f, 0.901960784f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Render(Entity* _pEntity)
{
	
}

unsigned int Renderer::CreateShader(const char* _pSource, GLShader _eShaderType)
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

void Renderer::CreateProgram(unsigned int _iVertexShader, unsigned int _iFragmentShader)
{
	m_iProgram = glCreateProgram();

	if (!m_iProgram)
	{
		glDeleteShader(_iVertexShader);
		glDeleteShader(_iFragmentShader);
		return;
	}

	glAttachShader(m_iProgram, _iVertexShader);
	glAttachShader(m_iProgram, _iFragmentShader);
	glLinkProgram(m_iProgram);
	GLint iLinked = GL_FALSE;
	glGetProgramiv(m_iProgram, GL_LINK_STATUS, &iLinked);

	if (!iLinked)
	{
        __android_log_print(ANDROID_LOG_ERROR, "LINK", "Error linking");
	}

	glDeleteShader(_iVertexShader);
	glDeleteShader(_iFragmentShader);
}

void Renderer::InitBuffers()
{
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(QUAD), &QUAD[0], GL_STATIC_DRAW);

	glGenBuffers(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_vIndices), m_vIndices, GL_STATIC_DRAW);
}

void Renderer::DeleteBuffers()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);
}

void Renderer::InitAttribPointers()
{
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(Vertex), (void*)(2*sizeof(float)));
	glEnableVertexAttribArray(1);
}
