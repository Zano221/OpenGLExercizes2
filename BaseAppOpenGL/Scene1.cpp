#include "Scene1.h"

CScene1::CScene1()
{
	pCamera = NULL;
	pTexto = NULL;
	pTextures = NULL;

	bIsWireframe = false;
	bIsCameraFPS = true;

	iFPS = 0;
	iFrames = 0;
	ulLastFPS = 0;
	szTitle[256] = 0;

	// Cria gerenciador de impressão de texto na tela
	pTexto = new CTexto();

	// Cria camera
	pCamera = new CCamera(0.0f, 1.0f, 20.0f, 0.2f);

	// Cria o Timer
	pTimer = new CTimer();
	pTimer->Init();

	fTimerPosY = 0.0f;
	fRenderPosY = 0.0f;

	// Carrega todas as texturas
	pTextures = new CTexture();


	fRotY = 0.0f;

	


	for (int i = 0; i < 38; i++)
		faceColor[i] = { (rand() % 255), (rand() % 255), (rand() % 255) };

	
	fPosX[0] = -50.0f;
	fPosY[0] = 10.0f;
	fPosZ[0] = -50.0f;

	fPosX[1] = 0.0f;
	fPosY[1] = 10.0f;
	fPosZ[1] = 50.0f;

	fPosX[2] = 50.0f;
	fPosY[2] = 10.0f;
	fPosZ[2] = -50.0f;

	// Definição das configurações da fonte de luz (EMISSOR)

	for (int i = 0; i < 3; i++) {
		LightAmbient[i][0] = 0.0f; LightAmbient[i][1] = 0.0f;; LightAmbient[i][2] = 0.0f;; LightAmbient[i][3] = 0.0f;;
		LightSpecular[i][0] = 1.0f; LightSpecular[i][1] = 1.0f; LightSpecular[i][2] = 1.0f; LightSpecular[i][3] = 1.0f;
		LightPosition[i][0] = fPosX[i]; LightPosition[i][1] = fPosY[i]; LightPosition[i][2] = fPosZ[i]; LightPosition[i][3] = 1.0f;
	}

	LightDiffuse[0][0] = 1.0f; LightDiffuse[0][1] = 0.1f; LightDiffuse[0][2] = 0.0f; LightDiffuse[0][3] = 1.0f;
	LightDiffuse[1][0] = 0.0f; LightDiffuse[1][1] = 1.0f; LightDiffuse[1][2] = 0.0f; LightDiffuse[1][3] = 1.0f;
	LightDiffuse[2][0] = 0.0f; LightDiffuse[2][1] = 0.0f; LightDiffuse[2][2] = 1.0f; LightDiffuse[2][3] = 1.0f;

	LightDirection[0] = 0.0f, LightDirection[1] = 1.0f; LightDirection[2] = 0.0f;

	// Definição das configurações do material do objeto (REFLEXÂO)
	MatAmbient[0] = 0.0f; MatAmbient[1] = 0.0f; MatAmbient[2] = 0.0f; MatAmbient[3] = 0.0f;
	MatDiffuse[0] = 1.0f; MatDiffuse[1] = 1.0f; MatDiffuse[2] = 1.0f; MatDiffuse[3] = 1.0f;
	MatSpecular[0] = 1.0f; MatSpecular[1] = 1.0f; MatSpecular[2] = 1.0f; MatSpecular[3] = 1.0f;
	MatShininess = 255.0f;

	RLightPosSwitch = false;
	GLightPosSwitch = false;
	BLightPosSwitch = false;

	fLightDistance = 50.0f;

}


CScene1::~CScene1(void)
{
	if (pTexto)
	{
		delete pTexto;
		pTexto = NULL;
	}

	if (pTextures)
	{
		delete pTextures;
		pTextures = NULL;
	}

	if (pCamera)
	{
		delete pCamera;
		pCamera = NULL;
	}

	if (pTimer)
	{
		delete pTimer;
		pTimer = NULL;
	}
}




