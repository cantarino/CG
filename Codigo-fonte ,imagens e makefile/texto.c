#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>

//texto tamanho 12
void texto12(int x, int y, char *string)
{
    //seta a posicao do texto
    glRasterPos2f(x,y);
    //pega o tamanho da string
    int len = (int) strlen(string);
    //imprime a string
    for (int i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,string[i]);
    }
}

//texto tamanho 18
void texto18(int x, int y, char *string)
{
    //seta a posicao do texto
    glRasterPos2f(x,y);
    //pega o tamanho da string
    int len = (int) strlen(string);
    //imprime a string
    for (int i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,string[i]);
    }
}

void texto24(int x, int y, char *string)
{
    //seta a posicao do texto
    glRasterPos2f(x,y);
    //pega o tamanho da string
    int len = (int) strlen(string);
    //imprime a string
    for (int i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,string[i]);
    }
}
