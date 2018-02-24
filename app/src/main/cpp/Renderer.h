//
// Created by Alberto on 15/02/2018.
//

#ifndef GAME_RENDERER_H
#define GAME_RENDERER_H

struct Vertex
{
	float m_vPosition[2];
};

class Entity;
class Matrix4;
class Shader;

class Renderer {
public:
	Renderer();
	~Renderer();

	void PreRender();
	void Render(Entity* _pEntity);
	void PostRender();
private:
	int m_iPosAttribute;
	unsigned int m_VBO;
	Vertex m_Rectangle[6];
	Shader* m_pEntitiesShader;

	void InitBuffers();
	void DeleteBuffers();
	void FillDefaultRectangle();
	void InitVertexAttributes();

	Matrix4 GetWorldTransformationToView(float _fScaleX, float _fScaleY, float _fRotation);
};


#endif //GAME_RENDERER_H
