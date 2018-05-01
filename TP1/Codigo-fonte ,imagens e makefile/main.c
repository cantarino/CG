#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL.h>
#include "texto.h"
#include "desenha.h"
#include "menuPrincipal.h"

#define PI 3.14159265

GLuint texturaBodao,texturaFogo,texturaBG,texturaCaneca,texturaJogar,texturaControles,texturaInstrucoes,texturaSair,texturaMouse,texturaWASD,texturaSetas;

struct ponto {
    float x, y;
};
struct tamanho {
    float largura, altura;
};

struct ponto posicaoPersonagem,velocidade,posicaoChao,posicaoCheckpoint;
struct tamanho tamanhoPersonagem,tamanhoChao,tamanhoCheckpoint;

float anguloRotacao = 0;
float tempo;
int mousePress = 0;
int vidas = 4;
int setup = 0;//0 rodando teclado //1 pausado no p //2 pausado no esc //3 subindo mouse //pausado no r
int fogo = 0;
int ativaMenu = 1;//menu ativo ou jogo
int seleciona = 0;
int aponta = 0;//apontador
int conf = 0;//confirma selecao da opcao no menu
int setControles = 0;//0 setas //1 wasd //2 mouse

void tocar_musica(char const nome[40], int loop){
        Mix_Chunk *som = NULL;
        int canal;
	int canal_audio=2;
        int taxa_audio = 22050;
        Uint16 formato_audio = AUDIO_S16SYS;
        int audio_buffers = 4096;
        if(Mix_OpenAudio(taxa_audio, formato_audio, canal_audio, audio_buffers) != 0) {
                printf("Não pode inicializar audio: %s\n", Mix_GetError());
        }
       som = Mix_LoadWAV(nome);
        if(som == NULL) {
                printf("Não pode inicializar audio: %s\n", Mix_GetError());
        }
       Mix_HaltChannel(-1);
       canal = Mix_PlayChannel( -1, som, loop);
        if(canal == -1) {
                printf("Não pode inicializar audio: %s\n", Mix_GetError());
        }
}

void parar_musica(){
	Mix_HaltChannel(-1);

}

void inicializa(){//inicio e reset do jogo
    inicializaTexturas(&texturaBodao,&texturaFogo,&texturaBG,&texturaCaneca);
    // define tudo
    posicaoPersonagem.x = 100;//inicio do personagem em x e y
    posicaoPersonagem.y = 100;
    tamanhoPersonagem.largura = 120;//largura e altura do personagem
    tamanhoPersonagem.altura = 120;
    velocidade.x = 0;//velocidade inicial em x e y
    velocidade.y = 1;
    anguloRotacao = 0;//angulo de rotacao inicial
    posicaoChao.x = 0;//posicao do chao em x e y
    posicaoChao.y = 700;
    tamanhoChao.largura = 1280;//largura e altura do chao
    tamanhoChao.altura = 30;
    posicaoCheckpoint.x = 100;//posicao do checkpoint 1 em x e y
    posicaoCheckpoint.y = 600;
    tamanhoCheckpoint.altura = 250;//largura e altura dos checkpoints
    tamanhoCheckpoint.largura = 200;
    tempo = 0;//inicia tempo
    fogo = 0;//inicia foguinho
    vidas--;//diminui vidas

}

void setSpeed(unsigned char key){//seta a velocidade
    if(key=='w')//subindo
        if(setup==0 || mousePress==1){//caso nao pausado ou mouse ativo calcula velocidade
            velocidade.x+=(sin(anguloRotacao*(PI/180)))*1;
            velocidade.y-=(cos(anguloRotacao*(PI/180)))*1;
            if(fogo<40)
              fogo += 2;
        }
    if(key=='s'){//gravidade
        if(setup==0){//caso nao pausado cacula gravidade
            velocidade.y+=0.027;
            if(velocidade.x>0)
                velocidade.x-=0.005;
            if(velocidade.x<0)
                velocidade.x+=0.005;
        }
        if(fogo>0)
          fogo--;
      }
}

