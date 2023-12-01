#pragma once

#include "RenderEngine.h"
#include "Cube.h"
#include "Texture.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <SOIL/SOIL.h>
#include "CRTMonitor.h"

class Application :
	public RenderEngine
{
public:
    Application();
    ~Application();
private:
	float viewCamX, viewCamY, viewCamZ, upCamX, upCamY, upCamZ, posCamX, posCamY, posCamZ, CAMERA_SPEED, fovy;
	Shader *shader;
	Cube *cube, *basecube, *cubeRoof, *cubeSofa, *cubeMeja, *picture,*picture2, *tv, *frame, *rug, *mat;
	CRTMonitor *monitor;
	Texture *cubeDiffTex, *cubeSpecTex;
	virtual void Init();
	virtual void DeInit();
	virtual void Update(double deltaTime);
	virtual void Render();
	virtual void ProcessInput(GLFWwindow* window);
	void setupLighting();
	void MoveCamera(float speed);
	void StrafeCamera(float speed);
	void RotateCamera(float speed);
	void InitCamera();
	void InitObject();
	void House();
	void Genteng(glm::vec3 posA, float y);
	void Plafon();
	void Base();
	void Sofa(glm::vec3 position);
	void SofaMiring(glm::vec3 position);
	void Meja();
	void MoneyHust();
	void PDS();
	void TV();
	void MejaTV();
	void FrameTembok();
	void Rug();
	void Keset();
	void Bed();
};

