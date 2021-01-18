#include <Windows.h> //acabei por utilizar o meso esquema para capturar as teclas do meu TPI (Marco Túlio)

#define VK_W 0x57
#define VK_S 0x53
#define VK_A 0x41
#define VK_D 0x44
#define VK_R 0x52
#define VK_F 0x46

#define PI 3.1415
#define w_width 1920
#define w_height 1080

typedef struct Player {
    float v[4];//vetor para posicao
    int mode;//primeira pessoa e etc
	double posx, posy, posz;
	double lx, ly, lz; //l=look at
	double teta;//teta marca o angulo no plano xz que a cam faz com x
	double phi;//phi marca o angulo no plano xy que a cam faz com y
    //o mundo eh orientado como se o plano xz fosse o chao e o eixo y eh o "para cima"
	double vel;
	double radius;
}Player, Persona;
typedef struct Mouse {
	int posx;
	int posy;
	int scroll;
	int state;
	int button;
}Mouse;

Player cam;
Mouse mouse;

enum { PANORAMICA,AMPLIADA,stPerson,sphericCam, centroParque};

int deltaX, deltaY; // Para o mousesao dinamico
int visaoBrinquedos=0;
double angulocamera=0;//só para o panoramica

int isDay;
int lightOn;
int fogOn;
int fov;

void wInScreen(char *string){
    for (char *c = string; *c != '\0'; c++) glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *c);
}

void mov_camera(int ue) {
	if (GetAsyncKeyState(VK_W)) {
		if(cam.mode==stPerson||cam.mode==sphericCam){
                cam.posx += (cam.vel / 10) * (cos(cam.teta) * sqrt(pow(cam.lx, 2) + pow(cam.lz, 2)));
                cam.posz += (cam.vel / 10) * (sin(cam.teta) * sqrt(pow(cam.lx, 2) + pow(cam.lz, 2)));
        }
	}
	if (GetAsyncKeyState(VK_S)) {
		if(cam.mode==stPerson||cam.mode==sphericCam){
                cam.posx -= (cam.vel / 10) * (cos(cam.teta) * sqrt(pow(cam.lx, 2) + pow(cam.lz, 2)));
                cam.posz -= (cam.vel / 10) * (sin(cam.teta) * sqrt(pow(cam.lx, 2) + pow(cam.lz, 2)));
        }
	}
	if (GetAsyncKeyState(VK_A)) {
		if(cam.mode==stPerson||cam.mode==sphericCam){
                cam.posx -= (cam.vel / 10) * (cos(cam.teta + PI / 2) * sqrt(pow(cam.lx, 2) + pow(cam.lz, 2)));
                cam.posz -= (cam.vel / 10) * (sin(cam.teta + PI / 2) * sqrt(pow(cam.lx, 2) + pow(cam.lz, 2)));
        }
	}
	if (GetAsyncKeyState(VK_D)) {
        if(cam.mode==stPerson||cam.mode==sphericCam){
            cam.posx += (cam.vel / 10) * (cos(cam.teta + PI / 2) * sqrt(pow(cam.lx, 2) + pow(cam.lz, 2)));
            cam.posz += (cam.vel / 10) * (sin(cam.teta + PI / 2) * sqrt(pow(cam.lx, 2) + pow(cam.lz, 2)));
        }
	}
	if (GetAsyncKeyState(VK_R)) {
		if(cam.mode==stPerson||cam.mode==sphericCam){
                cam.posy+=cam.vel*5;
        }
	}
	if (GetAsyncKeyState(VK_F)) {
		if(cam.mode==stPerson||cam.mode==sphericCam){
                cam.posy-=cam.vel*5;
        }
	}
	glutPostRedisplay();
	glutTimerFunc(1000/60,mov_camera,0);
}

void mousesao(int button, int state, int x, int y) {
	mouse.button = button; mouse.state = state;
    if (mouse.scroll >=100) {
		mouse.scroll = 100;

	}
	if (mouse.scroll <= 10) {
		mouse.scroll = 10;
	}
	if (button == 4) {
		mouse.scroll++;
		fov+=20;
	}
	if (button == 3) {
		mouse.scroll--;
		fov-=20;
	}
}
void mousesaoDinamico(int x, int y) {
	y = y - w_height;
	deltaX = x - mouse.posx;
	deltaY = y - mouse.posy;

    cam.teta += ((double)deltaX/(double)w_width) * PI * 2;
    cam.phi  += ((double)deltaY/(double)w_height)* PI * 2;

    glutWarpPointer(w_width/2, w_height/2);
    mouse.posy = w_height/2;
    mouse.posx = w_width/2;
	glutPostRedisplay();
}
void teclado(unsigned char key, int x, int y) {
    if (cam.mode == sphericCam) {//pois no modo esferico a direcao do look at é contraria ao movimento
		cam.lx = -cam.lx;
		cam.lz = -cam.lx;
	}
	else {
		cam.lx =cam.lx;
		cam.lz =cam.lx;
	}
    switch (key) {
        //"Esta faltandu identaciooon nu case" - Érick Jacquin Brazilian-French chef
        case 27:
            exit(0);
            break;
        case '1':
            cam.mode=PANORAMICA;
            break;
        case '2':
            cam.mode=AMPLIADA;
            break;
        case 'a':
            if(cam.mode==PANORAMICA)
                angulocamera+=0.1;
            if((cam.mode==AMPLIADA || cam.mode == centroParque)&& visaoBrinquedos<1)
                visaoBrinquedos++;
            break;
        case 'd':
            if(cam.mode==PANORAMICA)
                angulocamera-=0.1;
            if((cam.mode==AMPLIADA || cam.mode == centroParque) && visaoBrinquedos>-1)
                visaoBrinquedos--;
            break;
        case '3':
            cam.mode = stPerson;
            break;
        case '4':
            cam.mode = sphericCam;
            break;
        case '5':
            cam.mode= centroParque;
            break;
        case 'c'://para resetar as posicoes da cam na primeira e terceira pessoa
            cam.phi = PI / 2;
            cam.teta = 0;
            cam.lx=0;
            cam.ly=0;
            cam.lz=0;
            break;
        case 'l':
            if(lightOn){
                lightOn = 0;
            }else{
                lightOn = 1;
            }
            break;
        case 'k':
            if(fogOn){
                fogOn=0;
            }else{
                fogOn=1;
            }
            break;
    }
    glutPostRedisplay();
}

