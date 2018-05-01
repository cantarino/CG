//
//  menuPrincipal.h
//  ComputacaoGrafica
//
//  Created by Marcus Cantarino on 16/04/2018.
//  Copyright © 2018 Marcus Cantarino. All rights reserved.
//

#ifndef menuPrincipal_h
#define menuPrincipal_h

#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "texto.h"

void texturasMenu(GLuint *texturaJogar,GLuint *texturaControles,GLuint *texturaInstrucoes,GLuint *texturaSair,GLuint *texturaMouse,GLuint *texturaWASD,GLuint *texturaSetas);
void botao(float botaoX, float botaoY, float largura,float altura, char * texto,GLuint textura);
void apontador(int selecionado,float botaoX,float botaoY);
void menu(int seleciona,GLuint texturaJogar,GLuint texturaControles,GLuint texturaInstrucoes,GLuint texturaSair,GLuint texturaMouse,GLuint texturaWASD,GLuint texturaSetas);

#endif /* menuPrincipal_h */
