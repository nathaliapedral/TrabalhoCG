/*
CG - Trabalho Final
Grupo: Igor, Nathalia & Yves
*** !!!! Falta descrição geral do programa (explicar o que faz) 
* Usabilidade: Os comandos são controlados via teclado. Segue sua lista:
** !!! FALTA TRADUÇÃO
 * CONTROLLING RESOLUTION OF THE NURBS MESH
 *   Press "U" to increase the number samples in U direction.
 *   Press "u" to decrease the number samples in U direction.
 *   Press "V" to increase the number samples in V direction.
 *   Press "v" to decrease the number samples in U direction.
 *   
 * CONTROLLING THE ANIMATION:
 *   Press the "a" key to toggle the animation off and on.
 *   Press the "s" key to perform a single step of the animation.
 *   The left and right arrow keys controls the
 *		rate of rotation around the y-axis.
 *   The up and down arrow keys increase and decrease the rate of 
 *		rotation around the x-axis.  In order to reverse rotational
 *		direction you must zero or reset the patch ("0" or "r").
 *   Press the "r" key to reset back to initial
 *		position, with no rotation.
 *   Press "0" (zero) to zero the rotation rates.
 *
 * COMMANDS SHOWING OPENGL FEATURES:
 *   Pressing "p" toggles between wireframe and polygon mode.
 *   Pressing "f" key toggles between flat and smooth shading.
 *
 *
 **/

#include <stdlib.h>
#include "original.h"
#include <math.h>
#include <limits.h>
#include <GL/glut.h>	



GLfloat zpos = -6;





// Pontos para o retalho de Bezier

 
//ORIGINAL
const float circularStripInfty[4][3][4] = {
	{ {-2, -1, 0, 1}, { 0, 0, 2, 0}, { 2, -1, 0, 1 } },
	{ {-3, 0, 0, 1}, { 0, 0, 3, 0}, { 3, 0, 0, 1}},
	{ {-1.5, 0.5, 0, 1}, { 0, 0, 1.5, 0}, {1.5, 0.5, 0, 1}},			
	{ {-2, 1, 0, 1}, { 0, 0, 2, 0}, { 2,  1, 0, 1 } }
};  


/*
// OPÇÃO 2  (site nehe)
	const float circularStripInfty[16][1][3] = {
	{-0.75, -0.75, -0.50},
	{-0.25, -0.75, 0.00},
	{0.25, -0.75, 0.00},
	{0.75, -0.75, -0.50},
	{-0.75, -0.25, -0.75},
	{-0.25, -0.25, 0.50},
	{0.25, -0.25, 0.50},
	{0.75, -0.25, -0.75},
	{-0.75, 0.25, 0.00},
	{-0.25, 0.25, -0.50},
	{0.25, 0.25, -0.50},
	{0.75, 0.25, 0.00},
	{-0.75, 0.75, -0.50},
	{-0.25, 0.75, -1.00},
	{0.25, 0.75, -1.00},
	{0.75, 0.75, -0.50}

};
*/

