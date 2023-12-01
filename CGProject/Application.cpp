#include "Application.h"


Application::Application()
{
}

Application::~Application()
{
}

void Application::setupLighting()
{
	// set lighting attributes
	glm::vec3 lightPos = glm::vec3(0, 35, 0);
	shader->setVec3("lightPos", lightPos);
	shader->setVec3("viewPos", glm::vec3(0,2,3));
	glm::vec3 lightColor = glm::vec3(0.9f, 0.9f, 0.9f);
	shader->setVec3("lightColor", lightColor);
}

void Application::Init()
{
	shader = new Shader("texturedCube.vert", "texturedCube.frag");
	shader->Init();

	
	InitObject();
	InitCamera();

	setupLighting();

}

void Application::DeInit()
{
	delete cube,basecube, cubeRoof, cubeSofa, cubeMeja,picture, picture2, tv, frame, rug, mat, bedCover, leaf;
	delete monitor;
}

void Application::Update(double deltaTime)
{

}

void Application::ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	// zoom camera
	// -----------
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		if (fovy < 90) {
			fovy += 0.0001f;
		}
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		if (fovy > 0) {
			fovy -= 0.0001f;
		}
	}

	// update camera movement 
	// -------------
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		MoveCamera(CAMERA_SPEED);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		MoveCamera(-CAMERA_SPEED);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		StrafeCamera(-CAMERA_SPEED);
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		StrafeCamera(CAMERA_SPEED);
	}

	double mouseX, mouseY;
	double midX = screenWidth / 2;
	double midY = screenHeight / 2;
	float angleY = 0.0f;
	float angleZ = 0.0f;

	// Get mouse position
	glfwGetCursorPos(window, &mouseX, &mouseY);
	if ((mouseX == midX) && (mouseY == midY)) {
		return;
	}

	// Set mouse position
	glfwSetCursorPos(window, midX, midY);

	// Get the direction from the mouse cursor, set a resonable maneuvering speed
	angleY = (float)((midX - mouseX)) / 1000;
	angleZ = (float)((midY - mouseY)) / 1000;

	// The higher the value is the faster the camera looks around.
	viewCamY += angleZ * 2;

	// limit the rotation around the x-axis
	if ((viewCamY - posCamY) > 8) {
		viewCamY = posCamY + 8;
	}
	if ((viewCamY - posCamY) < -8) {
		viewCamY = posCamY - 8;
	}
	RotateCamera(-angleY);
	
}

void Application::Render()
{
	// render
	// ------
	glViewport(0, 0, this->screenWidth, this->screenHeight);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.52f, 0.8f, 0.92f, 1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	

	// Pass perspective projection matrix
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)this->screenWidth / (GLfloat)this->screenHeight, 0.1f, 100.0f);
	shader->setMat4("projection", projection);

	// LookAt camera (position, target/direction, up)
	glm::vec3 cameraPos = glm::vec3(posCamX, posCamY, posCamZ);
	glm::vec3 cameraFront = glm::vec3(viewCamX, viewCamY, viewCamZ);
	glm::mat4 view = glm::lookAt(cameraPos, cameraFront, glm::vec3(upCamX, upCamY, upCamZ));
	shader->setMat4("view", view);
	
	glm::vec3 pos = glm::vec3(-10.5f,-1,0);
	Sofa(pos);
	pos = glm::vec3(-7, -1, 5);
	SofaMiring(pos);
	pos = glm::vec3(-10, -1, -12);
	SofaMiring(pos);

	Meja();

	MoneyHust();

	PDS();

	TV();

	MejaTV();

	FrameTembok();

	House();
	Base();

	Rug();

	Keset();

	Bed();
	Lemari();

	MejaDapur();

	//Hijau-hijauan
	Pohon(glm::vec3(5, 0, 25));
	Pohon(glm::vec3(10, 0, 10));
	Pohon(glm::vec3(-26, 0, -6));
	Pohon(glm::vec3(-29, 0, 5));
	Pohon(glm::vec3(-27, 0, 18));
	Grass(glm::vec3(-27, -1, 30));
	Grass(glm::vec3(3, -1, 30));

	monitor->SetPosition(-17.5f, 0.85f, -16);
	monitor->SetScale(0.5f, 0.5f, 0.5f);
	monitor->DrawCRTMonitor();

	// glBindArray(0); // no need to unbind it every time
	glDisable(GL_DEPTH_TEST);
}


