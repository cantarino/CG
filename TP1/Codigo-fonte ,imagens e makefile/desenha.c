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

//comentario

#define PI 3.14159265

void inicializaTexturas(GLuint *texturaBodao,GLuint *texturaFogo,GLuint *texturaBG,GLuint *texturaCaneca){//mapeia texturas do jogo

    glClearColor(1, 1, 1, 0);

    glEnable(GL_BLEND );// habilita mesclagem de cores, para termos suporte a texturas (semi-)transparentes
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    *texturaBodao = SOIL_load_OGL_texture(
        "bodao.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
    SOIL_FLAG_INVERT_Y
  );

    if (texturaBodao == 0) {
        printf("Erro do SOIL: '%s'\n", SOIL_last_result());
    }

    *texturaFogo = SOIL_load_OGL_texture(
        "fogo.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
    SOIL_FLAG_INVERT_Y
  );

    if (texturaFogo == 0) {
        printf("Erro do SOIL: '%s'\n", SOIL_last_result());
    }

    *texturaBG = SOIL_load_OGL_texture(
        "vulcao.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
    SOIL_FLAG_INVERT_Y
  );

    if (texturaBG == 0) {
        printf("Erro do SOIL: '%s'\n", SOIL_last_result());
    }

    *texturaCaneca = SOIL_load_OGL_texture(
        "cerva.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
    SOIL_FLAG_INVERT_Y
  );

    if (texturaCaneca == 0) {
        printf("Erro do SOIL: '%s'\n", SOIL_last_result());
    }

}

void setFogo(float personagemX,float personagemY,float anguloRotacao,float personagemLargura,GLuint texturaFogo){
  glColor3f(0, 1, 1);//foguinho verde

  glPushMatrix();
  //translada,rotaciona em z e desenha foguinho
  glTranslatef(personagemX,personagemY,0);
  glRotatef(anguloRotacao,0,0,1);
  //comeca a usar a texturaFogo
  glBindTexture(GL_TEXTURE_2D,texturaFogo);
  glBegin(GL_TRIANGLE_FAN);
  glTexCoord2f(0, 0);         glVertex3f(0, personagemLargura/2, 0);//desenha o fogo como um retangulo que comeca na metade do personagem pra parecer que sai da boca dele
  glTexCoord2f(0, 1);         glVertex3f(personagemLargura, personagemLargura/2, 0);
  glTexCoord2f(1, 1);         glVertex3f(personagemLargura, personagemLargura, 0);
  glTexCoord2f(1, 0);         glVertex3f(0,personagemLargura, 0);
  glEnd();

  glPopMatrix();
}

void setprincipal(float personagemX,float personagemY,float anguloRotacao,float personagemLargura,GLuint texturaBodao){

    glPushMatrix();
    //translada,rotacionao e desenha personagem
    glTranslatef(personagemX,personagemY,0);
    glRotatef(anguloRotacao,0,0,1);
    //habilita o uso de texturas
    //comeca a usar a texturaBodao
    glBindTexture(GL_TEXTURE_2D,texturaBodao);
    glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f(0, 1);         glVertex3f(0, 0, 0);//desenha o personagem como um quadrado
    glTexCoord2f(1, 1);         glVertex3f(personagemLargura, 0, 0);
    glTexCoord2f(1, 0);         glVertex3f(personagemLargura, personagemLargura, 0);
    glTexCoord2f(0, 0);         glVertex3f(0,personagemLargura, 0);
    glEnd();

    glPopMatrix();

}

void setChao(float chaoX,float chaoY,float chaoAltura,float chaoLargura){

    glPushMatrix();
    //translada e desenha chao
    glTranslatef(chaoX, chaoY, 0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0,0,0);//desenha o chao "invisivel" como um retangulo
    glVertex3f(chaoLargura, 0, 0);
    glVertex3f(chaoLargura, chaoAltura, 0);
    glVertex3f(0, chaoAltura, 0);
    glEnd();

    glPopMatrix();

}

void setCheckpoint(float checkX,float checkY,float checkLargura,float checkAltura,GLuint texturaCaneca){

  glPushMatrix();
  //translada,rotacionao e desenha personagem
  glTranslatef(checkX,checkY,0);
  //comeca a usar a texturaCaneca
  glBindTexture(GL_TEXTURE_2D,texturaCaneca);
  glBegin(GL_TRIANGLE_FAN);
  glTexCoord2f(0, 1);         glVertex3f(0, 0, 0);//desenha a caneca como um quadrado
  glTexCoord2f(1, 1);         glVertex3f(checkLargura, 0, 0);
  glTexCoord2f(1, 0);         glVertex3f(checkLargura, checkAltura, 0);
  glTexCoord2f(0, 0);         glVertex3f(0,checkAltura, 0);
  glEnd();

  glPopMatrix();

}

void setHud(float velocidadeX,float velocidadeY,float posicaoY,float tempo,int setup,int vidas){
    glColor3f(1,1,1);//cor branca
    //desenha Heads Up Display(HUD) do jogador
    char c[50];
    texto18(1025,20,"Velocidade Vertical:");
    sprintf(c, "%g", -velocidadeY);//converte float para string
    texto12(1200,18,c);
    texto18(1025,40,"Velocidade Horizontal:");
    sprintf(c,"%g",velocidadeX);
    texto12(1220,40,c);
    texto18(1025,60,"Altitude:");
    sprintf(c,"%g",(680-posicaoY));//tamanhanho do mundo - altura chao
    texto12(1100,60,c);
    texto18(1025,80,"Tempo:");
    float tempo_arredondado = floorf((tempo/40) * 10) / 10;//arredonda tempo para 1 casa decimal
    sprintf(c,"%g",tempo_arredondado);
    texto12(1100,80,c);
    texto18(1025,100,"Vidas:");
    sprintf(c,"%d",vidas);
    texto12(1080,100,c);

    if(setup==1)//jogo pausado
        texto18(600, 200, "JOGO PAUSADO");
    if(setup==2){//jogo pausado no esc
        texto18(600, 200, "DESEJA SAIR?");
        texto18(550, 230, "Pressione esc para confirmar");
        texto18(560, 260, "Pressione p para continuar");
    }
    if(setup==4){
      texto18(600, 200, "DESEJA REINICIAR?");
      texto18(550, 230, "Pressione r para confirmar");
      texto18(560, 260, "Pressione p para continuar");
    }

}

void setBG(GLuint texturaBG){
  //comeca a usar a texturaBG
  glBindTexture(GL_TEXTURE_2D,texturaBG);
  glBegin(GL_TRIANGLE_FAN);
  glTexCoord2f(0, 1);         glVertex3f(0, 0, 0);//desenha toda a tela como BG
  glTexCoord2f(1, 1);         glVertex3f(1280, 0, 0);
  glTexCoord2f(1, 0);         glVertex3f(1280,720 , 0);
  glTexCoord2f(0, 0);         glVertex3f(0,720, 0);
  glEnd();

  glPopMatrix();
}
