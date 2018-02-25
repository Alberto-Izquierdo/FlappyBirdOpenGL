//
// Created by Alberto on 15/02/2018.
//

#ifndef GAME_RENDERER_H
#define GAME_RENDERER_H

class Entity;
class Matrix4;
class Shader;
class VertexBuffer;

class Renderer {
public:
	Renderer();
	~Renderer();

	void PreRender();
	void Render(Entity* _pEntity);
	void PostRender();

	void RenderPlayer(Entity* _pEntity);

	void RenderPopup(bool _bStart);
	void RenderScore(int _iScore);

	void SetTextureNumbers(int _iImageID) { m_iTextureNumbers = _iImageID; };

private:
	int m_iPosAttribute;
	int m_iPosPopupAttribute;
	int m_iTexPopupAttribute;
	int m_iTextureNumbers;
	unsigned int m_VBO;
	Shader* m_pEntitiesShader;
	Shader* m_pPlayerShader;
	Shader* m_pPopupShader;
	Shader* m_pNumberShader;

	VertexBuffer* m_pEntitiesVertexBuffer;
	VertexBuffer* m_pPlayerVertexBuffer;
	VertexBuffer* m_pStartPopupVertexBuffer;
	VertexBuffer* m_pGameOverPopupVertexBuffer;
	VertexBuffer* m_pNumbersPopupVertexBuffer;

	void InitBuffers();
	void DeleteBuffers();
	void InitVertexAttributes();

	Matrix4 GetWorldTransformationToView(float _fScaleX, float _fScaleY, float _fRotation);
};


#endif //GAME_RENDERER_H