void pausa(){//pausa o jogo
    if(setup==1||setup==2)
        setup=0;
    else
        setup=1;
}

void sair(){//pausa e jogo e confirma saida
    pausa();
    setup=2;
}

void reset(){//reinicia o jogo
    vidas=4;
    inicializa();
}

void desenhaJogo(){//desenha o jogo
      glColor3f(1,1,1);//cor branca
      glEnable(GL_TEXTURE_2D);//habilita o uso de texturas
      setBG(texturaBG);//desenha background
      setprincipal(posicaoPersonagem.x, posicaoPersonagem.y, anguloRotacao, tamanhoPersonagem.largura,texturaBodao);//desenha principal
      for(int i=0;i<5;i++)//desenha checkpoints
        setCheckpoint(posicaoCheckpoint.x + 230*i,posicaoCheckpoint.y,tamanhoCheckpoint.largura,tamanhoCheckpoint.altura,texturaCaneca);
      setChao(posicaoChao.x, posicaoChao.y, tamanhoChao.altura, tamanhoChao.largura);//seta o chao "invisivel"
      if(fogo>0)//seta foguinho
        setFogo(posicaoPersonagem.x, posicaoPersonagem.y, anguloRotacao, tamanhoPersonagem.largura,texturaFogo);
      glDisable(GL_TEXTURE_2D);//desliga texturas
      setHud(velocidade.x, velocidade.y, posicaoPersonagem.y, tempo, setup,vidas);//seta HUD
}

void sobe(){
    if(aponta<=3 && aponta > 0)//sobe com o seleciona
        aponta--;
    else
        aponta = 0;
}

void desce(){
    if(aponta<3)//desce com o seleciona
        aponta++;
    else
        aponta = 0;
}

void confirma(){
    conf = 1;
}

void setControl(){
    if(aponta==0){//set mouse
        if(conf==1){
            setControles=2;
            conf=0;
        }
    }
    if(aponta==1){
        if(conf==1){//set WASD
          setControles=1;
          conf=0;
        }
    }
    if(aponta==2){//set setas
        if(conf==1){
        setControles=0;
        conf=0;
      }
    }
    if(aponta==3){//voltar pro menuPrincipal
        conf=0;
        seleciona = 0;
    }
}

void setMenu(){//controla menu
    if(seleciona==2){//set controles
        setControl();
  }
    if(aponta==0){
        if(conf==1){
            ativaMenu = 0;//inicia jogo
        }
    }
    if(aponta==1){//set controles
        if(conf==1){
            conf = 0;
            seleciona=1;
        }
    }
    if(aponta==2){
        if(conf==1){//instrucoes
          conf = 0;
          seleciona = 2;
        }
    }
    if(aponta==3){
        if(conf==1){
            exit(0);
        }
    }//sair
}

void desenhaMenu(){//desenha menu

    setMenu();
    menu(seleciona,texturaJogar,texturaControles,texturaInstrucoes,texturaSair,texturaMouse,texturaWASD,texturaSetas);
    apontador(aponta,500, 100);

    glutPostRedisplay();
}

void desenhaCena(void){//desenha tela
    glClear(GL_COLOR_BUFFER_BIT);//limpa a tela

    if(ativaMenu==0)//se menu nao ativo
      desenhaJogo();
    if(ativaMenu==1)//se menu ativo
      desenhaMenu();

    glutSwapBuffers();//troca os buffers
}

void redimensiona(int w, int h)// callback de redimensionamento
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, h, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void mouse(int button,int state,int x,int y){//callback mouse
    if(button==3)//roda p/ cima
        anguloRotacao+=1.2;
    if(button==4)//roda p/baixo
        anguloRotacao-=1.2;
    if(button==GLUT_LEFT_BUTTON && state == GLUT_DOWN)//mouse pressionado
        mousePress = 1;
    if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)//mouse levantado
        mousePress = 0;
}

