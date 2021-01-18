#define PI 3.1415
//só funcoes basicas para desenhar as estruturas
void desenhaBase2(){
    glColor3f(0.6,0.6,0.6);
    glPushMatrix();
    glRotated(270,1,0,0);
    glutSolidCylinder(3.5,0.5,10.0,10.0);
    glPopMatrix();
}
void desenhaPilar(){
    glColor3f(1.0,0.0,0.0);
    glPushMatrix();
    glRotated(270,1,0,0);
    glutSolidCylinder(0.5,3.0,10.0,10.0);
    glPopMatrix();
}

void desenhaChaleira(int rotacaoXicara){
    glColor3f(0.8,0.0,0.8);
    glPushMatrix();
    glTranslated(0.0,3.5,0.0);
    glRotated(-rotacaoXicara,0,1,0);
    glutSolidTeapot(1.0);
    glPopMatrix();
}
void desenhaJogodeXicaras(){
    glColor3f(0.8,0.0,0.8);
    glPushMatrix();
    glTranslated(1.0,0.5,0.0);
    glRotated(0,0,1,0);
    glutSolidTeapot(1.0);
    glPopMatrix();
    glPushMatrix();
    glTranslated(2.0,0.5,0.0);
    glRotated(180,0,1,0);
    glutSolidTeapot(1.0);
    glPopMatrix();
    glPushMatrix();
    glTranslated(1.5,0.5,0.5);
    glRotated(90,0,1,0);
    glutSolidTeapot(1.0);
    glPopMatrix();
    glPushMatrix();
    glTranslated(1.5,0.5,-0.5);
    glRotated(270,0,1,0);
    glutSolidTeapot(1.0);
    glPopMatrix();

}
void desenhaXicaras(){
    for(double i=0;i<=2;i+=0.5){
        glPushMatrix();
        glTranslated((2*cos(i*PI))-1.5,0.0,(2*sin(i*PI)));
        desenhaJogodeXicaras();
        glPopMatrix();
    }

}

void desenhaChaleiraMaluca(int rotacaoXicara){
    glPushMatrix();
    desenhaBase2();
        glPushMatrix();
    glRotated(rotacaoXicara,0,1,0);
    desenhaPilar();
    desenhaXicaras();
        glPopMatrix();
    desenhaChaleira(rotacaoXicara);
    glPopMatrix();
}
