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
	const char* VertexSource =
		"#version 300 es\n"
		"layout (location = 0) in vec2 aPos;\n"
		"layout (location = 1) in vec4 aColor;\n"
		"out vec4 vertexColor;\n"
		"void main () {\n"
			"gl_Position = vec4(aPos, 0.0, 1.0);\n"
			"vertexColor = aColor;\n"
		"}\n";

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	if (!vertexShader)
	{
		__android_log_print(ANDROID_LOG_ERROR, "VS", "Error creating vertex shader");
        return;
	}

	glShaderSource(vertexShader, 1, &VertexSource, NULL);
	GLint iCompiled = GL_FALSE;
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &iCompiled);

	if (!iCompiled)
	{

        GLint infoLogLen = 0;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &infoLogLen);
        if (infoLogLen > 0) {
            GLchar* infoLog = (GLchar*)malloc(infoLogLen);
            if (infoLog) {
                glGetShaderInfoLog(vertexShader, infoLogLen, NULL, infoLog);
                __android_log_print(ANDROID_LOG_ERROR, "VS", "Error compiling vertex shader: \n%s", infoLog);
                free(infoLog);
            }
        }
		glDeleteShader(vertexShader);
        return;
	}

	const char* FragmentSource =
		"#version 300 es\n"
		"in vec4 vertexColor;\n"
		"out vec4 fragColor;\n"
		"void main () {\n"
			"fragColor = vertexColor;\n"
		"}\n\0";

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	if (!fragmentShader)
	{
		__android_log_print(ANDROID_LOG_ERROR, "FS", "Error creating fragment shader");
        glDeleteShader(vertexShader);
        return;
	}

	glShaderSource(fragmentShader, 1, &FragmentSource, NULL);
	iCompiled = GL_FALSE;
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &iCompiled);

	if (!iCompiled)
	{
		__android_log_print(ANDROID_LOG_ERROR, "FS", "Error compiling fragment shader");
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
        return;
	}

	m_iProgram = glCreateProgram();

	if (!m_iProgram)
	{
		//TODO: handle error
	}
	glAttachShader(m_iProgram, vertexShader);
	glAttachShader(m_iProgram, fragmentShader);
	glLinkProgram(m_iProgram);
	GLint iLinked = GL_FALSE;
	glGetProgramiv(m_iProgram, GL_LINK_STATUS, &iLinked);

	if (!iLinked)
	{
        __android_log_print(ANDROID_LOG_ERROR, "PR", "Error linking");
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Renderer::~Renderer()
{
}

void Renderer::PreRender()
{
    glClearColor(0.678431373f, 0.847058824f, 0.901960784f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Render(Entity* _pEntity)
{
	
}