void Application::InitCamera()
{
	posCamX = -20.0f;
	posCamY = 3.0f;
	posCamZ = 50.0f;
	viewCamX = 0.0f;
	viewCamY = 0.0f;
	viewCamZ = 0.0f;
	upCamX = 0.0f;
	upCamY = 1.0f;
	upCamZ = 0.0f;
	CAMERA_SPEED = 0.001f;
	fovy = 45.0f;
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Application::MoveCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	// forward positive cameraspeed and backward negative -cameraspeed.
	posCamX = posCamX + x * speed;
	posCamZ = posCamZ + z * speed;
	viewCamX = viewCamX + x * speed;
	viewCamZ = viewCamZ + z * speed;
}

void Application::StrafeCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	float orthoX = -z;
	float orthoZ = x;

	// left positive cameraspeed and right negative -cameraspeed.
	posCamX = posCamX + orthoX * speed;
	posCamZ = posCamZ + orthoZ * speed;
	viewCamX = viewCamX + orthoX * speed;
	viewCamZ = viewCamZ + orthoZ * speed;
}

void Application::RotateCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	viewCamZ = (float)(posCamZ + glm::sin(speed) * x + glm::cos(speed) * z);
	viewCamX = (float)(posCamX + glm::cos(speed) * x - glm::sin(speed) * z);
}


int main(int argc, char** argv) {
	Application app = Application();
	app.Start("Inti Bumi", 1920, 1080, false, false);
	return 0;
}


void Application::InitObject() {
	cubeDiffTex = new Texture("grey.png");
	cubeDiffTex->Init();
	cubeSpecTex = new Texture("grey.png");
	cubeSpecTex->Init();

	cube = new Cube(shader, cubeDiffTex, cubeSpecTex);
	cube->Init();

	cubeDiffTex = new Texture("brown.png");
	cubeDiffTex->Init();
	cubeSpecTex = new Texture("brown.png");
	cubeSpecTex->Init();

	cubeRoof = new Cube(shader, cubeDiffTex, cubeSpecTex);
	cubeRoof->Init();

	cubeDiffTex = new Texture("green.png");
	cubeDiffTex->Init();
	cubeSpecTex = new Texture("green.png");
	cubeSpecTex->Init();

	basecube = new Cube(shader, cubeDiffTex, cubeSpecTex);
	basecube->Init();

	cubeDiffTex = new Texture("cream2.png");
	cubeDiffTex->Init();
	cubeSpecTex = new Texture("cream2.png");
	cubeSpecTex->Init();

	cubeSofa = new Cube(shader, cubeDiffTex, cubeSpecTex);
	cubeSofa->Init();

	cubeDiffTex = new Texture("brown.png");
	cubeDiffTex->Init();
	cubeSpecTex = new Texture("brown.png");
	cubeSpecTex->Init();

	cubeMeja = new Cube(shader, cubeDiffTex, cubeSpecTex);
	cubeMeja->Init();

	cubeDiffTex = new Texture("DisneyMeneyHeist.png");
	cubeDiffTex->Init();
	cubeSpecTex = new Texture("DisneyMeneyHeist.png");
	cubeSpecTex->Init();

	picture = new Cube(shader, cubeDiffTex, cubeSpecTex);
	picture->Init();

	cubeDiffTex = new Texture("PDS.jpg");
	cubeDiffTex->Init();
	cubeSpecTex = new Texture("PDS.jpg");
	cubeSpecTex->Init();

	picture2 = new Cube(shader, cubeDiffTex, cubeSpecTex);
	picture2->Init();

	cubeDiffTex = new Texture("sketsa.jpg");
	cubeDiffTex->Init();
	cubeSpecTex = new Texture("sketsa.jpg");
	cubeSpecTex->Init();

	tv = new Cube(shader, cubeDiffTex, cubeSpecTex);
	tv->Init();

	cubeDiffTex = new Texture("dark-textured-watercolor.jpg");
	cubeDiffTex->Init();
	cubeSpecTex = new Texture("dark-textured-watercolor.jpg");
	cubeSpecTex->Init();

	frame = new Cube(shader, cubeDiffTex, cubeSpecTex);
	frame->Init();

	cubeDiffTex = new Texture("oldPlastic.jpg");
	cubeDiffTex->Init();
	cubeSpecTex = new Texture("oldPlastic.jpg");
	cubeSpecTex->Init();

	monitor = new CRTMonitor(shader, cubeDiffTex, cubeSpecTex);
	monitor->Init();

	cubeDiffTex = new Texture("karpet.png");
	cubeDiffTex->Init();
	cubeSpecTex = new Texture("karpet.png");
	cubeSpecTex->Init();

	rug = new Cube(shader, cubeDiffTex, cubeSpecTex);
	rug->Init();

	cubeDiffTex = new Texture("welcome.png");
	cubeDiffTex->Init();
	cubeSpecTex = new Texture("welcome.png");
	cubeSpecTex->Init();

	mat = new Cube(shader, cubeDiffTex, cubeSpecTex);
	mat->Init();

	cubeDiffTex = new Texture("putih.png");
	cubeDiffTex->Init();
	cubeSpecTex = new Texture("putih.png");
	cubeSpecTex->Init();

	bedCover = new Cube(shader, cubeDiffTex, cubeSpecTex);
	bedCover->Init();

	cubeDiffTex = new Texture("greenleaf.png");
	cubeDiffTex->Init();
	cubeSpecTex = new Texture("greenleaf.png");
	cubeSpecTex->Init();

	leaf = new Cube(shader, cubeDiffTex, cubeSpecTex);
	leaf->Init();
}