int CScene1::DrawGLScene(void)	// Função que desenha a cena
{
	// Get FPS
	if (GetTickCount() - ulLastFPS >= 1000)	// When A Second Has Passed...
	{
		ulLastFPS = GetTickCount();				// Update Our Time Variable
		iFPS = iFrames;							// Save The FPS
		iFrames = 0;							// Reset The FPS Counter
	}
	iFrames++;									// FPS counter

	pTimer->Update();							// Atualiza o timer

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Limpa a tela e o Depth Buffer
	glLoadIdentity();									// Inicializa a Modelview Matrix Atual


	// Seta as posições da câmera
	pCamera->setView();

	//pTextures->ApplyTexture(0);

	// Desenha grid 
	//Draw3DSGrid(200.0f, 200.0f);

	// Desenha os eixos do sistema cartesiano
	//DrawAxis();

	// Modo FILL ou WIREFRAME (pressione barra de espaço)	
	if (bIsWireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                               DESENHA OS OBJETOS DA CENA (INÍCIO)
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	glColor4ub(255, 255, 255, 255);
	glEnable(GL_TEXTURE_2D);

	// pTextures->ApplyTexture(1);

	// Chão
	/*glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);  glVertex3f(-50.0f, 0.0f, 50.0f);
	glTexCoord2f(5.0f, 0.0f);  glVertex3f(50.0f, 0.0f, 50.0f);
	glTexCoord2f(5.0f, 5.0f);  glVertex3f(50.0f, 0.0f, -50.0f);
	glTexCoord2f(0.0f, 5.0f);  glVertex3f(-50.0f, 0.0f, -50.0f);
	glEnd();
	glPopMatrix();*/

	//// Casa  (VERTEX ARRAYS)
	//pTextures->ApplyTexture(0);
	//glPushMatrix();
	//glTranslatef(0.0f, 0.0f, 0.0f);
	//glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	//glEnableClientState(GL_VERTEX_ARRAY);
	//glTexCoordPointer(2, GL_FLOAT, 0, &this->vfCasaTexCoords[0]);
	//glVertexPointer(3, GL_FLOAT, 0, &this->vfCasaVerts[0]);
	//glDrawArrays(GL_TRIANGLES, 0, 204);
	//glDisableClientState(GL_VERTEX_ARRAY);
	//glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	//glPopMatrix();
	
		
	
	



	// Desenha lâmpada  ////

	for (int i = 0; i < 3; i++) {
		LightPosition[i][0] = fPosX[i];
		LightPosition[i][1] = fPosY[i];
		LightPosition[i][2] = fPosZ[i];
		LightPosition[i][3] = 1.0f;
	}
	

	// Luz R
	if (!RLightPosSwitch) {
		fPosX[0] += 0.5f;
		fPosZ[0] += 0.5f;
		
		if (fPosX[0] > fLightDistance && fPosZ[0] > fLightDistance) {
			RLightPosSwitch = true;
		}
	
	}
	else {
		fPosX[0] -= 0.5f;
		fPosZ[0] -= 0.5f;

		if (fPosX[0] < -fLightDistance && fPosZ[0] < -fLightDistance) {
			RLightPosSwitch = false;
		}
	}

	// Luz G
	if (!GLightPosSwitch) {
		fPosZ[1] -= 0.5f;

		if (fPosZ[1] < -fLightDistance) {
			GLightPosSwitch = true;
		}

	}
	else {
		fPosZ[1] += 0.5f;

		if (fPosZ[1] > fLightDistance) {
			GLightPosSwitch = false;
		}
	}

	// Luz B
	if (!BLightPosSwitch) {
		fPosX[2] -= 0.5f;
		fPosZ[2] += 0.5f;

		if (fPosX[2] < -fLightDistance && fPosZ[2] > fLightDistance) {
			BLightPosSwitch = true;
		}

	}
	else {
		fPosX[2] += 0.5f;
		fPosZ[2] -= 0.5f;

		if (fPosX[2] > fLightDistance && fPosZ[2] < -fLightDistance) {
			BLightPosSwitch = false;
		}
	}

	glPushMatrix();
	glTranslatef(fPosX[0], fPosY[0], fPosZ[0]);
	glColor3f(1.0f, 1.0f, 1.0f);
	glutSolidSphere(0.2, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(fPosX[1], fPosY[1], fPosZ[1]);
	glColor3f(1.0f, 1.0f, 1.0f);
	glutSolidSphere(0.2, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(fPosX[2], fPosY[2], fPosZ[2]);
	glColor3f(1.0f, 1.0f, 1.0f);
	glutSolidSphere(0.2, 10, 10);
	glPopMatrix();
	/////////////////////////

	
	glEnable(GL_LIGHTING); //  Habilita iluminação

	

	// Atribui os parâmetros da luz 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient[0]);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse[0]);
	glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular[0]);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition[0]);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, LightDirection);
	glEnable(GL_LIGHT0); // Habilita a luz 0

	// Atribui os parâmetros da luz 1
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient[1]);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse[1]);
	glLightfv(GL_LIGHT1, GL_SPECULAR, LightSpecular[1]);
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition[1]);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, LightDirection);
	glEnable(GL_LIGHT1); // Habilita a luz 1

	// Atribui os parâmetros da luz 2
	glLightfv(GL_LIGHT2, GL_AMBIENT, LightAmbient[2]);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, LightDiffuse[2]);
	glLightfv(GL_LIGHT2, GL_SPECULAR, LightSpecular[2]);
	glLightfv(GL_LIGHT2, GL_POSITION, LightPosition[2]);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, LightDirection);
	glEnable(GL_LIGHT2); // Habilita a luz 2

	// Atribui os parâmetros de reflexão  do objeto
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MatAmbient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MatDiffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, MatSpecular);
	glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, MatShininess);

	//pTextures->ApplyTexture(0);

	// Desenha grid 
	Draw3DSGrid(200.0f, 200.0f);


	pTextures->ApplyTexture(2);

	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

	// Desenha os objetos com a definição do material específico
	glPushMatrix();
	glTranslatef(0.0f, 10.0f, 20.0f);
	//glutSolidTeapot(5.0);         >>>>>>>>>>>>>>>TEAPOT<<<<<<<<<<<<<<
	glPopMatrix();

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
		
	glDisable(GL_LIGHT0); // Desabilita a luz 0	
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHT2);
	glDisable(GL_LIGHTING); //  Desabilita iluminação



	glDisable(GL_TEXTURE_2D);





	fRotY += 1.0f;
	if (fRotY >= 360.0f)
		fRotY = 0.0f;


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                               DESENHA OS OBJETOS DA CENA (FIM)
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	fTimerPosY = pTimer->GetTime() / 1000.0f;
	fRenderPosY += 0.2f;

	// Impressão de texto na tela...
	// Muda para modo de projeção ortogonal 2D
	// OBS: Desabilite Texturas e Iluminação antes de entrar nesse modo de projeção
	OrthoMode(0, 0, WIDTH, HEIGHT);


	glPushMatrix();
	glTranslatef(0.0f, HEIGHT - 150, 0.0f);	// Move 1 unidade para dentro da tela (eixo Z)

	// Cor da fonte
	glColor3f(1.0f, 1.0f, 0.0f);


	glRasterPos2f(10.0f, 0.0f);	// Posicionando o texto na tela
	if (!bIsWireframe) {
		pTexto->glPrint("[TAB]  Modo LINE"); // Imprime texto na tela
	}
	else {
		pTexto->glPrint("[TAB]  Modo FILL");
	}


	//// Camera LookAt
	glRasterPos2f(10.0f, 40.0f);
	pTexto->glPrint("Player LookAt  : %f, %f, %f", pCamera->Forward[0], pCamera->Forward[1], pCamera->Forward[2]);

	//// Posição do Player
	glRasterPos2f(10.0f, 60.0f);
	pTexto->glPrint("Player Position: %f, %f, %f", pCamera->Position[0], pCamera->Position[1], pCamera->Position[2]);

	//// Imprime o FPS da aplicação e o Timer
	glRasterPos2f(10.0f, 80.0f);
	pTexto->glPrint("Frames-per-Second: %d ---- Timer: %.1f segundos", iFPS, (pTimer->GetTime() / 1000));

	glRasterPos2f(10.0f, 100.0f);
	pTexto->glPrint("fRot: %.1f ", fRotY);




	glPopMatrix();

	// Muda para modo de projeção perspectiva 3D
	PerspectiveMode();

	return true;
}




