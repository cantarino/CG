//
//  botao.c
//  ComputacaoGrafica
//
//  Created by Marcus Cantarino on 16/04/2018.
//  Copyright © 2018 Marcus Cantarino. All rights reserved.
//

#include "botao.h"
#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "texto.h"
#include "texto.h"

#define PI 3.14159265

void texturasMenu(*GLuint texturaJogar){
      *texturaJogar = SOIL_load_OGL_texture(
      "jogar.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
      );

      if (texturaJogar == 0) {
          printf("Erro do SOIL: '%s'\n", SOIL_last_result());
      }
}
