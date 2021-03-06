/*
CG - Trabalho Final
Grupo: Igor, Nathalia & Yves


Esse trabalho procura ilustrar retalhos de Bezier através de 4 retalhos diferentes (um de cada vez).


Usabilidade: Os comandos são controlados via teclado. Segue sua lista:

1. Controle da resolução do retalho:
	1.1 - Ao pressionar a tecla "U" (maiúsculo), a quantidade de amostras na direção U aumenta.
	1.2 - Ao pressionar a tecla "u" (minúsculo), a quantidade de amostras na direção U diminui.
	1.3 - Ao pressionar a tecla "V" (maiúsculo), a quantidade de amostras na direção V aumenta.
	1.4 - Ao pressionar a tecla "v" (minúsculo), a quantidade de amostras na direção U diminui.

2. Controle de animação (rotação):
	2.1 - Pressione tecla "a" para ligar/desligar rotação.
	2.2 - Pressione tecla "s" para movimento um passo de cada vez ("camera lenta").
	2.3 - As teclas "<-" e "->" controlam a direção e velocidade da rotação no eixo y.
	2.4 - As teclas de seta (para cima e para baixo) controlam a direção e velocidade da rotação no eixo s.
	2.5 - Pressione tecla "r" para voltar ao esquema original de posição, antes de iniciar rotação.
	2.6 - Pressione "0" (número zero) para zerar a velocidade de rotação.

3. Zoom
	3.1 - Pressione tecla "z" para aumentar o zoom.
	3.2 - Pressione tecla "x" para diminuir o zoom.

4. Preenchimento e sombra
	4.1 - Ao pressionar a tecla "p", alterne as opções de preenchimento da superfície (GL_LINE ou GL_FILL).
	4.2 - Ao pressionar a tecla "o", alterne as opções de sombra (GL_FLAT e GL_SMOOTH).

*/

#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include "original.h"
#include <math.h>
#include <limits.h>
#include <GL/glut.h>	


// Modelos de retalhos de Bezier
const float obj1[4][3][4] = {
	{ {-2, -1, 0, 1}, { 0, 0, 2, 0}, { 2, -1, 0, 1 } },
	{ {-3, 0, 0, 1}, { 0, 0, 3, 0}, { 3, 0, 0, 1}},
	{ {-1.5, 0.5, 0, 1}, { 0, 0, 1.5, 0}, {1.5, 0.5, 0, 1}},			
	{ {-2, 1, 0, 1}, { 0, 0, 2, 0}, { 2,  1, 0, 1 } }
};  

const float obj2[16][1][3] = {
	{{-0.75, -0.75, -0.50}},
	{{-0.25, -0.75, 0.00}},
	{{0.25, -0.75, 0.00}},
	{{0.75, -0.75, -0.50}},
	{{-0.75, -0.25, -0.75}},
	{{-0.25, -0.25, 0.50}},
	{{0.25, -0.25, 0.50}},
	{{0.75, -0.25, -0.75}},
	{{-0.75, 0.25, 0.00}},
	{{-0.25, 0.25, -0.50}},
	{{0.25, 0.25, -0.50}},
	{{0.75, 0.25, 0.00}},
	{{-0.75, 0.75, -0.50}},
	{{-0.25, 0.75, -1.00}},
	{{0.25, 0.75, -1.00}},
	{{0.75, 0.75, -0.50}}

};

const float obj3[4][3][4] = {
	{{4.0,2.0,2.0,1.0},{4.0,1.6,2.5,1.0},{4.0,2.0,3.0,1.0}},
    {{5.0,4.0,2.0,1.0},{5.0,4.0,2.5,1.0},{5.0,4.0,3.0,1.0}},
    {{6.0,5.0,2.0,1.0},{6.0,5.0,2.5,1.0},{6.0,5.0,3.0,1.0}},
    {{sqrt(12.0),sqrt(12.0),sqrt(4.0),sqrt(2.0)},
     {sqrt(12.0),sqrt(12.0),sqrt(5.0),sqrt(2.0)},
     {sqrt(12.0),sqrt(12.0),sqrt(6.0),sqrt(2.0)}}

};

const float obj4[2][1][10] = {
	{0.0, 1.0, 2.0, 3.0, 0.5, 1.5, 2.5, 0.5, 1.5, 0.0},
	{0.0, 0.0, 0.0, 0.0, 1.0, 1.25, 1.5 , 2.0, 2.5, 3.0}

};