void CScene1::MouseMove(void) // Tratamento de movimento do mouse
{
	// Realiza os cálculos de rotação da visão do Player (através das coordenadas
	// X do mouse.
	POINT mousePos;
	int middleX = WIDTH >> 1;
	int middleY = HEIGHT >> 1;

	GetCursorPos(&mousePos);

	if ((mousePos.x == middleX) && (mousePos.y == middleY)) return;

	SetCursorPos(middleX, middleY);

	fDeltaX = (float)((middleX - mousePos.x)) / 10;
	fDeltaY = (float)((middleY - mousePos.y)) / 10;

	// Rotaciona apenas a câmera
	pCamera->rotateGlob(-fDeltaX, 0.0f, 1.0f, 0.0f);
	pCamera->rotateLoc(-fDeltaY, 1.0f, 0.0f, 0.0f);
}

void CScene1::KeyPressed(void) // Tratamento de teclas pressionadas
{

	// Verifica se a tecla 'W' foi pressionada e move o Player para frente
	if (GetKeyState('W') & 0x80)
	{
		pCamera->moveGlob(pCamera->Forward[0], pCamera->Forward[1], pCamera->Forward[2]);
	}
	// Verifica se a tecla 'S' foi pressionada e move o Player para tras
	else if (GetKeyState('S') & 0x80)
	{
		pCamera->moveGlob(-pCamera->Forward[0], -pCamera->Forward[1], -pCamera->Forward[2]);
	}
	// Verifica se a tecla 'A' foi pressionada e move o Player para esquerda
	else if (GetKeyState('A') & 0x80)
	{
		pCamera->moveGlob(-pCamera->Right[0], -pCamera->Right[1], -pCamera->Right[2]);
	}
	// Verifica se a tecla 'D' foi pressionada e move o Player para direira
	else if (GetKeyState('D') & 0x80)
	{
		pCamera->moveGlob(pCamera->Right[0], pCamera->Right[1], pCamera->Right[2]);
	}
	else if (GetKeyState('Q') & 0x80)
	{
		pCamera->moveGlob(0.0f, -pCamera->Up[1], 0.0f);
	}
	else if (GetKeyState('E') & 0x80)
	{
		pCamera->moveGlob(0.0f, pCamera->Up[1], 0.0f);
	}
	// Senão, interrompe movimento do Player
	else
	{
	}


	if (GetKeyState(VK_LEFT) & 0x80)
		fPosX[0] -= 0.1f;
	if (GetKeyState(VK_RIGHT) & 0x80)
		fPosX[0] += 0.1f;
	if (GetKeyState(VK_UP) & 0x80)
		fPosZ[0] -= 0.1f;
	if (GetKeyState(VK_DOWN) & 0x80)
		fPosZ[0] += 0.1f;
	if (GetKeyState(VK_PRIOR) & 0x80)
		fPosY[0] += 0.1f;
	if (GetKeyState(VK_NEXT) & 0x80)
		fPosY[0] -= 0.1f;


}

