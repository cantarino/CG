//
//  menuPrincipal.c
//  ComputacaoGrafica
//
//  Created by Marcus Cantarino on 16/04/2018.
//  Copyright © 2018 Marcus Cantarino. All rights reserved.
//
#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "texto.h"

void texturasMenu(GLuint *texturaJogar,GLuint *texturaControles,GLuint *texturaInstrucoes,GLuint *texturaSair,GLuint *texturaMouse,GLuint *texturaWASD,GLuint *texturaSetas){
      *texturaJogar = SOIL_load_OGL_texture(
      "jogar.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
      );

      if (texturaJogar == 0) {
          printf("Erro do SOIL: '%s'\n", SOIL_last_result());
      }

      *texturaControles = SOIL_load_OGL_texture(
      "controles.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
      );

      if (texturaControles == 0) {
          printf("Erro do SOIL: '%s'\n", SOIL_last_result());
      }

      *texturaInstrucoes = SOIL_load_OGL_texture(
      "instrucoes.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
      );

      if (texturaInstrucoes == 0) {
          printf("Erro do SOIL: '%s'\n", SOIL_last_result());
      }

      *texturaSair = SOIL_load_OGL_texture(
      "sair.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
      );

      if (texturaSair == 0) {
          printf("Erro do SOIL: '%s'\n", SOIL_last_result());
      }

      *texturaMouse = SOIL_load_OGL_texture(
      "mouse.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
      );

      if (texturaMouse == 0) {
          printf("Erro do SOIL: '%s'\n", SOIL_last_result());
      }

      *texturaWASD = SOIL_load_OGL_texture(
      "wasd.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
      );

      if (texturaWASD == 0) {
          printf("Erro do SOIL: '%s'\n", SOIL_last_result());
      }

      *texturaSetas = SOIL_load_OGL_texture(
      "setas.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
      );

      if (texturaSetas == 0) {
          printf("Erro do SOIL: '%s'\n", SOIL_last_result());
      }
}

void botao(float botaoX, float botaoY, float largura,float altura, char * texto,GLuint textura){
    glColor3f(1, 1, 1);

    glPushMatrix();
    //translada e desenha botao
    glTranslatef(botaoX,botaoY,0);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0, 0, 0);                glTexCoord2f(1,1);
    glVertex3f(largura, 0, 0);          glTexCoord2f(1,0);
    glVertex3f(largura, altura, 0);     glTexCoord2f(0,0);
    glVertex3f(0,altura, 0);            glTexCoord2f(0,1);
    glEnd();

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    //escreve texto do botao
    glColor3f(1,0,0);
    texto24(botaoX + 5*largura/12, botaoY + 2*altura/3, texto);


}

void apontador(int selecionado,float botaoX,float botaoY){
    glColor3f(1, 0, 0);

    float largura,altura;
    largura=altura=30;


    glPushMatrix();
    //translada e desenha apontador do botao selecionado
    glTranslatef(botaoX-largura-10,botaoY+altura/3 + 150*selecionado,0);//apontador do menu principal

    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0, 0, 0);
    glVertex3f(largura, 0, 0);
    glVertex3f(largura, altura, 0);
    glVertex3f(0,altura, 0);
    glEnd();

    glPopMatrix();
}

void menu(int seleciona,GLuint texturaJogar,GLuint texturaControles,GLuint texturaInstrucoes,GLuint texturaSair,GLuint texturaMouse,GLuint texturaWASD,GLuint texturaSetas){
    int i;
    char c [4][50] = {"Jogar","Controles","Instrucoes","Sair"};// botoes do menu principal
    char c2 [4][50] = {"Mouse","WASD","Setas Direcionais","Sair"};//botoes menu controles
    if(seleciona==0){//menu principal selecionado
        for(i=0;i<4;i++){//desenha botoes menu principal
            if(i==0){
                botao(500, 100 + 150*i, 300, 50, c[i],texturaJogar);
            }
            if(i==1){
                botao(500, 100 + 150*i, 300, 50, c[i],texturaJogar);
            }
            if(i==2){
                botao(500, 100 + 150*i, 300, 50, c[i],texturaJogar);
            }
            if(i==3){
                botao(500, 100 + 150*i, 300, 50, c[i],texturaJogar);
            }
        }
    }
    if(seleciona==1){//menu controles selecionado
        for(i=0;i<4;i++){//desenha botoes menu controles
            if(i==0){
              botao(500, 100 + 150*i, 300, 50, c2[i],texturaJogar);
            }
            if(i==1){
              botao(500, 100 + 150*i, 300, 50, c[i],texturaJogar);
            }
            if(i==2){
              botao(500, 100 + 150*i, 300, 50, c[i],texturaJogar);
            }
            if(i==3){
              botao(500, 100 + 150*i, 300, 50, c[i],texturaJogar);
            }
        }
    }
    if(seleciona==2){//menu instrucoes selecionado
        texto18(100,100,"teste");
      }
}