// Variaveis que controlam o refinamento do retalho
int NumU1 = 4;
int NumV1 = 4;
int NumU2 = 8;
int NumV2 = 8;



const float PI2 = 2.0f*3.1415926535f;
int obj;
GLfloat zpos = -6; // Posição z inicial (usado para zoom)


GLenum shadeModel = GL_FLAT;		// Podendo alternar entre GL_FLAT e GL_SMOOTH
GLenum polygonMode = GL_LINE;		// Podendo alternar entre GL_LINE e GL_FILL

// Variaveis de rotacao
GLenum runMode = GL_TRUE;
float RotX = 0.0f;					// Posicao de rotacao eixo X
float RotY = 0.0f;					// Posicao de rotacao eixo Y
float RotIncX = 0.0;					// Incrementa rotacao (eixo X)
float RotIncY = 0.0;					// Incrementa rotacao (eixo Y)
const float RotIncFactor = 1.5;				// Fator de rotacao a cada pressionada do teclado (pode imaginar como uma velocidade) 

// Valores iluminacao
float ambientLight[4] = {0.2, 0.2, 0.2, 1.0};
float Lt0amb[4] = {0.1, 0.1, 0.1, 1.0};
float Lt0diff[4] = {0.6, 0.6, 0.6, 1.0};
float Lt0spec[4] = {1.0, 1.0, 1.0, 1.0};
float Lt0pos[4] = {1.0, 0.0, 1.0, 0.0};			// Luz direcional

float Lt1amb[4] = {0.1, 0.1, 0.1, 1.0};
float Lt1diff[4] = {0.6, 0.6, 0.6, 1.0};
float Lt1spec[4] = {1.0, 1.0, 1.0, 1.0};
float Lt1pos[4] = {0.0, 1.0, 1.0, 0.0};			// Luz direcional

// Variveis brilho/reflexão   
float Noemit[4] = {0.0, 0.0, 0.0, 1.0};
float Matspec[4] = {1.0, 1.0, 1.0, 1.0};
float Matnospec[4] = {0.8, 0.05, 0.4, 1.0};		// Sombra
float Matshine = 50.0;					// Controla intensidade do brilho

void menuHelp(){

	printf("\n\n\n\tCONTROLAR A ANIMAÇÃO:\n");
	printf("\t\tPressione 'a' para ativar e desativar animação\n");
	printf("\t\tPressione 's' para executar um passo da animação\n");
	printf("\t\tPressione'->' ou '<-' para rotacionar no eixo y\n");
	printf("\t\tPressione '/\' '\\/' para rotacionar no eixo x\n");
	printf("\t\tPressione '0' para resetar a direção da rotação\n");
	printf("\t\tPressione 'r' para resetar o retalho\n\n\n");
	printf("\tCONTROLES DO OPENGL:\n");
	printf("\t\tPressione 'p' para trocar entre modo polígono e modo wireframe\n");
	printf("\t\tPressione 'f' para trocar entre shading flat e shading smooth\n\n");
	printf("\tPressione ESC para sair");


}

// Comandos do teclado
void keyboardFunc( unsigned char key, int x, int y ) {
	switch ( key ) {
	case 'a':
		runMode = !runMode;
		break;
	case 's':			// Movimento um passo de cada vez ("camera lenta" controlada pelo teclado)
		runMode = GL_TRUE;
		updateScene();
		runMode = GL_FALSE;
		break;
	case 27:			// Fecha a janela
		exit(1);
	case 'r':			// Reinicia tudo (volta ao esquema original)
		ResetAnimation();
		break;
	case '0':			// Zera a rotacao
		ZeroRotation();
		break;
	case 'f':			//  alterna entre GL_FLAT e GL_SMOOTH
		ShadeModelFunc();
		break;
	case 'p':			// Formato do poligono --> alterna entre GL_LINE e GL_FILL
		FillModeFunc();
		break;
	case 'u':			// Decrementa "u"
		DecU();
		break;
	case 'U':			// Incrementa "u"
		IncU();
		break;
	case 'v':			// Decrementa "v"
		DecV();
		break;
	case 'V':			// Incrementa "v"
		IncV();
		break;
	case 'z':
		zpos ++;
		return;
	case 'x':
		zpos --;
		return;
	case 'h':
		menuHelp();
		return;
	}
	
}

