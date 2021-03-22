Trabalho Pratico II de Computação Grafica (2019.2) 
Prof. Flavio Coutinho
Eng. Comp.
CEFET_MG

alunos[] = {Francisco_Abreu, Marco_Tulio};

PROJETO FINAL DEMONSTRADO: https://youtu.be/zn-EwlQP-ZI

Se o Code Blocks disser que o projeto não exista, abra o Code Blocks e abra um novo projeto existente selecionando esse(Tp2.cbp) como o ja existente.
Por mais que o codigo esteja em C++ não há implementações a mais alem das conhecidas em C.

O programa foi dividido em 3 arquivos:
 - (3) para desenho de brinquedos especificos (barco,chaleira,rodaGigante)
 - (1) arquivo geral que inclui os anteriores.
 - (1) gerenciador de controles do mouse/teclado
 - (1) atualizador das variaveis responsaveis pelo ciclo dia e noite

 - (1) main

Os controles são:
 - 1 (teclado) para camera que faz um  360 ao redor do mapa; A e D para se locomover
 - 2           cameras do posto de vista de um visitante que acabou de entrar no parque; A e D para alternar entre as 3 cameras disponiveis
 - 3           camera em primeira pessoa; (W, A, S, D) navegam no plano xz  e (R, F) aumenta a altura em relacao xz e mouse controla o vetor do olhar
 - 4           modo esferico, invert-se algumas propiedades do lookAt para o efeito; mesmos controles da camera em primeira pessoa
 - 5           uma camera posicionada acima da bola azul que gira (obelisco) e tem visão direcionada apenas para os brinquedos; A e D para alternar entre as 3 cameras disponiveis
 - k           ativa o FOG
 - l           ativa as luzes

(Se o capslock estiver ligado elas nao funcionarão no case)

O ciclo dia e noite passa automaticamente, para alterar sua duração veja os comentarios do arquivo ControleDia

O nome da Janela condiz com o tema do parque, o que configura porcentagens extras :v (criatividade ?)
