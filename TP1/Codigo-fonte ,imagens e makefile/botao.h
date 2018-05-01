//
//  botao.h
//  ComputacaoGrafica
//
//  Created by Marcus Cantarino on 16/04/2018.
//  Copyright © 2018 Marcus Cantarino. All rights reserved.
//

#ifndef botao_h
#define botao_h

#include "desenha.h"
#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "texto.h"

void texturasBotoes(*GLuint texturaJogar);
void botao(float botaoX,float botaoY,float largura,float altura,char * texto);

#endif /* botao_h */
