#include <math.h>
#define PI 3.1415
//só funcoes basicas para desenhar as estruturas
void desenhaBase(){
    glColor3f(0.6,0.6,0.6);
    glPushMatrix();
    glRotated(270,1,0,0);
    glutSolidCone(2.0,2.0,10.0,10.0);
    glPopMatrix();
}
void desenhaRoda(int anguloRoda){
    glColor3f(0.6,0.6,0.6);
    glPushMatrix();
    glRotated(anguloRoda,0,0,1);
    glutSolidTorus(0.5,3.0,10.0,10.0);
    glPopMatrix();
}
void desenhaCabineUnica(int anguloRoda){
    glPushMatrix();
    glRotated(270,1,0,0);
    glColor3f(0.0,1.0,0.0);
    glutSolidCylinder(0.5,1.0,10.0,10.0);
    glRotated(-270,1,0,0);
    glTranslated(0.0,1.0,0.0);
    glColor3f(0.0,0.0,0.0);
    glRotated(270,1,0,0);
    glutSolidCone(1.0,1.0,10.0,10.0);
    glRotated(-270,1,0,0);
    glPopMatrix();
}
void desenhaCabines(int anguloRoda){
       for(double i=0;i<=2;i+=0.5){
        glPushMatrix();
        glTranslated((3*cos(i*PI)),(3*sin(i*PI)),0.0);
        glRotated(-anguloRoda,0,0,1);
        desenhaCabineUnica(anguloRoda);
        glPopMatrix();
       }
}

void desenhaRodaGigante(int anguloRoda){
    glPushMatrix();
    desenhaBase();
        glPushMatrix();
        glTranslated(0.0,5.0,1.0);
        desenhaRoda(anguloRoda);
        glTranslated(0.0,0.0,-2.0);
        desenhaRoda(anguloRoda);
        glTranslated(0.0,0.0,2.0);
            glPushMatrix();
            glRotated(anguloRoda,0,0,1);
            glTranslated(0.0,0.0,-1.0);
            desenhaCabines(anguloRoda);
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}
