/** @file TrabalhoFinal.c
 *  @brief Programa para ilustrar superficies de Bezier através de 4 retalhos diferentes (um de cada vez).
 *
 *  @author Grupo (ordem alfabética): Igor, Nathália & Yves
 */


#include "TrabalhoFinal.h"
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <GL/glut.h>	



// Pontos para o retalho de Bezier
 
//ORIGINAL
const float controlPoints[4][3][4] = {
	{ {-2, -1, 0, 1}, { 0, 0, 2, 0}, { 2, -1, 0, 1 } },
	{ {-3, 0, 0, 1}, { 0, 0, 3, 0}, { 3, 0, 0, 1}},
	{ {-1.5, 0.5, 0, 1}, { 0, 0, 1.5, 0}, {1.5, 0.5, 0, 1}},			
	{ {-2, 1, 0, 1}, { 0, 0, 2, 0}, { 2,  1, 0, 1 } }
};  



const float controlPoints[16][1][3] = {
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


const float controlPoints[13][3][4] = {
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


const float controlPoints[2][1][10] = {
	{0.0, 1.0, 2.0, 3.0, 0.5, 1.5, 2.5, 0.5, 1.5, 0.0},
	{0.0, 0.0, 0.0, 0.0, 1.0, 1.25, 1.5 , 2.0, 2.5, 3.0}
};




GLfloat zpos = -6;			// Posição z inicial (usado para zoom)

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



void keyboardFunc(unsigned char key, int x, int y) 
{
}


void rotKeyFunc(int key, int x, int y) 
{
}


void KeyUp() 
{
}

void KeyDown() 
{
}

void KeyLeft() 
{
}

void KeyRight()
{	
}


void ResetAnimation() 
{
}


void ZeroRotation() 
{
}


void ShadeModelFunc() 
{
}


void FillModelFunc() 
{
}


void IncU() 
{
}


void DecU() 
{
}


void IncV() 
{
}


void DecV() 
{
}

void updateScene(void)
{
}


void initRendering()
{
}


void resizeWindow(int w, int h)
{	
}


