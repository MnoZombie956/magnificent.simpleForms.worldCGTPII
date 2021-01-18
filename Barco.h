//só funcoes basicas para desenhar as estruturas
void desenhaBase3(int angulo){
    glColor3f(0.6,0.6,0.6);
    glPushMatrix();
    glRotated(angulo,1,0,0);
    glScaled(1.0,8.0,0.5);
    glutSolidCube(1.0);
    glPopMatrix();

}
void desenhaSuporte(){
    glColor3f(0.6,0.6,0.6);
    glPushMatrix();
    glScaled(6.0,1.0,1.0);
    glutSolidCube(1.0);
    glPopMatrix();
}

void desenhaCasco(){
    glColor3f(0.6,0.3,0.0);
    glPushMatrix();
    glScaled(1.0,1.0,4.0);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0.0,1.0,2.0);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0.0,1.0,-2.0);
    glutSolidCube(1.0);
    glPopMatrix();
}
void desenhaMastro(int rotacaoBarco ){
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslated(-0.25,2.0,0.0);
    glScaled(0.0,2.0,3.0);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6,0.3,0.0);
    glRotated(270,1,0,0);
    glutSolidCylinder(0.25,4.0,10.0,10.0);
    glPopMatrix();
}

void desenhaBarco(int rotacaoBarco){
    glPushMatrix();
    desenhaBase3(30);
    glTranslated(-5.0,0.0,0.0);
    desenhaBase3(30);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0.0,0.0,5.0);
    desenhaBase3(-30);
    glTranslated(-5.0,0.0,0.0);
    desenhaBase3(-30);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-2.5,4.0,2.5);
    desenhaSuporte();
        glPushMatrix();
        glRotated(rotacaoBarco,1,0,0);
        glTranslated(0.0,-4.0,0.0);
        desenhaMastro(rotacaoBarco);
        desenhaCasco();
        glPopMatrix();
    glPopMatrix();


}