// Trata as quatro possibilidades de movimentos rotacionais (cima,baixo,esquerda,direita)
void rotKeyFunc( int key, int x, int y ) {
	switch ( key ) {
	case GLUT_KEY_UP:				
		KeyUp();		// Aumenta rotação para cima ou diminui rotação para baixo
		break;
	case GLUT_KEY_DOWN:
		KeyDown();		// Aumenta rotação para baixo ou diminui rotação para cima
		break;
	case GLUT_KEY_LEFT:
		KeyLeft();		// Aumenta rotação para esquerda ou diminui rotação para direita
		break;
	case GLUT_KEY_RIGHT:
		KeyRight();		// Aumenta rotação para direita ou diminiu rotação para esquerda
		break;
	}
}

// As quatro funções: KeyUp, KeyDown, KeyLeft e KeyRight limitam a mudança de direção de rotação apenas com "reset"
void KeyUp() {
    if ( RotIncX == 0.0 ) {
		RotIncX = -0.1;		// Inicialmente 1/10 degrau de rotação por update (isso se repete para as 3 seguintes funções)
	}
}

void KeyDown() {
    if ( RotIncX == 0.0 ) {
		RotIncX = 0.1;		
	}
	else if ( RotIncX > 0.0f) {
		RotIncX *= RotIncFactor;
	}
	else {
		RotIncX /= RotIncFactor;
	}	
}

void KeyLeft() {
    if ( RotIncY == 0.0 ) {
		RotIncY = -0.1;		
	}
	else if ( RotIncY < 0.0) {
		RotIncY *= RotIncFactor;
	}
	else {
		RotIncY /= RotIncFactor;
	}	
}

void KeyRight() {
    if ( RotIncY == 0.0 ) {
		RotIncY = 0.1;		
	}
	else if ( RotIncY > 0.0) {
		RotIncY *= RotIncFactor;
	}
	else {
		RotIncY /= RotIncFactor;
	}	
}


// Restaura posicao original e define rotação igual a zero.
void ResetAnimation() {
	RotX = RotY = RotIncX = RotIncY = 0.0;
}

// Restaura rotação para zero.
void ZeroRotation() {
	RotIncX = RotIncY = 0.0;
}

// Alterna entre GL_SMOOTH e GL_FLAT
void ShadeModelFunc() {
	if ( shadeModel == GL_FLAT ) {
		shadeModel = GL_SMOOTH;
	}
	else {
		shadeModel = GL_FLAT;
	}
}

// Alterna entre GL_LINE e GL_FILL
void FillModeFunc() {
	if ( polygonMode == GL_LINE ) {
		polygonMode = GL_FILL;
	}
	else {
		polygonMode = GL_LINE;
	}
}

// Incrementa "u"
void IncU() {
	NumU1++;
}

// Decrementa "u"
void DecU() {
	if (NumU1>4) {
		NumU1--;
	}
}

// Incrementa "v"
void IncV() {
	NumV1++;
}

// Decrementa "v"
void DecV() {
	if (NumV1>4) {
		NumV1--;
	}
}