void teclado(unsigned char key, int x, int y){// callback de teclado (teclas normais)
    if(ativaMenu==0){
        if(key==27 && setup==2){//sai
          exit(0);
        }
        if(key=='r' && setup==4){
          vidas=4;
          inicializa();
        }
        if(key==27)//confirma saida
          sair();
        if(key=='a')//esquerda
          anguloRotacao-=5;
        if(key=='d')//direita
          anguloRotacao+=5;
        if(key=='w')//ativa motor
          setSpeed(key);
        if(key=='r')//reseta jogo
          setup=4;
        if(key=='p')//pausa jogo
          pausa();
    }
    if(ativaMenu==1){
      if(key=='s')
        desce();
      if(key=='w')
        sobe();
      if(key==13)
        confirma();
    }
}

void tecladoEspecial(int key,int x,int y){//callback  do teclado (teclas especiais)
    if(ativaMenu == 0){
      if(key==GLUT_KEY_UP)// cima
        setSpeed('w');
      if(key==GLUT_KEY_LEFT)//esquerda
        anguloRotacao-=5;
      if(key==GLUT_KEY_RIGHT)//direita
        anguloRotacao+=5;
    }
    if(ativaMenu == 1){
      if(key==GLUT_KEY_DOWN)
        desce();
      if(key==GLUT_KEY_UP)
        sobe();
    }
}

int endGame(){//testa condicao de vitoria
    int i;
    for(i=0;i<5;i++)
      if(posicaoPersonagem.y >= 545)//colisao em y
        if(230*i + 125<=posicaoPersonagem.x && posicaoPersonagem.x<=160 + 230*i)//colisoes em x
          return 1;//vitoria
    return 0;
}

void gameover(){
    if((posicaoChao.y-posicaoPersonagem.y<tamanhoPersonagem.largura/2) ||posicaoPersonagem.y + tamanhoPersonagem.altura <0
    || posicaoPersonagem.y>720 || posicaoPersonagem.x>1280 || posicaoPersonagem.x + tamanhoPersonagem.largura < 0 )//morte ou offscreen
        inicializa();
    if(endGame()){//caso vitoria
      vidas++;//mesmo numero de vidas,fase reseta
      inicializa();
      pausa();
    }
    if(vidas==0)//game over
        exit(0);
}

void setCharacter(){//desloca o personagem
    posicaoPersonagem.x+=velocidade.x;
    posicaoPersonagem.y+=velocidade.y;
}

void setTempo(){//registra tempo
    tempo++;
}

void atualiza(int indice) {
    if(ativaMenu==0)
      if(setup==0){
        setCharacter();
        setTempo();
    }
    if(mousePress==1 && ativaMenu == 0)
        setSpeed('w');
    if(ativaMenu==0)
      gameover();//testa fim de jogo
    //redesenha
    glutPostRedisplay();
    if(ativaMenu==0)
      setSpeed('s');

    glutTimerFunc(25, atualiza, 0);// dispara o timer de 25 ms (40 fps(pra facilitar marcar tempo))
}

int main(int argc, char **argv){// funcao principal

    glutInit(&argc, argv);  // configuracao inicial da janela
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(1280, 720);
    glutInitWindowPosition(0, 0);

    glutCreateWindow("Hell's Beer");

    tocar_musica("musica.wav",1);

    if(ativaMenu==0)
      inicializa();
    if(ativaMenu==1)
      texturasMenu(&texturaJogar,&texturaControles,&texturaInstrucoes,&texturaSair,&texturaMouse,&texturaWASD,&texturaSetas);

    glutDisplayFunc(desenhaCena);
    glutReshapeFunc(redimensiona);
    glutKeyboardFunc(teclado);
    glutSpecialFunc(tecladoEspecial);
    glutMouseFunc(mouse);
    glutTimerFunc(0, atualiza, 0);

    glutMainLoop();
    return 0;
}