void Application::House() {
	glm::vec3 posA = glm::vec3(0, 9, 0);
	glm::vec3 posNew = posA;
	posNew.y--;
	float scaleY = 1;

	for (int i = 0; i < 21; i++)
	{
		cubeRoof->SetPosition(posA.x, posA.y, posA.z);
		cubeRoof->SetRotation(0, 0, 1, 0);
		cubeRoof->SetScale(41, 1, 1);
		cubeRoof->Draw();

		//penutup samping
		if (i != 0 && i != 20) {
			posNew.x = 19;
			Genteng(posNew, scaleY);
			posNew.x = -19;
			Genteng(posNew, scaleY);
		}


		if (i < 10) {
			posA.y += 1;
			posNew.y += 0.5;
			scaleY += 1;
		}
		else {
			posA.y -= 1;
			posNew.y -= 0.5;
			scaleY -= 1;
		}
		posA.z -= 1;
		posNew.z--;
	}

	glm::vec3 posB = glm::vec3(-19, 9, 4);
	posNew = posB;
	posNew.y -= 0.5;
	scaleY = 0;

	for (int i = 0; i < 15; i++)
	{
		cubeRoof->SetPosition(posB.x, posB.y, posB.z);
		cubeRoof->SetRotation(0, 0, 1, 0);
		cubeRoof->SetScale(1, 1, 20);
		cubeRoof->Draw();

		if (i != 0 && i != 14) {
			posNew.z = 12;
			Genteng(posNew, scaleY);
		}

		if (i < 7) {
			posB.y++;
			posNew.y += 0.5;
			scaleY += 1;
		}
		else {
			posB.y--;
			posNew.y -= 0.5;
			scaleY -= 1;
		}
		posB.x++;
		posNew.x++;
	}

	Plafon();

	//tembok belakang
	cube->SetPosition(0, 3, -19);
	cube->SetRotation(0, 0, 1, 0);
	cube->SetScale(37, 9, 1);
	cube->Draw();

	//tembok kiri
	cube->SetPosition(-19, 3, -10);
	cube->SetRotation(0, 0, 1, 0);
	cube->SetScale(1, 9, 19);
	cube->Draw();

	//tembok kanan
	cube->SetPosition(19, 3, -10);
	cube->SetRotation(0, 0, 1, 0);
	cube->SetScale(1, 9, 19);
	cube->Draw();

	//tembok depan
	cube->SetPosition(7, 3, -1);
	cube->SetRotation(0, 0, 1, 0);
	cube->SetScale(23, 9, 1);
	cube->Draw();

	//tembok dalam
	cube->SetPosition(7, 3, -8);
	cube->SetRotation(0, 0, 1, 0);
	cube->SetScale(1, 9, 14);
	cube->Draw();

	//tembok dalam atas
	cube->SetPosition(7, 7, -16.75f);
	cube->SetRotation(0, 0, 1, 0);
	cube->SetScale(1, 5, 4);
	cube->Draw();

	//tembok kiri extend
	cube->SetPosition(-19, 3, 6);
	cube->SetRotation(0, 0, 1, 0);
	cube->SetScale(1, 9, 13);
	cube->Draw();

	//tembok kanan extend
	cube->SetPosition(-5, 3, 5.5);
	cube->SetRotation(0, 0, 1, 0);
	cube->SetScale(1, 9, 14);
	cube->Draw();

	//atas depan
	cube->SetPosition(-12, 8, 6);
	cube->SetRotation(0, 0, 1, 0);
	cube->SetScale(15, 1, 14);
	cube->Draw();

	//bawah belakang
	cube->SetPosition(0, -2, -10);
	cube->SetRotation(0, 0, 1, 0);
	cube->SetScale(39, 1, 19);
	cube->Draw();

	//bawah depan
	cube->SetPosition(-12, -2, 9);
	cube->SetRotation(0, 0, 1, 0);
	cube->SetScale(15, 1, 20);
	cube->Draw();

	//tembok depan lagi
	cube->SetPosition(-12, 6, 12);
	cube->SetRotation(0, 0, 1, 0);
	cube->SetScale(13, 3, 1);
	cube->Draw();

	//tembok depan lagi kiri
	cube->SetPosition(-16, 1.5f, 12);
	cube->SetRotation(0, 0, 1, 0);
	cube->SetScale(5, 6, 1);
	cube->Draw();

	//tembok depan lagi kanan
	cube->SetPosition(-8, 1.5f, 12);
	cube->SetRotation(0, 0, 1, 0);
	cube->SetScale(5, 6, 1);
	cube->Draw();
}

