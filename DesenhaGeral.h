#include "rodaGigante.h"
#include "chaleiraMaluca.h"
#include "barco.h"
#include "ControleDia.h"

int rotacaoRoda=0;
int rotacaoXicara=0;
int rotacaoBarco=0;
int rotacaoObelisco=0;
int movimentoNavio=0;

//Alem de definir a emissao do poste de luz, o resto são só desenhos e logicazinhas para as rotações/translações

void movimentoBarco(){
    if(rotacaoBarco==90 || rotacaoBarco==-90)
        movimentoNavio++;
}
void rotacao(int tempo){//incrementa as variveis das funcoes de desenha
    rotacaoRoda = (rotacaoRoda + 1) % 360;
    rotacaoXicara = (rotacaoXicara + 1) % 360;
    movimentoBarco();
    if(movimentoNavio%2==0)
        rotacaoBarco = rotacaoBarco + 1;
    else
        rotacaoBarco = rotacaoBarco - 1;
    rotacaoObelisco = (rotacaoObelisco + 1) % 360;
    glutTimerFunc(1000/60,rotacao,0);
}

void desenhaLagoa(){
    double div=(2*PI)/20;
    glColor3f(0.0,0.4,1.0);
    glBegin(GL_TRIANGLE_FAN);
        for(int i=1;i<=20;i++){
            glVertex3f(-8+4.0*(cos(div*i)),0.1,18.0+4.0*(sin(div*i)));
    }
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
        for(int i=1;i<=20;i++){
            glVertex3f(-10+4.0*(cos(div*i)),0.1,22.0+4.0*(sin(div*i)));
    }
    glEnd();
}

void desenhaPortao() {
    glColor3f(0.6,0.6,0.6);
    glPushMatrix();
    glTranslated(0.5,0.5,0.0);
    glutSolidCube(1.0);
    glTranslatef(0.0,1.0,0.0);
    glutSolidCube(1.0);
    glTranslatef(0.0,1.0,0.0);
    glutSolidCube(1.0);
    glTranslatef(0.0,1.0,0.0);
    glutSolidCube(1.0);
    glTranslatef(-1.0,0.0,0.0);
    glutSolidCube(1.0);
    glTranslatef(-1.0,0.0,0.0);
    glutSolidCube(1.0);
    glTranslatef(-1.0,0.0,0.0);
    glutSolidCube(1.0);
    glTranslatef(0.0,-1.0,0.0);
    glutSolidCube(1.0);
    glTranslatef(0.0,-1.0,0.0);
    glutSolidCube(1.0);
    glTranslatef(0.0,-1.0,0.0);
    glutSolidCube(1.0);
    glPopMatrix();

}
void desenhaMuro(){
    glColor3f(0.6,0.6,0.6);

    glPushMatrix();
    glTranslated(5.0,0.5,0.0);
    glScalef(20.0,1.0,0.5);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-10.0,0.5,0.0);
    glScalef(20.0,1.0,0.5);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslated(15.0,0.5,15.0);
    glScalef(0.5,1.0,30.0);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-20.0,0.5,15.0);
    glScalef(0.5,1.0,30.0);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-2.5,0.5,30.0);
    glScalef(35.0,1.0,0.5);
    glutSolidCube(1.0);
    glPopMatrix();
}
void desenhaArvore1(){//arvore redondinha
    glColor3f(0.6,0.3,0.0);
    glRotated(270,1,0,0);
    glutSolidCylinder(0.5,1.0,10.0,10.0);
    glRotated(-270,1,0,0);
    glTranslatef(0.0,2.0,0.0);
    glColor3f(0.0,0.7,0.0);
    glutSolidSphere(1.0,10.0,10.0);
    glTranslated(0.0,-2.0,0.0);
}
void desenhaArvore2(){//pseudo pinheiro
    glColor3f(0.4,0.3,0);
    glRotated(270,1,0,0);
    glutSolidCylinder(0.5,1.0,10.0,10.0);
    glRotated(-270,1,0,0);
    glTranslatef(0.0,1.0,0.0);
    glRotated(270,1,0,0);
    glColor3f(0.2,0.4,0.1);
    glutSolidCone(1.0,1.0,10.0,10.0);
    glRotated(-270,1,0,0);
    glTranslatef(0.0,1.0,0.0);
    glRotated(270,1,0,0);
    glutSolidCone(0.5,1.0,10.0,10.0);
    glRotated(-270,1,0,0);
    glTranslatef(0.0,-2.0,0.0);
}
void desenhaPostes(){
    glPushMatrix();
        glColor3f(0.4,0.4,0.4);

        glRotated(270,1,0,0);
        glutSolidCylinder(0.25,1.0,10.0,10.0);
        glRotated(-270,1,0,0);

        glTranslated(0.0,1.0,0.0);

        glColor3f(1.0,1.0,0.0);
        if(isDay==0){
            glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, luzPosteEmissiva);
            glutSolidSphere(0.5,10.0,10.0);
            glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);
        }else if(isDay==1){
            glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);
            glutSolidSphere(0.5,10.0,10.0);
        }
    glPopMatrix();
}

