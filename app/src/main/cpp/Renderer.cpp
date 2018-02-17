//
// Created by Alberto on 15/02/2018.
//

#include "Renderer.h"
#include <EGL/egl.h>
#include <stdlib.h>
#include <GLES3/gl3.h>
#include <android/log.h>
#include "Entity.h"

Renderer::Renderer()
{
	FillDefaultRectangle();
	const char* VertexSource =
        "attribute vec2 aPos;\n"
		"attribute vec4 aColor;\n"
		"uniform vec2 uPos;\n"
		"uniform vec4 uColor;\n"
		"varying vec4 vertexColor;\n"
		"void main () {\n"
			"gl_Position = vec4(aPos, 0.0, 1.0);\n"
			"vertexColor = aColor;\n"
		"}\n\0";

	GLuint vertexShader = CreateShader(VertexSource, GLShader::VERTEX);

	if (!vertexShader)
	{
		return;
	}

	const char* FragmentSource =
        "precision mediump float;\n"
		"varying vec4 vertexColor;\n"
		"void main () {\n"
			"gl_FragColor = vertexColor;\n"
		"}\n\0";

	GLuint fragmentShader = CreateShader(FragmentSource, GLShader::FRAGMENT);

	if (!fragmentShader)
	{
		glDeleteShader(vertexShader);
		return;
	}

	CreateProgram(vertexShader, fragmentShader);
	GetAttribLocations();
	InitBuffers();
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
    glUseProgram(m_iProgram);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glVertexAttribPointer(m_iPosAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glVertexAttribPointer(m_iColorAttribute, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(2*sizeof(float)));
	glEnableVertexAttribArray(m_iPosAttribute);
	glEnableVertexAttribArray(m_iColorAttribute);

	GLint err = glGetError();
	if (err != GL_NO_ERROR) {
		__android_log_print(ANDROID_LOG_ERROR, "CREA", "Error drawing: %i", err);
	}
}

void Renderer::Render(Entity* _pEntity)
{
    glDrawArrays(GL_TRIANGLES, 0, 6);
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_Rectangle), &m_Rectangle[0], GL_DYNAMIC_DRAW);
}

void Renderer::DeleteBuffers()
{
	glDeleteBuffers(1, &m_VBO);
}

void Renderer::GetAttribLocations()
{
	m_iPosAttribute = glGetAttribLocation(m_iProgram, "aPos");
    m_iColorAttribute = glGetAttribLocation(m_iProgram, "aColor");
}

void Renderer::FillDefaultRectangle()
{
	float xOffsets [6] = {0.f, 1.f, 1.f, 0.f, 1.f, 0.f};
	float yOffsets [6] = {0.f, 0.f, 1.f, 0.f, 1.f, 1.f};

	for (int i = 0; i < 6; ++i)
	{
		m_Rectangle[i].m_vPosition[0] = -0.5f + xOffsets[i];
		m_Rectangle[i].m_vPosition[1] = -0.5f + yOffsets[i];
		m_Rectangle[i].m_vColor[0] = 1.f;
		m_Rectangle[i].m_vColor[1] = 1.f;
		m_Rectangle[i].m_vColor[2] = 1.f;
		m_Rectangle[i].m_vColor[3] = 1.f;
	}
}