void updateScene( void ) {
	// Clear the rendering window
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glShadeModel( shadeModel );	// Especifica tonalidade da sombra alterna entre GL_FLAT e GL_SMOOTH
	glPolygonMode(GL_FRONT_AND_BACK, polygonMode);	// Especifica rasterização do poligono (deixar suas linhas ou preencher por completo)

	// Especifica materiais do retalho (iluminação)
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Matnospec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Matspec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, Matshine);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Noemit);

	glPushMatrix();		

	glTranslatef(.0f, 0.f, zpos); // Matriz de translação (zoom in ou zoom out, dependendo do valor de zpos)

	// Atualiza orientação, case alguma animação (rotação) esteja ocorrendo.
	if ( runMode ) {
		RotY += RotIncY;
		if ( fabs(RotY)>360.0 ) {
			RotY -= 360.0*((int)(RotY/360.0));
		}
		RotX += RotIncX;
		if ( fabs(RotX)>360.0 ) {
			RotX -= 360.0*((int)(RotX/360.0));
		}
	}
	// Define orientação (eixo x e eixo y)
	glRotatef( RotX, 1.0, 0.0, 0.0);
	glRotatef( RotY, 0.0, 1.0, 0.0);

	// Desenha retalho Bezier
	glEnable(GL_MAP2_VERTEX_4);

	if (obj == 1){
		glMap2f(GL_MAP2_VERTEX_4, 0,1,4,3, 0,1,12,4, &obj1[0][0][0] );	 // Define mapeamento linear da grade.
		glMapGrid2f( NumU1, 0,1, NumV1, 0, 1); 							// Define quantidade de partições.
		glEvalMesh2(GL_FILL, 0,NumU1, 0, NumV1);
	}

	if (obj == 2){
		glMap2f(GL_MAP2_VERTEX_4, 0,1,4,3, 0,1,12,4, &obj2[0][0][0] );	
		glMapGrid2f( NumU2, 0,1, NumV2, 0, 1);
		glEvalMesh2(GL_FILL, 0,NumU2, 0, NumV2);
	}

	if (obj == 3){
		glMap2f(GL_MAP2_VERTEX_4, 0,1,4,3, 0,1,12,4, &obj3[0][0][0] );	
		glMapGrid2f(NumU1, 0,1, NumV1, 0, 1);
		glEvalMesh2(GL_FILL, 0,NumU1, 0,NumV1 );
	}

	if (obj == 4){
		glMap2f(GL_MAP2_VERTEX_4, 0,1,4,3, 0,1,12,4, &obj4[0][0][0] );	
		glMapGrid2f( NumU2, 0,1, NumV2, 0, 1);
		glEvalMesh2(GL_FILL, 0,NumU2, 0, NumV2);
	}

	glPopMatrix();		

	
    glFlush();
    glutSwapBuffers();
}

// Inicializa OpenGL (iluminação)
void initRendering() {

    glEnable( GL_DEPTH_TEST );
	glEnable( GL_AUTO_NORMAL );

	glEnable(GL_LIGHTING);		
	glEnable(GL_LIGHT0);		
	glEnable(GL_LIGHT1);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);	// Luz Ambiente

	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);		// Phong 

	glFrontFace(GL_CW);					

	glLightfv(GL_LIGHT0, GL_AMBIENT, Lt0amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Lt0diff);
	glLightfv(GL_LIGHT0, GL_SPECULAR, Lt0spec);
	glLightfv(GL_LIGHT0, GL_POSITION, Lt0pos);

	glLightfv(GL_LIGHT1, GL_AMBIENT, Lt1amb);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Lt1diff);
	glLightfv(GL_LIGHT1, GL_SPECULAR, Lt1spec);
	glLightfv(GL_LIGHT1, GL_POSITION, Lt1pos);
}

// Efetua mudança nas dimensões da janela (aumentando ou diminuindo de acordo com ação do mouse).
void resizeWindow(int w, int h)
{
    float aspectRatio;
	glViewport( 0, 0, w, h );	// View port uses whole window
	h = (w == 0) ? 1 : h;
	aspectRatio = (float)w/(float)h;

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 60.0, aspectRatio, 1.0, 30.0 );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	
	// Seleciona uma visualização diferente para cada objeto
	if (obj == 1){
		glTranslatef(0.0, 0.0, -0.5);
		glRotatef(5.0, 1.0,0.0,0.0);	 
	}
	if (obj == 2){
		glTranslatef(-10.0, 0.0, -20.0);
		glRotatef(0.0, 1.0,0.0,0.0);	 
	}
	if (obj == 4){
		glTranslatef(0.0, 0.0, -10.0);
		glRotatef(15.0, 1.0,0.0,0.0);	 
	}
	if (obj == 3){
		glTranslatef(-3.0, -3.0, -5.0);
		glRotatef(15.0, 1.0,0.0,0.0);	 
	}
		 
}

void chooseObj(){
	printf("\n\n\n\t**********APLICAÇÃO DE BEZIER*************\n\n");
	printf("\t Selecione um modelo (1,2,3 ou 4): ");
		scanf("%d", &obj);
}




int main( int argc, char** argv )
{
	chooseObj();
	glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );

	// Posicao e tamanho da janela
    glutInitWindowPosition( 10, 60 );
    glutInitWindowSize( 800, 600 );
    glutCreateWindow( "CG Trabalho Final - Bezier aplicacao" );
    initRendering();
	resizeWindow(800,600);

	glutKeyboardFunc( keyboardFunc );
	glutSpecialFunc( rotKeyFunc );
    glutReshapeFunc( resizeWindow );
	glutIdleFunc( updateScene );
    glutDisplayFunc( updateScene );

	glutMainLoop(  );

    return(0);	
}
