#include "CRTMonitor.h"
#include <glm/gtx/string_cast.hpp>

CRTMonitor::CRTMonitor(Shader* shader, Texture* diffuseTexture, Texture* specularTexture)
{
	this->shader = shader;
	this->diffuseTexture = diffuseTexture;
	this->specularTexture = specularTexture;
	VAO = VBO = EBO = 0;
}

CRTMonitor::~CRTMonitor() {};

void CRTMonitor::MakeCRTMonitor() {

	float vertices[] = {
		-0.2f, -1.0f, 1.25f,	0.0f, 0.0f, 0.0f,  0.0f,  1.0f,
		-0.2f, 1.0f, 1.25f,		1.0f, 0.0f, 0.0f,  0.0f,  1.0f,
		-0.2f, -1.0f, -1.25f,	1.0f, 1.0f, 0.0f,  0.0f,  1.0f,
		-0.2f, 1.0f, -1.25f,	0.0f, 1.0f, 0.0f,  0.0f,  1.0f,

		0.2f, -1.0f, 1.25f,		0.0f, 0.0f, 0.0f,  0.0f,  1.0f,
		0.2f, 1.0f, 1.25f,		1.0f, 0.0f, 0.0f,  0.0f,  1.0f,
		0.2f, -1.0f, -1.25f,	1.0f, 1.0f, 0.0f,  0.0f,  1.0f,
		0.2f, 1.0f, -1.25f,		0.0f, 1.0f, 0.0f,  0.0f,  1.0f,

		-0.2f, -0.8f, -1.0f,	0.0f, 0.0f, 0.0f,  0.0f,  1.0f,
		-0.2f, -0.8f, 1.0f,		1.0f, 0.0f, 0.0f,  0.0f,  1.0f,
		-0.2f, 0.8f, 1.0f,		1.0f, 1.0f, 0.0f,  0.0f,  1.0f,
		-0.2f, 0.8f, -1.0f,		0.0f, 1.0f, 0.0f,  0.0f,  1.0f,

		-1.7f, -0.72f, -0.9f,	0.0f, 0.0f, 0.0f,  0.0f,  1.0f,
		-1.7f, -0.72f, 0.9f,	1.0f, 0.0f, 0.0f,  0.0f,  1.0f,
		-1.7f, 0.72f, 0.9f,		1.0f, 1.0f, 0.0f,  0.0f,  1.0f,
		-1.7f, 0.72f, -0.9f,	0.0f, 1.0f, 0.0f,  0.0f,  1.0f,

		-0.575f, -0.78f, -0.5f,	0.0f, 0.0f, 0.0f,  0.0f,  1.0f,
		-0.575f, -0.78f, 0.5f,	1.0f, 0.0f, 0.0f,  0.0f,  1.0f,
		-1.325f, -0.74f, -0.45f,1.0f, 1.0f, 0.0f,  0.0f,  1.0f,
		-1.325f, -0.74f, 0.45f,	0.0f, 1.0f, 0.0f,  0.0f,  1.0f,

		-0.575f, -1.28f, -0.5f,	0.0f, 0.0f, 0.0f,  0.0f,  1.0f,
		-0.575f, -1.28f, 0.5f,	1.0f, 0.0f, 0.0f,  0.0f,  1.0f,
		-1.325f, -1.24f, -0.45f,1.0f, 1.0f, 0.0f,  0.0f,  1.0f,
		-1.325f, -1.24f, 0.45f,	0.0f, 1.0f, 0.0f,  0.0f,  1.0f,

		-0.2f, -1.3f, -1.0f,	0.0f, 0.0f, 0.0f,  0.0f,  1.0f,
		-0.2f, -1.3f, 1.0f,		1.0f, 0.0f, 0.0f,  0.0f,  1.0f,
		-1.7f, -1.22f, -0.9f,	1.0f, 1.0f, 0.0f,  0.0f,  1.0f,
		-1.7f, -1.22f, 0.9f,	0.0f, 1.0f, 0.0f,  0.0f,  1.0f,

		-0.2f, -1.5f, -1.0f,	0.0f, 0.0f, 0.0f,  0.0f,  1.0f,
		-0.2f, -1.5f, 1.0f,		1.0f, 0.0f, 0.0f,  0.0f,  1.0f,
		-1.7f, -1.42f, -0.9f,	1.0f, 1.0f, 0.0f,  0.0f,  1.0f,
		-1.7f, -1.42f, 0.9f,	0.0f, 1.0f, 0.0f,  0.0f,  1.0f,

		0.2f, 0.9f, -1.125f,	0.0f, 0.0f, 0.0f,  0.0f,  1.0f,
		0.2f, -0.9f, -1.125f,	1.0f, 0.0f, 0.0f,  0.0f,  1.0f,
		0.2f, -0.9f, 1.125f,	1.0f, 1.0f, 0.0f,  0.0f,  1.0f,
		0.2f, 0.9f, 1.125f,		0.0f, 1.0f, 0.0f,  0.0f,  1.0f,

		0.15f, 0.9f, -1.125f,	0.0f, 0.0f, 0.0f,  0.0f,  1.0f,
		0.15f, -0.9f, -1.125f,	1.0f, 0.0f, 0.0f,  0.0f,  1.0f,
		0.15f, -0.9f, 1.125f,	1.0f, 1.0f, 0.0f,  0.0f,  1.0f,
		0.15f, 0.9f, 1.125f,	0.0f, 1.0f, 0.0f,  0.0f,  1.0f
	};

	unsigned int indices[] = {
		3, 10, 1, //belakang monitor
		3, 6, 2, //samping monitor
		5, 32, 7, //depan monitor
		5, 0, 4, //samping monitor
		6, 0, 2, //bawah monitor
		3, 5, 7, //atas monitor
		8, 15, 11, //kanan mesin monitor
		0, 8, 2, //bawah belakang monitor
		2, 11, 3, //belakang monitor
		1, 9, 0, //belakang monitor
		14, 12, 13, //belakang mesin monitor
		10, 13, 9,
		11, 14, 10,
		9, 16, 8,
		16, 22, 18,
		12, 16, 18,
		12, 19, 13,
		13, 17, 9,
		21, 27, 25,
		17, 20, 16,
		17, 23, 21,
		18, 23, 19,
		26, 31, 27,
		22, 27, 23,
		20, 26, 22,
		21, 24, 20,
		29, 30, 28,
		24, 30, 26,
		25, 28, 24,
		25, 31, 29,
		34, 39, 35,
		7, 33, 6,
		4, 35, 5,
		6, 34, 4,
		36, 38, 37,
		33, 38, 34,
		35, 36, 32,
		32, 37, 33,
		3, 11, 10,
		3, 7, 6,
		5, 35, 32,
		5, 1, 0,
		6, 4, 0,
		3, 1, 5,
		8, 12, 15,
		0, 9, 8,
		2, 8, 11,
		1, 10, 9,
		14, 15, 12,
		10, 14, 13,
		11, 15, 14,
		9, 17, 16,
		16, 20, 22,
		12, 8, 16,
		12, 18, 19,
		13, 19, 17,
		21, 23, 27,
		17, 21, 20,
		17, 19, 23,
		18, 22, 23,
		26, 30, 31,
		22, 26, 27,
		20, 24, 26,
		21, 25, 24,
		29, 31, 30,
		24, 28, 30,
		25, 29, 28,
		25, 27, 31,
		34, 38, 39,
		7, 32, 33,
		4, 34, 35,
		6, 33, 34,
		36, 39, 38,
		33, 37, 38,
		35, 39, 36,
		32, 36, 37
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void CRTMonitor::InitTexture()
{
	diffuseTexture->Init();
	specularTexture->Init();
}

void CRTMonitor::Init()
{
	// Initialize buffers
	MakeCRTMonitor();
	// Initalize texture
	InitTexture();


}

void CRTMonitor::DrawCRTMonitor() {
	diffuseTexture->Use(GL_TEXTURE0);
	shader->setInt("material.diffuse", 0);
	specularTexture->Use(GL_TEXTURE1);
	shader->setInt("material.specular", 1);
	shader->setFloat("material.shininess", 10.0f);

	glBindVertexArray(VAO);

	glm::mat4 model;
	model = glm::scale(scale);
	model = glm::translate(model, position);

	shader->setMat4("model", model);

	glDrawElements(GL_TRIANGLES, 228, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

void CRTMonitor::SetPosition(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
}

void CRTMonitor::SetScale(float sx, float sy, float sz)
{
	scale.x = sx;
	scale.y = sy;
	scale.z = sz;

	position.x = position.x / sx;
	position.y = position.y / sy;
	position.z = position.z / sz;

}