void Application::Base() {
	basecube->SetPosition(0, -3, 0);
	basecube->SetRotation(0, 0, 1, 0);
	basecube->SetScale(200, 1, 200);
	basecube->Draw();
}

void Application::Genteng(glm::vec3 posA,float y) {
	cube->SetPosition(posA.x, posA.y, posA.z);
	cube->SetRotation(0, 0, 1, 0);
	cube->SetScale(1, y, 1);
	cube->Draw();
}

void Application::Plafon() {
	cube->SetPosition(0,8,-10);
	cube->SetRotation(0, 0, 1, 0);
	cube->SetScale(37, 1, 19);
	cube->Draw();
}

void Application::Sofa(glm::vec3 position) {
	cubeSofa->SetPosition(position.x,position.y,position.z);
	cubeSofa->SetRotation(0, 1, 0, 0);
	cubeSofa->SetScale(5, 1, 1);
	cubeSofa->Draw();

	glm::vec3 newPos = position;

	cubeSofa->SetPosition(newPos.x, newPos.y, newPos.z - 1);
	cubeSofa->SetRotation(0, 1, 0, 0);
	cubeSofa->SetScale(6, 3.5f, 1);
	cubeSofa->Draw();

	newPos = position;

	cubeSofa->SetPosition(newPos.x + 2.75f, newPos.y, newPos.z);
	cubeSofa->SetRotation(0, 1, 0, 0);
	cubeSofa->SetScale(0.5f, 2, 1);
	cubeSofa->Draw();

	newPos = position;

	cubeSofa->SetPosition(newPos.x - 2.75f, newPos.y, newPos.z);
	cubeSofa->SetRotation(0, 1, 0, 0);
	cubeSofa->SetScale(0.5f, 2, 1);
	cubeSofa->Draw();
}