/*
// OPÇÃO 3
const float circularStripInfty[13][3][4] = {
	{{4.0,2.0,2.0,1.0},{4.0,1.6,2.5,1.0},{4.0,2.0,3.0,1.0}},
    {{5.0,4.0,2.0,1.0},{5.0,4.0,2.5,1.0},{5.0,4.0,3.0,1.0}},
    {{6.0,5.0,2.0,1.0},{6.0,5.0,2.5,1.0},{6.0,5.0,3.0,1.0}},
    {{sqrt(12.0),sqrt(12.0),sqrt(4.0),sqrt(2.0)},
     {sqrt(12.0),sqrt(12.0),sqrt(5.0),sqrt(2.0)},
     {sqrt(12.0),sqrt(12.0),sqrt(6.0),sqrt(2.0)}},
    {{5.2,6.7,2.0,1.0},{5.2,6.7,2.5,1.0},{5.2,6.7,3.0,1.0}},
    {{sqrt(8.0),sqrt(12.0),sqrt(4.0),sqrt(2.0)},
     {sqrt(8.0),sqrt(12.0),sqrt(5.0),sqrt(2.0)},
     {sqrt(8.0),sqrt(12.0),sqrt(6.0),sqrt(2.0)}},
    {{4.0,5.2,2.0,1.0},{4.0,4.6,2.5,1.0},{4.0,5.2,3.0,1.0}},
    {{sqrt(8.0),sqrt(12.0),sqrt(4.0),sqrt(2.0)},
     {sqrt(8.0),sqrt(12.0),sqrt(5.0),sqrt(2.0)},
     {sqrt(8.0),sqrt(12.0),sqrt(6.0),sqrt(2.0)}},
    {{2.8,6.7,2.0,1.0},{2.8,6.7,2.5,1.0},{2.8,6.7,3.0,1.0}},
    {{sqrt(4.0),sqrt(12.0),sqrt(4.0),sqrt(2.0)},
     {sqrt(4.0),sqrt(12.0),sqrt(5.0),sqrt(2.0)},
     {sqrt(4.0),sqrt(12.0),sqrt(6.0),sqrt(2.0)}},
    {{2.0,5.0,2.0,1.0},{2.0,5.0,2.5,1.0},{2.0,5.0,3.0,1.0}},
    {{3.0,4.0,2.0,1.0},{3.0,4.0,2.5,1.0},{3.0,4.0,3.0,1.0}},
    {{4.0,2.0,2.0,1.0},{4.0,1.6,2.5,1.0},{4.0,2.0,3.0,1.0}}

};

*/


/*
//OPÇÃO 4   (BUGGADO)
const float circularStripInfty[2][1][6] = {
	{0.0,  0.5 , 1.0, 0.25, 0.75, 0.0},
	{0.0, -0.25, 0.0, 0.5 , 0.75, 1.0}

};
*/


/* 
//OPÇÃO 5
const float circularStripInfty[2][1][10] = {
	{0.0, 1.0, 2.0, 3.0, 0.5, 1.5, 2.5, 0.5, 1.5, 0.0},
	{0.0, 0.0, 0.0, 0.0, 1.0, 1.25, 1.5 , 2.0, 2.5, 3.0}

};
*/



// Variaveis que controlam o refinamento do retalho
int NumU = 4;
int NumV = 4;

const float PI2 = 2.0f*3.1415926535f;

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

// Variveis brilho/reflexão   !!!!!!!!! explicar melhor !!!!!!!!!!!
float Noemit[4] = {0.0, 0.0, 0.0, 1.0};
float Matspec[4] = {1.0, 1.0, 1.0, 1.0};
float Matnospec[4] = {0.8, 0.05, 0.4, 1.0};		// Sombra
float Matshine = 50.0;					// Controla intensidade do brilho


// Comandos do teclado
void keyboardFunc( unsigned char key, int x, int y ) 
{
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
	case 'f':			// Gradação --> alterna entre GL_FLAT e GL_SMOOTH
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
	}
}