void desenhaCaminho(){
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(0.0,0.1,0.0);
    glVertex3f(-2.0,0.1,0.0);
    glVertex3f(0.0,0.1,8.0);
    glVertex3f(-2.0,0.1,8.0);
    glEnd();
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(0.0,0.1,14.0);
    glVertex3f(-2.0,0.1,14.0);
    glVertex3f(0.0,0.1,19.0);
    glVertex3f(-2.0,0.1,19.0);
    glEnd();
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(-5.0,0.1,10.0);
    glVertex3f(-8.0,0.1,10.0);
    glVertex3f(-5.0,0.1,12.0);
    glVertex3f(-8.0,0.1,12.0);
    glEnd();
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(3.0,0.1,10.0);
    glVertex3f(6.0,0.1,10.0);
    glVertex3f(3.0,0.1,12.0);
    glVertex3f(6.0,0.1,12.0);
    glEnd();
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(3.0,0.1,8.0);
    glVertex3f(1.0,0.1,10.0);
    glVertex3f(3.0,0.1,14.0);
    glVertex3f(1.0,0.1,12.0);
    glVertex3f(-5.0,0.1,14.0);
    glVertex3f(-3.0,0.1,12.0);
    glVertex3f(-5.0,0.1,8.0);
    glVertex3f(-3.0,0.1,10.0);
    glVertex3f(3.0,0.1,8.0);
    glVertex3f(1.0,0.1,10.0);
    glEnd();
}
void desenhaChao(){
    glColor3f(0.0,0.5,0.0);
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(-20.0,0.0,0.0);
    glVertex3f(15.0,0.0,0.0);
    glVertex3f(-20.0,0.0,30.0);
    glVertex3f(15.0,0.0,30.0);
    glEnd();
}
void desenhaQuiosque1(){
    glColor3f(1.0,1.0,1.0);
    glPushMatrix();
    glRotated(270,1,0,0);
    glutSolidCylinder(2,0.5,10.0,10.0);
    glRotated(-270,1,0,0);
    glColor3f(0.6,0.6,0.6);
    glTranslated(0,0.5,0);
    for(double i=0;i<=2;i+=0.5){
        glPushMatrix();
        glTranslated(1.5*cos(i*PI),0.0,1.5*sin(i*PI));
        glRotated(270,1,0,0);
        glutSolidCylinder(0.5,2,10.0,10.0);
        glPopMatrix();
    }
    glColor3f(1.0,1.0,1.0);
    glTranslated(0,2,0);
    glRotated(270,1,0,0);
    glutSolidCone(2,2,10.0,10.0);
    glRotated(-270,1,0,0);
    glPopMatrix();
}

void desenhaQuiosque2(){
    glColor3f(0.7,0.5,0.0);
    glPushMatrix();
        glPushMatrix();
            glScalef(3.0,1.0,3.0);
            glutSolidCube(1.0);
        glPopMatrix();

        glTranslated(0,0.61,0);
        glRotated(270,1,0,0);
        glutSolidCylinder(0.5,3.0,10.0,10.0);
        glRotated(-270,1,0,0);
        glTranslated(0,2,0);
        glRotated(270,1,0,0);
        glutSolidCone(2,2,10.0,10.0);
        glRotated(-270,1,0,0);
    glPopMatrix();
}
void desenhaObelisco(int rotacaoObelisco){
    glPushMatrix();
    glColor3f(0.6,0.6,0.6);
    glRotated(270,1,0,0);
    glutSolidCone(1.0,1.0,10.0,10.0);
    glRotated(-270,1,0,0);
        glPushMatrix();
        glColor3f(0.0,0.0,1.0);
        glRotated(rotacaoObelisco,0,1,0);
        glTranslated(0.0,1.0,0.0);
        glutSolidSphere(1.0,10.0,10.0);
        glPopMatrix();
    glPopMatrix();
}
void desenhaNatureza(){
    int deslocamentoX;
    int deslocamentoZ;
    int i=0;
    for(deslocamentoX=1;deslocamentoX<=6;deslocamentoX+=2){
            for(deslocamentoZ=2;deslocamentoZ<=6;deslocamentoZ+=2){
                glTranslated(deslocamentoX,0,deslocamentoZ);
                desenhaArvore1();
                glTranslated(-deslocamentoX,0,-deslocamentoZ);
            }
    }
    for(deslocamentoX=-3;deslocamentoX>=-7;deslocamentoX-=2){
            for(deslocamentoZ=2;deslocamentoZ<=6;deslocamentoZ+=2){
                glTranslated(deslocamentoX,0,deslocamentoZ);
                desenhaArvore2();
                glTranslated(-deslocamentoX,0,-deslocamentoZ);
            }
    }
    for(deslocamentoX=-9;deslocamentoX>=-17;deslocamentoX-=2){
            for(deslocamentoZ=2;deslocamentoZ<=6;deslocamentoZ+=2){
                glTranslated(deslocamentoX,0,deslocamentoZ);
                if(i%2==0){
                    desenhaArvore1();
                    i++;
                }
                else{
                    desenhaArvore2();
                    i++;
                }
                glTranslated(-deslocamentoX,0,-deslocamentoZ);
            }
            i=0;
    }
    for(deslocamentoX=8;deslocamentoX<=12;deslocamentoX+=2){
            for(deslocamentoZ=2;deslocamentoZ<=4;deslocamentoZ+=2){
                glTranslated(deslocamentoX,0,deslocamentoZ);
                desenhaArvore2();
                glTranslated(-deslocamentoX,0,-deslocamentoZ);
            }
    }
    for(deslocamentoZ=16;deslocamentoZ<=26;deslocamentoZ+=2){
            for(deslocamentoX=8;deslocamentoX<=12;deslocamentoX+=2){
                glTranslated(deslocamentoX,0,deslocamentoZ);
                if(i%2==0){
                    desenhaArvore1();
                    i++;
                }
                else{
                    desenhaArvore2();
                    i++;
                }
                glTranslated(-deslocamentoX,0,-deslocamentoZ);
            }
            i=0;
    }
    for(deslocamentoZ=14;deslocamentoZ<=28;deslocamentoZ+=2){
            for(deslocamentoX=-15;deslocamentoX>=-17;deslocamentoX-=2){
                glTranslated(deslocamentoX,0,deslocamentoZ);
                desenhaArvore2();
                glTranslated(-deslocamentoX,0,-deslocamentoZ);
            }
    }
}