void CScene1::KeyDownPressed(WPARAM	wParam) // Tratamento de teclas pressionadas
{
	switch (wParam)
	{
	case VK_TAB:
		bIsWireframe = !bIsWireframe;
		break;

	case VK_SPACE:
		pTimer->Init();
		break;

	case VK_RETURN:
		break;
	}

}

//	Cria um grid horizontal ao longo dos eixos X e Z
void CScene1::Draw3DSGrid(float width, float length)
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(0.2f, 0.2f, 0.2f);
	glPushMatrix();
	for (float i = -width; i <= length; i += 1)
	{
		for (float j = -width; j <= length; j += 1)
		{
			// inicia o desenho das linhas
			glBegin(GL_QUADS);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f);  glVertex3f(i, 0.0f, j + 1);
			glTexCoord2f(5.0f, 0.0f);  glVertex3f(i + 1, 0.0f, j + 1);
			glTexCoord2f(5.0f, 5.0f);  glVertex3f(i + 1, 0.0f, j);
			glTexCoord2f(0.0f, 5.0f);  glVertex3f(i, 0.0f, j);
			glEnd();
		}
	}
	glPopMatrix();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}



void CScene1::DrawAxis()
{
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	// Eixo X
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-1000.0f, 0.0f, 0.0f);
	glVertex3f(1000.0f, 0.0f, 0.0f);

	// Eixo Y
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 1000.0f, 0.0f);
	glVertex3f(0.0f, -1000.0f, 0.0f);

	// Eixo Z
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 1000.0f);
	glVertex3f(0.0f, 0.0f, -1000.0f);
	glEnd();
	glPopMatrix();
}


void CScene1::DrawCube()
{
	glBegin(GL_QUADS);
	// face frente
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);

	// face trás
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);

	// face direita
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);


	// face esquerda
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);

	// face baixo
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);

	// face cima
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);

	glEnd();
}


void CScene1::DrawPyramid()
{
	glBegin(GL_TRIANGLES);

	// Face frente
	glColor4ub(222, 58, 219, 255);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.0f, 0.5f, 0.0f);

	// Face direita
	glColor4ub(181, 147, 54, 255);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(0.0f, 0.5f, 0.0f);

	// Face esquerda
	glColor4ub(50, 160, 168, 255);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(0.0f, 0.5f, 0.0f);

	// Face trás
	glColor4ub(14, 201, 45, 255);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(0.0f, 0.5f, 0.0f);
	glEnd();
}