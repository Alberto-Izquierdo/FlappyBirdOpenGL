#include "Shaders.h"

const char* Shaders::entitiesVertexSource =
	"attribute vec2 aPos;\n"
	"uniform vec4 uPos;\n"
	"uniform vec4 uColor;\n"
	"uniform mat4 uTransformationMatrix;\n"
	"varying vec4 vertexColor;\n"
	"vec2 finalPosition;\n"
	"vec4 vPosition;\n"
	"void main () {\n"
		"gl_Position = uTransformationMatrix * vec4(aPos, 0.0, 1.0) + uPos;\n"
		"vertexColor = uColor;\n"
	"}\n\0";

const char* Shaders::entitiesFragmentSource =
	"precision mediump float;\n"
	"varying vec4 vertexColor;\n"
	"void main () {\n"
		"gl_FragColor = vertexColor;\n"
	"}\n\0";
