#include "Scene3.h"

CScene3::CScene3()
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
	pTextures->CreateTextureAnisotropic(0, "../Scene3/CasaTex.jpg");
	pTextures->CreateTextureAnisotropic(1, "../Scene1/grass.bmp");
	pTextures->CreateTextureAnisotropic(2, "../Scene3/gold.jpg");
	pTextures->CreateTextureAnisotropic(3, "../Scene3/ruby.jpg");


	fRotY = 0.0f;

	fPosX = 0.0f;
	fPosY = 20.0f;
	fPosZ = 30.0f;


	for (int i = 0; i < 38; i++)
		faceColor[i] = { (rand() % 255), (rand() % 255), (rand() % 255) };

	

	// Definição das configurações da fonte de luz (EMISSOR)
	LightAmbient[0] = 1.0f; LightAmbient[1] = 1.0f; LightAmbient[2] = 1.0f; LightAmbient[3] = 1.0f;
	LightDiffuse[0] = 1.0f; LightDiffuse[1] = 1.0f; LightDiffuse[2] = 1.0f; LightDiffuse[3] = 1.0f;
	LightSpecular[0] = 1.0f; LightSpecular[1] = 1.0f; LightSpecular[2] = 1.0f; LightSpecular[3] = 1.0f;
	LightPosition[0] = fPosX; LightPosition[1] = fPosY; LightPosition[2] = fPosZ; LightPosition[3] = 1.0f;

	// Definição das configurações do material do objeto (REFLEXÂO)
	MatAmbient[0] = 0.1f; MatAmbient[1] = 0.0f; MatAmbient[2] = 0.0f; MatAmbient[3] = 1.0f;
	MatDiffuse[0] = 1.0f; MatDiffuse[1] = 0.0f; MatDiffuse[2] = 0.0f; MatDiffuse[3] = 1.0f;
	MatSpecular[0] = 1.0f; MatSpecular[1] = 1.0f; MatSpecular[2] = 1.0f; MatSpecular[3] = 1.0f;
	MatShininess = 128.0f;


	Ruby = CMaterial(
		0.1745f, 0.01175f, 0.01175f, 0.55f,
		0.61424f, 0.04136f, 0.04136f, 0.55f,
		0.727811f, 0.626959f, 0.626959f, 0.55f,
		76.8f);

	Gold = CMaterial(
		0.19125f, 0.0735f, 0.0275f, 1.0f,
		0.75164f, 0.60648f, 0.22648f, 1.0f,
		0.628281f, 0.555802f, 0.366065f, 1.0f,
		51.2f);

}


CScene3::~CScene3(void)
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




int CScene3::DrawGLScene(void)	// Função que desenha a cena
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

	// Desenha grid 
	//Draw3DSGrid(20.0f, 20.0f);

	// Desenha os eixos do sistema cartesiano
	DrawAxis();

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

	pTextures->ApplyTexture(1);

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
		

	//// Casa (IMMEDIATE MODE)
	int iTexCount = 0;
	int iVertCount = 0;
	pTextures->ApplyTexture(0);
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 204; i++)
	{
		float u = vfCasaTexCoords[iTexCount++];
		float v = vfCasaTexCoords[iTexCount++];
		float x = vfCasaVerts[iVertCount++];
		float y = vfCasaVerts[iVertCount++];
		float z = vfCasaVerts[iVertCount++];

		glTexCoord2f(u, v);
		glVertex3f(x, y, z);
	}
	glEnd();
	glPopMatrix();


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
	LightPosition[0] = fPosX; 
	LightPosition[1] = fPosY; 
	LightPosition[2] = fPosZ; 
	LightPosition[3] = 1.0f;

	glPushMatrix();
	glTranslatef(fPosX, fPosY, fPosZ);
	glColor3f(1.0f, 1.0f, 1.0f);
	glutSolidSphere(0.2, 10, 10);
	glPopMatrix();
	/////////////////////////

	
	glEnable(GL_LIGHTING); //  Habilita iluminação

	

	// Atribui os parâmetros da luz 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);	
	glEnable(GL_LIGHT0); // Habilita a luz 0

	// Atribui os parâmetros de reflexão  do objeto
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MatAmbient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MatDiffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, MatSpecular);
	glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, MatShininess);



	pTextures->ApplyTexture(2);

	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

	// Desenha os objetos com a definição do material específico
	glPushMatrix();
	glTranslatef(0.0f, 10.0f, 20.0f);
	glutSolidTeapot(5.0);
	glPopMatrix();

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
		
	glDisable(GL_LIGHT0); // Desabilita a luz 0	
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




void CScene3::MouseMove(void) // Tratamento de movimento do mouse
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

void CScene3::KeyPressed(void) // Tratamento de teclas pressionadas
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
		fPosX -= 0.1f;
	if (GetKeyState(VK_RIGHT) & 0x80)
		fPosX += 0.1f;
	if (GetKeyState(VK_UP) & 0x80)
		fPosZ -= 0.1f;
	if (GetKeyState(VK_DOWN) & 0x80)
		fPosZ += 0.1f;
	if (GetKeyState(VK_PRIOR) & 0x80)
		fPosY += 0.1f;
	if (GetKeyState(VK_NEXT) & 0x80)
		fPosY -= 0.1f;


}

void CScene3::KeyDownPressed(WPARAM	wParam) // Tratamento de teclas pressionadas
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

	case 'G':
	{
		MatAmbient[0] = Gold.rA;
		MatAmbient[1] = Gold.gA;
		MatAmbient[2] = Gold.bA;
		MatAmbient[3] = Gold.aA;

		MatDiffuse[0] = Gold.rD;
		MatDiffuse[1] = Gold.gD;
		MatDiffuse[2] = Gold.bD;
		MatDiffuse[3] = Gold.aD;

		MatSpecular[0] = Gold.rS;
		MatSpecular[1] = Gold.gS;
		MatSpecular[2] = Gold.bS;
		MatSpecular[3] = Gold.aS;

		MatShininess = Gold.s;
	}
		break;

	case 'R':
	{
		MatAmbient[0] = Ruby.rA; 
		MatAmbient[1] = Ruby.gA; 
		MatAmbient[2] = Ruby.bA; 
		MatAmbient[3] = Ruby.aA;

		MatDiffuse[0] = Ruby.rD;
		MatDiffuse[1] = Ruby.gD;
		MatDiffuse[2] = Ruby.bD;
		MatDiffuse[3] = Ruby.aD;

		MatSpecular[0] = Ruby.rS; 
		MatSpecular[1] = Ruby.gS; 
		MatSpecular[2] = Ruby.bS; 
		MatSpecular[3] = Ruby.aS;

		MatShininess = Ruby.s;
	}
		break;

	}

}

//	Cria um grid horizontal ao longo dos eixos X e Z
void CScene3::Draw3DSGrid(float width, float length)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(0.0f, 0.3f, 0.0f);
	glPushMatrix();
	for (float i = -width; i <= length; i += 1)
	{
		for (float j = -width; j <= length; j += 1)
		{
			// inicia o desenho das linhas
			glBegin(GL_QUADS);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(i, 0.0f, j + 1);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(i + 1, 0.0f, j + 1);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(i + 1, 0.0f, j);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(i, 0.0f, j);
			glEnd();
		}
	}
	glPopMatrix();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}



void CScene3::DrawAxis()
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


void CScene3::DrawCube()
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


void CScene3::DrawPyramid()
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