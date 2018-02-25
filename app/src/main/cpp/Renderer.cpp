//
// Created by Alberto on 15/02/2018.
//

#include "Renderer.h"
#include "Entity.h"
#include "Constants.h"
#include "Shader.h"
#include "Shaders.h"
#include "VertexBuffer.h"

#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <android/log.h>
#include <cmath>

Renderer::Renderer()
{
	m_pBackgroundShader = new Shader(Shaders::backgroundVertexSource, Shaders::backgroundFragmentSource);
	m_pEntitiesShader = new Shader(Shaders::entitiesVertexSource, Shaders::entitiesFragmentSource);
	m_pPlayerShader = new Shader(Shaders::playerVertexSource, Shaders::playerFragmentSource);
	m_pPopupShader = new Shader(Shaders::popupVertexSource, Shaders::popupFragmentSource);
	m_pNumberShader = new Shader(Shaders::numberVertexSource, Shaders::numberFragmentSource);
	InitBuffers();
}

Renderer::~Renderer()
{
	DeleteBuffers();
	delete m_pBackgroundShader;
	delete m_pEntitiesShader;
	delete m_pPlayerShader;
	delete m_pPopupShader;
	delete m_pNumberShader;
}

void Renderer::RenderBackground(float _fTime, bool _bInitState)
{
    glClearColor(0.678431373f, 0.847058824f, 0.901960784f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_pBackgroundShader->Bind();
	m_pBackgroundVertexBuffer->Bind();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_iTextureNumbers);
	m_pBackgroundShader->SetUniform1i("uTexture", 0);

	if (_bInitState)
	{
		m_pBackgroundShader->SetUniform1f("uTime", 0.f);
	}
	else if (_fTime >= 0.f)
	{
		m_pBackgroundShader->SetUniform1f("uTime", _fTime);
	}

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindTexture(GL_TEXTURE_2D, 0);
	m_pBackgroundVertexBuffer->Unbind();
	m_pBackgroundShader->Unbind();
}

void Renderer::PreRender()
{
	m_pEntitiesShader->Bind();
	m_pEntitiesVertexBuffer->Bind();

	GLint err = glGetError();
	if (err != GL_NO_ERROR) {
		//__android_log_print(ANDROID_LOG_ERROR, "DRAW", "Error pre-drawing: %i", err);
	}
}

void Renderer::Render(Entity* _pEntity)
{
	float fDimensions[2] = {_pEntity->GetWidth(), _pEntity->GetHeight()};
	float fPosition[2] = {_pEntity->GetX() / Constants::k_fWorldWidth * 2.f - 1.f, _pEntity->GetY() / Constants::k_fWorldHeight * 2.f - 1.f};
	m_pEntitiesShader->SetUniform4f("uPos", fPosition[0], fPosition[1], 0.f, 0.f);
	float* color = _pEntity->GetColor();
	m_pEntitiesShader->SetUniform4f("uColor", color[0], color[1], color[2], color[3]);
	float fRotation = _pEntity->GetRotation() * 2.f * 3.1415f / 360.f;
	Matrix4 matrix = GetWorldTransformationToView(fDimensions[0], fDimensions[1], fRotation);
	m_pEntitiesShader->SetUniformMatrix4("uTransformationMatrix", matrix);
    glDrawArrays(GL_TRIANGLES, 0, 6);

	GLint err = glGetError();
	if (err != GL_NO_ERROR) {
		__android_log_print(ANDROID_LOG_ERROR, "DRAW", "Error drawing: %i", err);
	}
}

void Renderer::RenderPlayer(Entity* _pEntity)
{
	m_pPlayerShader->Bind();
	m_pPlayerVertexBuffer->Bind();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_iTextureNumbers);
	m_pPopupShader->SetUniform1i("uTexture", 0);

	float fDimensions[2] = {_pEntity->GetWidth() + 40, _pEntity->GetHeight() + 40};
	float fPosition[2] = {_pEntity->GetX() / Constants::k_fWorldWidth * 2.f - 1.f, _pEntity->GetY() / Constants::k_fWorldHeight * 2.f - 1.f};
	m_pPlayerShader->SetUniform4f("uPos", fPosition[0], fPosition[1], 0.f, 0.f);
	float fRotation = _pEntity->GetRotation() * 2.f * 3.1415f / 360.f;
	Matrix4 matrix = GetWorldTransformationToView(fDimensions[0], fDimensions[1], fRotation);
	m_pPlayerShader->SetUniformMatrix4("uTransformationMatrix", matrix);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisable(GL_BLEND);

	glBindTexture(GL_TEXTURE_2D, 0);
	m_pPlayerVertexBuffer->Unbind();
	m_pPlayerShader->Unbind();
}

void Renderer::PostRender()
{
	m_pEntitiesVertexBuffer->Unbind();
	m_pEntitiesShader->Unbind();
}

void Renderer::RenderPopup(bool _bStart)
{
	m_pPopupShader->Bind();
	if (_bStart)
	{
		m_pStartPopupVertexBuffer->Bind();
	}
	else
	{
		m_pGameOverPopupVertexBuffer->Bind();
	}

	GLint err = glGetError();
	if (err != GL_NO_ERROR) {
		__android_log_print(ANDROID_LOG_ERROR, "DRAW", "Error pre-drawing: %i", err);
	}
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_iTextureNumbers);
	m_pPopupShader->SetUniform1i("uTexture", 0);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	m_pPopupShader->Unbind();
}

