/*
Greetings Fegemo !

Francisco Abreu :D
Marco Túlio Siqueira da Mata :P

CG (2019.2) Prof. Flávio Coutinho
Eng. Comp
CEFET_MG
*/
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SOIL/SOIL.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "Controles.h"
#include "DesenhaGeral.h"

enum { MENU,PLAYING,OPTIONS,PAUSE};

int gameMode; //sem tempo de implementar

GLfloat cor[] = { 0.2, 0.2, 0.3 };//para o fog

void inicilizaLuzes(){
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glEnable(GL_COLOR_MATERIAL);
    glShadeModel (GL_SMOOTH);

    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mShininess);

    glLightfv(GL_LIGHT0, GL_SPECULAR, white);
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzSol);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzSol);
}
void inicilizaValores(){
    cam.posx = 0;
	cam.posy = 50;
	cam.posz = 100;
	cam.lx = 1;
	cam.ly = 0;
	cam.lz = 0;
	cam.teta = 0;
	cam.phi = PI / 2;
	cam.mode = PANORAMICA;
	cam.vel = 0.5;// passos curtos para suaavidade

	mouse.scroll = 50;//0 a 100

	gameMode = PLAYING; //Mudar para menu na versao fina

	isDay=1;
	lightOn=1;
	fogOn=1;
	phisol=PI/2;//começa de manha
}
void inicializa() {
    glClearColor(0, .5, 1, 1);//azul bebe do fundo que depois sera modificado

    inicilizaValores();

    glEnable(GL_DEPTH_TEST);
    glEnable( GL_BLEND );

    glFogi(GL_FOG_MODE, GL_EXP2);
    glFogfv(GL_FOG_COLOR, cor);
    glFogf(GL_FOG_DENSITY, .005);
    glHint(GL_FOG_HINT, GL_NICEST);
    glFogf(GL_FOG_START, 60.f);
    glFogf(GL_FOG_END, 100.0f);
    glEnable(GL_FOG); // inicialmente ligado

    glClearDepth(1);

    inicilizaLuzes();
}
void setLookAt() {
	cam.lx = 100 * ((double)mouse.scroll / 100) * sin(cam.phi) * cos(cam.teta);
	cam.lz = 100 * ((double)mouse.scroll / 100) * sin(cam.phi) * sin(cam.teta);
	cam.ly = 100 * ((double)mouse.scroll / 100) * cos(cam.phi);
	switch (cam.mode)//melhor parte ever
	{
		case stPerson: {
			gluLookAt(
				cam.posx, cam.posy, cam.posz,
				cam.posx+cam.lx, cam.posy+cam.ly, cam.posz+cam.lz,
				0, 1, 0
			);
			break;
		}
		case sphericCam: {
			gluLookAt(
				cam.posx + cam.lx, cam.posy + cam.ly, cam.posz + cam.lz,
				cam.posx, cam.posy, cam.posz,
				0, 1, 0
			);
			break;
		}
		case PANORAMICA: {
		    gluLookAt(200*cos(angulocamera),100,100+200*sin(angulocamera),0,30,100, 0, 1, 0);
			break;
		}
		case AMPLIADA: {
		    switch(visaoBrinquedos){//visao da entrada do parque na perspectiva de um visitante
                case -1:
                    gluLookAt(0,50,100,-50,30,10*10,0,1,0);
                    break;
                case 0:
                    gluLookAt(-1,5,5,-1,5,15,0,1,0);
                    break;
                case 1:
                    gluLookAt(-2,5,10,5,5,10,0,1,0);
                break;
            }
			break;
		}
		case centroParque:{
		    switch(visaoBrinquedos){//visao da entrada do parque na perspectiva de um visitante
                case -1:
                    gluLookAt(-10,30,110,-10+1,30,110,0,1,0);
                    break;
                case 0:
                    gluLookAt(-10,30,110,-10-1,30,110,0,1,0);
                    break;
                case 1:
                    gluLookAt(-10,30,110,-10,30,110+1,0,1,0);
                break;
            }
			break;
		}
	}
}
void desenhaCena() {
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glPushMatrix();
    {
        setLookAt();

        if(lightOn){
            glEnable(GL_LIGHTING);
            glEnable(GL_LIGHT0);
            glEnable(GL_LIGHT1);
        }else{
            glDisable(GL_LIGHTING);
            glDisable(GL_LIGHT0);
            glDisable(GL_LIGHT1);
        }
        if(fogOn){
            glEnable(GL_FOG);
        }else{
            glDisable(GL_FOG);
        }
        glScalef(10,10,10);//estava muito pequeno
        desenhaCenario();//esta na desenhaGeral
        desenhaBrinquedos();//idem
    }
    glPopMatrix();

    glutSwapBuffers();
}

void redesenha(int tempo){
    glutPostRedisplay();
    glutTimerFunc(1000/60,redesenha,0);
}

void redimensiona(int w, int h) {
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(cam.mode==stPerson?fov:75,(float)(w)/h, 1, 1000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
int main(int argc, char* argv[]) {

    glutInit(&argc, argv);

    glutInitContextVersion(2, 1);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(w_width, w_height);
    glutCreateWindow("Magnificent SimpleForms World");//logo, é obviamente explicito que se trata de um parque tematico :xx

    glutFullScreen();
    glutReshapeFunc(redimensiona);
    glutDisplayFunc(desenhaCena);

    glutKeyboardFunc(teclado);

    glutSetCursor(GLUT_CURSOR_NONE);//o mouse reseta sempra para o meio, mas vc nao o ve :D
    glutMouseFunc(mousesao);//para clicks
	glutPassiveMotionFunc(mousesaoDinamico);//para efeito hover

    glutTimerFunc(1000/60,redesenha,0);
    glutTimerFunc(1000/60,rotacao,0);
    glutTimerFunc(1000/60,mov_camera,0);
    glutTimerFunc(1000/60,dayLightCycle,0);

    inicializa();

    glutMainLoop();
    return 0;
}
