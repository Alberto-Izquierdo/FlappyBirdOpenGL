//
// Created by Alberto on 15/02/2018.
//

#include "Renderer.h"
#include "Entity.h"
#include "Constants.h"
#include "Shader.h"
#include "Shaders.h"

#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <android/log.h>

Renderer::Renderer()
{
	FillDefaultRectangle();
	m_pEntitiesShader = new Shader(Shaders::entitiesVertexSource, Shaders::entitiesFragmentSource);
	m_pPopupShader = new Shader(Shaders::popupVertexSource, Shaders::popupFragmentSource);
	InitBuffers();
	InitVertexAttributes();
}

Renderer::~Renderer()
{
	DeleteBuffers();
	delete m_pEntitiesShader;
	delete m_pPopupShader;
}

void Renderer::PreRender()
{
    glClearColor(0.678431373f, 0.847058824f, 0.901960784f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_pEntitiesShader->Bind();
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glVertexAttribPointer(m_iPosAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(m_iPosAttribute);

	GLint err = glGetError();
	if (err != GL_NO_ERROR) {
		__android_log_print(ANDROID_LOG_ERROR, "DRAW", "Error pre-drawing: %i", err);
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

void Renderer::PostRender()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	m_pEntitiesShader->Unbind();
}

void Renderer::RenderPopup(bool _bStart)
{
	m_pPopupShader->Bind();
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glVertexAttribPointer(m_iPosPopupAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(m_iPosPopupAttribute);
	glVertexAttribPointer(m_iTexPopupAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(m_iTexPopupAttribute);

	GLint err = glGetError();
	if (err != GL_NO_ERROR) {
		__android_log_print(ANDROID_LOG_ERROR, "DRAW", "Error pre-drawing: %i", err);
	}
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _bStart ? m_iTextureStart : m_iTextureGameOver);
	m_pPopupShader->SetUniform1i("uTexture", 0);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	m_pPopupShader->Unbind();
}

void Renderer::InitBuffers()
{
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_Rectangle), &m_Rectangle[0], GL_DYNAMIC_DRAW);
}

void Renderer::InitVertexAttributes()
{
	m_iPosAttribute = glGetAttribLocation(m_pEntitiesShader->GetRendererID(), "aPos");
	m_iPosPopupAttribute = glGetAttribLocation(m_pPopupShader->GetRendererID(), "aPos");
	m_iTexPopupAttribute = glGetAttribLocation(m_pPopupShader->GetRendererID(), "aTexCoord");
}

void Renderer::DeleteBuffers()
{
	glDeleteBuffers(1, &m_VBO);
}

void Renderer::FillDefaultRectangle()
{
	float xOffsets [6] = {-0.5f, 0.5f, 0.5f, -0.5f, 0.5f, -0.5f};
	float yOffsets [6] = {-0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f};

	for (int i = 0; i < 6; ++i)
	{
		m_Rectangle[i].m_vPosition[0] = xOffsets[i];
		m_Rectangle[i].m_vPosition[1] = yOffsets[i];
		m_Rectangle[i].m_vTexCoord[0] = xOffsets[i] + 0.5f;
		m_Rectangle[i].m_vTexCoord[1] = yOffsets[i] + 0.5f;
	}
}

Matrix4 Renderer::GetWorldTransformationToView(float _fWidth, float _fHeight, float _fRotation)
{
	Matrix4 scale = Matrix4::Scale((_fWidth * 2.f / Constants::k_fWorldWidth), (_fHeight * 2.f / Constants::k_fWorldHeight), 0.f);
	Matrix4 rotation = Matrix4::RotationZ(_fRotation);
	Matrix4 result = rotation * scale;
	return result;
}
