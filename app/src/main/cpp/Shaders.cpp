#include "Shaders.h"

const char* Shaders::entitiesVertexSource =
	"attribute vec2 aPos;\n"
	"attribute vec2 aTexCoord;\n"
	"uniform vec4 uPos;\n"
	"uniform mat4 uTransformationMatrix;\n"
	"varying vec2 vTexCoord;\n"
	"void main () {\n"
		"gl_Position = uTransformationMatrix * vec4(aPos, 0.0, 1.0) + uPos;\n"
		"vTexCoord = aTexCoord;\n"
	"}\n\0";

const char* Shaders::entitiesFragmentSource =
	"precision mediump float;\n"
	"uniform sampler2D uTexture;\n"
	"uniform float uYMaxTexCoord;\n"
	"varying vec2 vTexCoord;\n"
	"float yCoord;\n"
	"void main () {\n"
		"yCoord = vTexCoord.y* 10.0;\n"
		"while (yCoord > uYMaxTexCoord) {;\n"
			"yCoord -= uYMaxTexCoord;\n"
		"}\n"
		"gl_FragColor = texture2D(uTexture, vec2(vTexCoord.x, yCoord));\n"
	"}\n\0";

const char* Shaders::playerVertexSource =
	"attribute vec2 aPos;\n"
	"attribute vec2 aTexCoord;\n"
	"uniform vec4 uPos;\n"
	"uniform mat4 uTransformationMatrix;\n"
	"varying vec2 vTexCoord;\n"
	"void main () {\n"
		"gl_Position = uTransformationMatrix * vec4(aPos, 0.0, 1.0) + uPos;\n"
		"vTexCoord = aTexCoord;\n"
	"}\n\0";

const char* Shaders::playerFragmentSource =
	"precision mediump float;\n"
	"uniform sampler2D uTexture;\n"
	"varying vec2 vTexCoord;\n"
	"void main () {\n"
		"gl_FragColor = texture2D(uTexture, vTexCoord);\n"
	"}\n\0";

const char* Shaders::popupVertexSource =
	"attribute vec2 aPos;\n"
	"attribute vec2 aTexCoord;\n"
	"varying vec2 vTexCoord;\n"
	"void main () {\n"
		"gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
		"vTexCoord = aTexCoord;\n"
	"}\n\0";

const char* Shaders::popupFragmentSource =
	"precision mediump float;\n"
	"uniform sampler2D uTexture;\n"
	"varying vec2 vTexCoord;\n"
	"void main () {\n"
		"gl_FragColor = texture2D(uTexture, vTexCoord);\n"
	"}\n\0";

const char* Shaders::numberVertexSource =
	"attribute vec2 aPos;\n"
	"attribute vec2 aTexCoord;\n"
	"uniform vec2 uPos;\n"
	"varying vec2 vTexCoord;\n"
	"void main () {\n"
		"gl_Position = vec4(aPos.x + uPos.x, aPos.y, 0.0, 1.0);\n"
		"vTexCoord = aTexCoord;\n"
	"}\n\0";

const char* Shaders::numberFragmentSource =
	"precision mediump float;\n"
	"uniform sampler2D uTexture;\n"
	"uniform vec2 uTexCoordOffset;\n"
	"varying vec2 vTexCoord;\n"
	"void main () {\n"
		"gl_FragColor = texture2D(uTexture, vec2(vTexCoord.x + uTexCoordOffset.x, vTexCoord.y + uTexCoordOffset.y));\n"
	"}\n\0";

const char* Shaders::backgroundVertexSource =
	"attribute vec2 aPos;\n"
	"attribute vec2 aTexCoord;\n"
	"uniform float uTime;\n"
	"varying vec2 vTexCoord;\n"
	"varying float vTime;\n"
	"void main() {\n"
		"gl_Position = vec4(aPos, 0.0, 1.0);\n"
		"vTexCoord = aTexCoord;\n"
		"vTime = uTime;\n"
	"}\n";

const char* Shaders::backgroundFragmentSource =
	"precision mediump float;\n"
	"uniform sampler2D uTexture;\n"
	"varying vec2 vTexCoord;\n"
	"varying float vTime;\n"
	"void main () {\n"
		"gl_FragColor = texture2D(uTexture, vec2(vTexCoord.x + vTime, vTexCoord.y));\n"
	"}\n\0";