void Application::SofaMiring(glm::vec3 position) {
	cubeSofa->SetPosition(position.x, position.y, position.z);
	cubeSofa->SetRotation(0, 1, 0, 0);
	cubeSofa->SetScale(1, 1, 5);
	cubeSofa->Draw();

	glm::vec3 newPos = position;

	cubeSofa->SetPosition(newPos.x + 1, newPos.y, newPos.z);
	cubeSofa->SetRotation(0, 1, 0, 0);
	cubeSofa->SetScale(1, 3.5f, 6);
	cubeSofa->Draw();

	newPos = position;

	cubeSofa->SetPosition(newPos.x , newPos.y, newPos.z + 2.75f);
	cubeSofa->SetRotation(0, 1, 0, 0);
	cubeSofa->SetScale(1, 2, 0.5f);
	cubeSofa->Draw();

	newPos = position;

	cubeSofa->SetPosition(newPos.x , newPos.y, newPos.z - 2.75f);
	cubeSofa->SetRotation(0, 1, 0, 0);
	cubeSofa->SetScale(1, 2, 0.5f);
	cubeSofa->Draw();
}

void Application::Meja() {
	cubeMeja->SetPosition(-11,-0.25f,5);
	cubeMeja->SetRotation(0, 1, 0, 0);
	cubeMeja->SetScale(2.5f, 0.5f, 4);
	cubeMeja->Draw();

	glm::vec3 pos = glm::vec3(-12, -1, 3.5f);
	for (int i = 0; i < 2; i++)
	{
		cubeMeja->SetPosition(pos.x,pos.y,pos.z);
		cubeMeja->SetRotation(0, 1, 0, 0);
		cubeMeja->SetScale(0.5f, 1, 0.5f);
		cubeMeja->Draw();

		glm::vec3 newPos = pos;
		newPos.x += 2;

		cubeMeja->SetPosition(newPos.x, newPos.y, newPos.z);
		cubeMeja->SetRotation(0, 1, 0, 0);
		cubeMeja->SetScale(0.5f, 1, 0.5f);
		cubeMeja->Draw();

		pos.z += 3;
	}
}

void Application::MoneyHust() {
	picture->SetPosition(-5.5f,3,5);
	picture->SetRotation(0, 0, 1, 0);
	picture->SetScale(0.2f,3,2);
	picture->Draw();
}

void Application::PDS() {
	picture2->SetPosition(-16, 3, 11.55f);
	picture2->SetRotation(0, 0, 1, 0);
	picture2->SetScale(2, 2, 0.2f);
	picture2->Draw();
}

void Application::TV() {
	tv->SetPosition(-18.5f, 3, -12);
	tv->SetRotation(0, 0, 1, 0);
	tv->SetScale(0.2f, 3, 5);
	tv->Draw();


	float y = 4.6f;
	for (int i = 0; i < 2; i++)
	{
		frame->SetPosition(-18.5f, y, -11.95f);
		frame->SetRotation(0, 0, 1, 0);
		frame->SetScale(0.4f, 0.2f, 5.3f);
		frame->Draw();

		y -= 3.2f;
	}

	float z = -9.4;
	for (int i = 0; i < 2; i++)
	{
		frame->SetPosition(-18.5f, 3, z);
		frame->SetRotation(0, 0, 1, 0);
		frame->SetScale(0.4f, 3, 0.2f);
		frame->Draw();

		z -= 5.1f;
	}
	
}

