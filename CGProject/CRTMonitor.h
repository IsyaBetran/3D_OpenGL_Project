#pragma once

#include <glad/glad.h>
#include "RenderEngine.h"
#include "Texture.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <SOIL/SOIL.h>

class CRTMonitor 
{
public:
	CRTMonitor(Shader* shader, Texture* diffuseTexture, Texture* specularTexture);
	~CRTMonitor();
	void SetPosition(float x, float y, float z);
	void SetScale(float sx, float sy, float sz);
	void Init();
	void DrawCRTMonitor();
private:
	GLuint shaderProgram, texture3, VAO, VBO, EBO, texture4;
	Texture* diffuseTexture, * specularTexture;
	Shader* shader;
	glm::vec3 position, scale;
	float angle;
	void InitTexture();
	void MakeCRTMonitor();
};