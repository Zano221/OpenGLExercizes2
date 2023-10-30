#pragma once
#include "SceneBaseClass.h"
#include "CTexture.h"
#include "CTimer.h"
#include "CTexto.h"
#include "CCamera.h"
#include "VertexData.h"
#include "CMaterial.h"
#include <glm/glm.hpp>
#include <vector>
#include "math.h"

# define M_PI           3.14159265358979323846 //cmath n funciona, nem math.h, ent fds
#define M_PI_2     1.57079632679489661923

class CScene2 : public CSceneBaseClass
{
public:
	CScene2();
	~CScene2(void);


	virtual void MouseMove(void);					// Tratamento de movimento do mouse
	virtual void KeyPressed(void);					// Tratamento de teclas pressionadas
	virtual void KeyDownPressed(WPARAM	wParam);	// Tratamento de teclas pressionadas
	virtual int DrawGLScene(void);					// Função que desenha a cena

	void Draw3DSGrid(float width, float length);
	void DrawAxis();

	void DrawCube();
	void DrawPyramid();

private:

	bool	keys[256];		// Array usado para rotinas do teclado
	bool	active;			// Window Active Flag Set To TRUE By Default
	bool	fullscreen;		// Exibir janela em modo fullscreem (TRUE) ou em janela (FALSE)


	CCamera* pCamera;	// Gerencia câmera OpenGL
	float fDeltaY;		// Rotação da câmera OpenGL no eixo Y
	float fDeltaX;		// Rotação da câmera OpenGL no eixo X

	CTexto* pTexto;	// Objeto que gerencia texto
	CTexture* pTextures;	// Objeto que gerencia texturas
	CTimer* pTimer;	// Objeto que gerencia o timer


	int		iFPS;			// FPS and FPS Counter
	int		iFrames;		// FPS and FPS Counter
	DWORD	ulLastFPS;		// FPS and FPS Counter
	char	szTitle[256];	// FPS and FPS Counter


	bool bIsWireframe;	// Modos Wireframe/Solid
	bool bIsCameraFPS;	// Ativa modo de camera First Person Shooter (true) ou Third Person Shooter (false)

	float fRenderPosY;
	float fTimerPosY;

	float fRotY;

	float fPosX[3];
	float fPosY[3];
	float fPosZ[3];

	bool RLightPosSwitch;
	bool GLightPosSwitch;
	bool BLightPosSwitch;

	float fLightDistance;


	unsigned char R;
	unsigned char G;
	unsigned char B;


	CColor3 faceColor[38];

	// Definição das configurações da fonte de luz (EMISSOR)
	GLfloat LightAmbient[3][4];
	GLfloat LightDiffuse[3][4];
	GLfloat LightSpecular[3][4];
	GLfloat LightPosition[3][4];
	GLfloat BallAngle[3];
	GLfloat LightAngle[3][3];

	// Definição das configurações do material do objeto (REFLEXÂO)
	GLfloat MatAmbient[4];
	GLfloat MatDiffuse[4];
	GLfloat MatSpecular[4];
	float MatShininess;




};

