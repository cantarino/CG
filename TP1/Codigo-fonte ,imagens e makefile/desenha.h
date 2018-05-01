#ifndef desenha_h
#define desenha_h

#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "texto.h"

void inicializaTexturas(GLuint *texturaBodao,GLuint *texturaFogo,GLuint *texturaBG,GLuint *texturaCaneca);
void setFogo(float personagemX,float personagemY,float anguloRotacao,float personagemLargura,GLuint texturaBodao);
void setprincipal(float personagemX,float personagemY,float anguloRotacao,float personagemLargura,GLuint texturaBodao);
void setCheckpoint(float checkX,float checkY,float checkLargura,float checkAltura,GLuint texturaCaneca);
void setChao(float chaoX,float chaoY,float chaoAltura,float chaoLargura);
void setHud(float velocidadeX,float velocidadeY,float posicaoY,float tempo,int setup,int vidas);
void setBG(GLuint texturaBG);

#endif /* desenha_h */