void Renderer::RenderScore(int _iScore)
{
	m_pNumberShader->Bind();
	m_pNumbersPopupVertexBuffer->Bind();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_iTextureNumbers);
	m_pPopupShader->SetUniform1i("uTexture", 0);
	int iAux = 1;

	do
	{
		int unit = ((_iScore / (int)std::pow(10, iAux - 1)) % 10);
		float vTexCoordOffset[2] = {(unit % 5) * 0.1f, ((unit % (int)std::pow(10, iAux)) / 5) * 0.1f};
		m_pNumberShader->SetUniform2f("uTexCoordOffset", vTexCoordOffset[0], vTexCoordOffset[1]);
		m_pNumberShader->SetUniform2f("uPos", -0.2f * (float)(iAux - 1), 0);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glDisable(GL_BLEND);
		++iAux;
	} while (_iScore / (int)std::pow(10, iAux - 1) > 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	m_pNumbersPopupVertexBuffer->Unbind();
	m_pNumberShader->Unbind();
}

void Renderer::InitBuffers()
{
	{
		float vPositions[12] = {-0.5f, -0.5f,
								 0.5f, -0.5f,
								 0.5f,  0.5f,
								-0.5f, -0.5f,
								 0.5f,  0.5f,
								-0.5f,  0.5f};
		float vTexCoords[12] = {};
		m_pEntitiesVertexBuffer = new VertexBuffer(vPositions, vTexCoords);
	}

	{
		float vPositions[12] = {-0.5f, -0.5f,
								 0.5f, -0.5f,
								 0.5f,  0.5f,
								-0.5f, -0.5f,
								 0.5f,  0.5f,
								-0.5f,  0.5f};
		float vTexCoords[12] = {
								0.5f,  0.25f,
								0.75f, 0.25f,
								0.75f, 0.0f,
								0.5f,  0.25f,
								0.75f, 0.0f,
								0.5f,  0.0f};
		m_pPlayerVertexBuffer = new VertexBuffer(vPositions, vTexCoords);
	}

	{
		float vPositions[12] = {-1.0f, -1.0f,
								 1.0f, -1.0f,
								 1.0f,  1.0f,
								-1.0f, -1.0f,
								 1.0f,  1.0f,
								-1.0f,  1.0f};
		float vTexCoords[12] = {0.0f,  1.0f,
								0.281f, 1.0f,
								0.281f, 0.5f,
								0.0f,  1.0f,
								0.281f, 0.5f,
								0.0f,  0.5f};
		m_pBackgroundVertexBuffer = new VertexBuffer(vPositions, vTexCoords);
	}

	{
		float vPositions[12] = {-1.0f, -0.25f,
								 1.0f, -0.25f,
								 1.0f,  0.25f,
								-1.0f, -0.25f,
								 1.0f,  0.25f,
								-1.0f,  0.25f};
		float vTexCoords[12] = {0.0f,  0.839f,
								1.0f,  0.839f,
								1.0f,  0.404f,
								0.0f,  0.839f,
								1.0f,  0.404f,
								0.0f,  0.404f};
		for (int i = 0; i < 12; ++i)
		{
			vTexCoords[i] /= 2.f;
		}
		m_pStartPopupVertexBuffer = new VertexBuffer(vPositions, vTexCoords);
		vPositions[1] = vPositions[3] = vPositions[7] = -0.12f;
		vPositions[5] = vPositions[9] = vPositions[11] = 0.12f;
		vTexCoords[1] = vTexCoords[3] = vTexCoords[7] = 1.f / 2.f;
		vTexCoords[5] = vTexCoords[9] = vTexCoords[11] = 0.839f / 2.f;
		m_pGameOverPopupVertexBuffer = new VertexBuffer(vPositions, vTexCoords);
	}
	{
		float vPositions[12] = { 0.7f,  0.7f,
								 1.0f,  0.7f,
								 1.0f,  1.0f,
								 0.7f,  0.7f,
								 1.0f,  1.0f,
								 0.7f,  1.0f};
		float vTexCoords[12] = {0.0f,  0.2f,
								0.2f,  0.2f,
								0.2f,  0.0f,
								0.0f,  0.2f,
								0.2f,  0.0f,
								0.0f,  0.0f};
		for (int i = 0; i < 12; ++i)
		{
			vTexCoords[i] /= 2.f;
		}
		m_pNumbersPopupVertexBuffer = new VertexBuffer(vPositions, vTexCoords);
	}
}

void Renderer::DeleteBuffers()
{
	delete m_pBackgroundVertexBuffer;
	delete m_pEntitiesVertexBuffer;
	delete m_pPlayerVertexBuffer;
	delete m_pStartPopupVertexBuffer;
	delete m_pGameOverPopupVertexBuffer;
	delete m_pNumbersPopupVertexBuffer;
}

Matrix4 Renderer::GetWorldTransformationToView(float _fWidth, float _fHeight, float _fRotation)
{
	Matrix4 scale = Matrix4::Scale((_fWidth * 2.f / Constants::k_fWorldWidth), (_fHeight * 2.f / Constants::k_fWorldHeight), 0.f);
	Matrix4 rotation = Matrix4::RotationZ(_fRotation);
	Matrix4 result = rotation * scale;
	return result;
}
