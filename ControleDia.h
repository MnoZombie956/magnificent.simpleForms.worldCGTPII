GLfloat mShininess[] = {10}; //set the shininess of the material
GLfloat luzSol[] = {(float)252/256,(float)212/256,(float)64/256,1 };
GLfloat luzPosteEmissiva[] = { 0.9, 0.9, 0, 1 };// {255/255, 241/255, 224/255};
GLfloat phisol; //para variacao da cor do sol

GLfloat white[] = {1.0, 1.0, 1.0};
GLfloat black[] = {0,0,0};

void dayLightCycle(int ue){
    /*
        Com o passar das horas os objetos mudam(amarelado) a forma que refletem a luz (shininess) e luz varia sua intensidade
        tendo seu valor maximo amarelado como no dia e um multiplo pequeno desse valor para a noite

        alem da luz e do material, a luz de brackbround é mudada de um azul bebe para o dia para uma preto a noite

        perceba que a emissividade dos postes só é ligada na parte da "noite"
    */

    phisol+=0.001;//aumente para diminuar a duracao dos dias

    if(phisol>=2*PI){
        phisol=0;
    }
    if((phisol>=0.5235 && phisol <= 2.6179)||(5.7595 >= phisol && phisol >= 3.6651)){//condicao de dia no circ trig.
        isDay=1;
    }else{
        isDay=0;
    }
    glClearColor(//modifica(atualiza) o azul do fundo
        0,
         fabs(sin(phisol))*0.5,
         fabs(sin(phisol))*1.0,
        1.0
    );//azul bebe do fundao

    //luz do sol amarelada

    luzSol[0] = (GLfloat)((GLfloat)252/256 * (GLfloat)fabs(sin(phisol)) );
    luzSol[1] = (GLfloat)((GLfloat)212/256 * (GLfloat)fabs(sin(phisol)) );
    luzSol[2] = (GLfloat)((GLfloat) 64/256 * (GLfloat)fabs(sin(phisol)) );

    glLightfv(GL_LIGHT0, GL_AMBIENT, luzSol);//atualiza a luz do sol
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzSol);

    mShininess[0] = (GLfloat)20 - ( (GLfloat)15 * (GLfloat)cos(phisol) );//modifica a cor dos materiais
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mShininess);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, luzSol);

    glutTimerFunc(1000/60,dayLightCycle,0);
}