void desenhaIluminacao(){
    int deslocamentoX;
    int deslocamentoZ;
    for(deslocamentoX=-1;deslocamentoX>=-1;deslocamentoX-=2){
        for(deslocamentoZ=2;deslocamentoZ<=6;deslocamentoZ+=2){
                glTranslated(deslocamentoX,0,deslocamentoZ);
                desenhaPostes();
                glTranslated(-deslocamentoX,0,-deslocamentoZ);
        }
    }
    for(deslocamentoX=-1;deslocamentoX>=-1;deslocamentoX-=2){
        for(deslocamentoZ=15;deslocamentoZ<=17;deslocamentoZ+=2){
                glTranslated(deslocamentoX,0,deslocamentoZ);
                desenhaPostes();
                glTranslated(-deslocamentoX,0,-deslocamentoZ);
        }
    }
    for(deslocamentoZ=9;deslocamentoZ<=9;deslocamentoZ+=2){
        for(deslocamentoX=-4;deslocamentoX<=2;deslocamentoX+=2){
                glTranslated(deslocamentoX,0,deslocamentoZ);
                desenhaPostes();
                glTranslated(-deslocamentoX,0,-deslocamentoZ);
        }
    }
    for(deslocamentoZ=13;deslocamentoZ<=13;deslocamentoZ+=2){
        for(deslocamentoX=-4;deslocamentoX<=2;deslocamentoX+=2){
                glTranslated(deslocamentoX,0,deslocamentoZ);
                desenhaPostes();
                glTranslated(-deslocamentoX,0,-deslocamentoZ);
        }
    }
    for(deslocamentoZ=11;deslocamentoZ<=11;deslocamentoZ+=2){
        for(deslocamentoX=2;deslocamentoX<=4;deslocamentoX+=2){
                glTranslated(deslocamentoX,0,deslocamentoZ);
                desenhaPostes();
                glTranslated(-deslocamentoX,0,-deslocamentoZ);
        }
    }
    for(deslocamentoZ=11;deslocamentoZ<=11;deslocamentoZ+=2){
        for(deslocamentoX=-4;deslocamentoX>=-6;deslocamentoX-=2){
                glTranslated(deslocamentoX,0,deslocamentoZ);
                desenhaPostes();
                glTranslated(-deslocamentoX,0,-deslocamentoZ);
        }
    }

}
void desenhaBrinquedos(){
    glPushMatrix();
    glTranslated(-1.0,0.0,22.0);
    desenhaRodaGigante(rotacaoRoda);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-12.0,0.0,11.0);
    desenhaChaleiraMaluca(rotacaoXicara);
    glPopMatrix();

    glPushMatrix();
    glTranslated(12.0,1.0,8.0);
    desenhaBarco(rotacaoBarco);
    glPopMatrix();
}

void desenhaCenario(){
    desenhaChao();
    desenhaCaminho();
    desenhaLagoa();

    glPushMatrix();
    glTranslatef(-9.0,0.1,20.0);
    desenhaQuiosque1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.0,0.1,16.0);
    desenhaQuiosque2();
    glPopMatrix();

    desenhaPortao();
    desenhaMuro();
    desenhaNatureza();
    desenhaIluminacao();

    glPushMatrix();
    glTranslated(-1,0.0,11.0);
    desenhaObelisco(rotacaoObelisco);
    glPopMatrix();
}