void Application::MejaTV() {
	cubeMeja->SetPosition(-18, -1, -12);
	cubeMeja->SetRotation(0, 0, 1, 0);
	cubeMeja->SetScale(1.5f, 2, 9);
	cubeMeja->Draw();

	cubeMeja->SetPosition(-18, 0, -12);
	cubeMeja->SetRotation(0, 0, 1, 0);
	cubeMeja->SetScale(2, 0.25f, 10);
	cubeMeja->Draw();
}

void Application::FrameTembok() {

	float y = 3;
	float z = -3;
	for (int i = 0; i < 7; i++)
	{
		cubeMeja->SetPosition(-18, y, z);
		cubeMeja->SetRotation(0, 0, 1, 0);
		cubeMeja->SetScale(0.7, 0.2f, 2);
		cubeMeja->Draw();

		if (i % 2 == 0 || i == 0) {
			y += 1;
		}
		else {
			y -= 1;
		}
		z += 2;
	}
}

void Application::Rug() {
	rug->SetPosition(-13.5f, -1.5f, -12);
	rug->SetRotation(0, 0, 1, 0);
	rug->SetScale(6, 0.2f, 9);
	rug->Draw();
}

void Application::Keset() {
	mat->SetPosition(-12, -1.5f, 14);
	mat->SetRotation(0, 0, 1, 0);
	mat->SetScale(3, 0.2f, 1.5f);
	mat->Draw();
}

void Application::Bed() {
	//Bagian Bawah
	cubeRoof->SetPosition(10, -1, -7);
	cubeRoof->SetRotation(0, 0, 1, 0);
	cubeRoof->SetScale(5, 1.5f, 10);
	cubeRoof->Draw();
	//Bagian Kepala
	cubeRoof->SetPosition(10, 0, -2);
	cubeRoof->SetRotation(0, 0, 1, 0);
	cubeRoof->SetScale(5, 4, 0.5f);
	cubeRoof->Draw();
	//cover
	bedCover->SetPosition(10, 0, -7);
	bedCover->SetRotation(0, 0, 1, 0);
	bedCover->SetScale(5, 0.5, 9.4);
	bedCover->Draw();
}

void Application::Lemari() {
	//base
	cubeRoof->SetPosition(16, 2, -3);
	cubeRoof->SetRotation(0, 0, 1, 0);
	cubeRoof->SetScale(5, 8, 2);
	cubeRoof->Draw();
	//kiri
	cubeRoof->SetPosition(17.2, 2.25f, -4);
	cubeRoof->SetRotation(0, 0, 1, 0);
	cubeRoof->SetScale(2, 7, 0.5f);
	cubeRoof->Draw();
	//kanan
	cubeRoof->SetPosition(14.8, 2.25f, -4);
	cubeRoof->SetRotation(0, 0, 1, 0);
	cubeRoof->SetScale(2, 7, 0.5f);
	cubeRoof->Draw();
}

void Application::Pohon(glm::vec3 position) {
	//batang
	cubeRoof->SetPosition(position.x,position.y, position.z);
	cubeRoof->SetRotation(0, 0, 1, 0);
	cubeRoof->SetScale(2, 6, 2);
	cubeRoof->Draw();
	//daun
	leaf->SetPosition(position.x, position.y + 6, position.z);
	leaf->SetRotation(0, 0, 1, 0);
	leaf->SetScale(8, 8, 8);
	leaf->Draw();
}

void Application::Grass(glm::vec3 position) {
	leaf->SetPosition(position.x, position.y, position.z);
	leaf->SetRotation(0, 0, 1, 0);
	leaf->SetScale(25, 3, 3);
	leaf->Draw();
}

void Application::MejaDapur() {
	cubeRoof->SetPosition(0, -1.5f, -2.75f);
	cubeRoof->SetRotation(0, 0, 1, 0);
	cubeRoof->SetScale(8, 4, 2.5f);
	cubeRoof->Draw();

	cubeRoof->SetPosition(5.25f, -1.5f, -5.5f);
	cubeRoof->SetRotation(0, 0, 1, 0);
	cubeRoof->SetScale(2.5f, 4, 8);
	cubeRoof->Draw();
}