// Trata as quatro possibilidades de movimentos rotacionais (cima,baixo,esquerda,direita)
void rotKeyFunc( int key, int x, int y ) 
{
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
/*	else if ( RotIncX < 0.0f) {
		RotIncX *= RotIncFactor;
	}
	else {
		RotIncX /= RotIncFactor;
	}	*/
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

void KeyRight()
{
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
	NumU++;
}

// Decrementa "u"
void DecU() {
	if (NumU>4) {
		NumU--;
	}
}

// Incrementa "v"
void IncV() {
	NumV++;
}

// Decrementa "v"
void DecV() {
	if (NumV>4) {
		NumV--;
	}
}

void updateScene( void )
{
	// Clear the rendering window
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glShadeModel( shadeModel );	// Set the shading to flat or smooth.
	glPolygonMode(GL_FRONT_AND_BACK, polygonMode);	// Set to be "wire" or "solid"

	// Bezier Patch Materials
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Matnospec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Matspec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, Matshine);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Noemit);

	glPushMatrix();		// Save to use again next time.

	glTranslatef(.0f, 0.f, zpos);

	// Update the orientation, if the animation is running.
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
	// Set the orientation.
	glRotatef( RotX, 1.0, 0.0, 0.0);
	glRotatef( RotY, 0.0, 1.0, 0.0);

	// Draw the Bezier patch
 	glEnable(GL_MAP2_VERTEX_4);

	glMap2f(GL_MAP2_VERTEX_4, 0,1,4,3, 0,1,12,4, &circularStripInfty[0][0][0] );
	
	glMapGrid2f( NumU, 0,1, NumV, 0, 1);
	glEvalMesh2(GL_FILL, 0,NumU, 0, NumV);

	glPopMatrix();		// Restore to original matrix as set in resizeWindow()

	// Flush the pipeline, swap the buffers
    glFlush();
    glutSwapBuffers();
}

// Initialize OpenGL
void initRendering()
{
    glEnable( GL_DEPTH_TEST );
	glEnable( GL_AUTO_NORMAL );

	glEnable(GL_LIGHTING);		// Enable lighting calculations
	glEnable(GL_LIGHT0);		// Turn on lights (unnecessary here, since also in Animate()
	glEnable(GL_LIGHT1);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);	// Ambient light

	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);		// Phong light backsides

	// Next line is suspicious, perhaps compensating for OpenGL bug	
	glFrontFace(GL_CW);					// Is needed for Bezier Patches (OpenGL bug??)

	// Light 0 
	glLightfv(GL_LIGHT0, GL_AMBIENT, Lt0amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Lt0diff);
	glLightfv(GL_LIGHT0, GL_SPECULAR, Lt0spec);
	glLightfv(GL_LIGHT0, GL_POSITION, Lt0pos);

	// Light 1 
	glLightfv(GL_LIGHT1, GL_AMBIENT, Lt1amb);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Lt1diff);
	glLightfv(GL_LIGHT1, GL_SPECULAR, Lt1spec);
	glLightfv(GL_LIGHT1, GL_POSITION, Lt1pos);
}

// Called when the window is resized
//		Sets up the projection view matrix (somewhat poorly, however)
void resizeWindow(int w, int h)
{
    float aspectRatio;
	glViewport( 0, 0, w, h );	// View port uses whole window
	h = (w == 0) ? 1 : h;
	aspectRatio = (float)w/(float)h;

	// Set up the proection view matrix
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 60.0, aspectRatio, 1.0, 30.0 );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	// Move system 10 units away to be able to view from the origin.
	glTranslatef(0.0, 0.0, -10.0);

	// Tilt system 15 degrees downward in order to view from above 
	//   the xy-plane.
	glRotatef(15.0, 1.0,0.0,0.0);	 
}


// Main routine
// Set up OpenGL, hook up callbacks, and start the main loop
int main( int argc, char** argv )
{
	glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );

	// Posicao e tamanho da janela
    glutInitWindowPosition( 10, 60 );
    glutInitWindowSize( 500, 500 );
    glutCreateWindow( "Versao 1 - Bezier aplicacao" );

	// Initialize OpenGL rendering modes
    initRendering();
	resizeWindow(500,500);

	// Set up callback functions for key presses
	glutKeyboardFunc( keyboardFunc );
	glutSpecialFunc( rotKeyFunc );

	// Set up the callback function for resizing windows
    glutReshapeFunc( resizeWindow );

	// Call this for background processing
	glutIdleFunc( updateScene );
	// Call this whenever window needs redrawing
    glutDisplayFunc( updateScene );
	
	glutMainLoop(  );

    return(0);	
}
