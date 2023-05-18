#include <GL/glut.h>
#include <stdio.h>
// define a taxa de FPS desejada (60 FPS)
#define DESIRED_FPS 60
#define FALSE 0
#define TRUE 1

typedef int bool;

int width = 800; //largura da janela
int height = 600; // altura da janela

bool front = FALSE;
bool back = FALSE;
bool left = FALSE;
bool right = FALSE;
bool run = FALSE;
bool portaAberta = FALSE;
bool ventiladorLigado = FALSE;

float anguloVentilador = 0.0;
float anguloPorta = 0.0;

float cameraSpeed = 0.1f; // Velocidade de movimento da câmera


float cameraPosX = -10.0f; // posição da câmera no eixo X
float cameraPosY = 0.0f; // posição da câmera no eixo Y
float cameraPosZ = 40.0f; // posição da câmera no eixo Z

float cameraFrontX = 0.0f; // direção que a câmera está apontando no eixo X
float cameraFrontY = 0.0f; // direção que a câmera está apontando no eixo Y
float cameraFrontZ = -1.0f; // direção que a câmera está apontando no eixo Z

float cameraUpX = 0.0f; // direção "para cima" da câmera no eixo X
float cameraUpY = 1.0f; // direção "para cima" da câmera no eixo Y
float cameraUpZ = 0.0f; // direção "para cima" da câmera no eixo Z

float cameraRotateX = 0.0f; // rotação horizontal da câmera
float cameraRotateY = 0.0f; // rotação vertical da câmera

float mouseRateMove = 0.5;
int positionMouseX = 0;
int positionMouseY = 0;

float comprimentoMaximo = 60.0; //Comprimeneto do lab
float larguraMaxima = -80.0; // largura do lab
//PAREDE
float espessuraParede = 1.5f;


void init(); // Função de inicialização
void renderScene(); // Função de renderização da cena


void handleKeyDown(unsigned char key, int x, int y); // Função de entrada do teclado
void handleKeyUp(unsigned char key, int x, int y); // Função de entrada do teclado

void update();

void movSpeed();
void move();

//PARTES LAB
void parede();
void chao();

//OBJETOS
//OBJETOS
void fechadura();
void porta();
void janelaEsquerda();
void janelaDireita();
void mesa();
void cadeira();
void armario();
void portaArmario();
void frigobar();
void portaFrigobar();
void ventilador();

//PARALELEPIPEDO
void paralelepipedo(float comprimento, float altura, float profundidade);
void plano();



void mouseMove(int x, int y);

int main(int argc, char** argv) {
    glutInit(&argc, argv); // Inicializa o GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // Define o modo de exibição
    glutInitWindowSize(width, height); // Define o tamanho da janela
    glutCreateWindow("Camera"); // Cria a janela

    glutDisplayFunc(renderScene); // Define a função de renderização da cena
    glutKeyboardFunc(handleKeyDown);
    glutKeyboardUpFunc(handleKeyUp);

    glutMotionFunc(mouseMove); // Define a função de callback de movimento do mouse com um botão pressionado
     // Registra a função de callback para o mouse
    glutIdleFunc(update);

    glutMainLoop(); // Entra em loop do GLUT

    return 0;
}

void init(){ // Função de inicialização
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpa o buffer de cor e o buffer de profundidade
    glEnable(GL_DEPTH_TEST); // Habilita o teste de profundidade
}

void renderScene() { // Função de renderização da cena
    init(); // Inicializa a cena
    glMatrixMode(GL_PROJECTION); // Seleciona a matriz de projeção
    glLoadIdentity(); // Carrega a matriz identidade na matriz de projeção
    gluPerspective(45.0f, (float)width / (float)height, 0.1f, 100.0f); // Define a perspectiva da cena, com um campo de visão de 45 graus, razão de aspecto (float)width / (float)height, uma distância de plano próximo de 0,1 unidades e uma distância de plano distante de 100 unidades.

    glMatrixMode(GL_MODELVIEW); // Seleciona a matriz de modelo e visão
    glLoadIdentity(); // Carrega a matriz identidade
    
    glRotatef(cameraRotateY, 1.0f, 0.0f, 0.0f); // Rotaciona a cena em relação ao eixo Y de acordo com a variável cameraRotateY
    glRotatef(cameraRotateX, 0.0f, 1.0f, 0.0f); // Rotaciona a cena em relação ao eixo X de acordo com a variável cameraRotateX
    gluLookAt(cameraPosX, cameraPosY, cameraPosZ, cameraPosX + cameraFrontX, cameraPosY + cameraFrontY, cameraPosZ + cameraFrontZ, cameraUpX, cameraUpY, cameraUpZ); // Define a posição da câmera e para onde ela está olhando.

    // Desenhe a renderScene aqui
     chao();
    parede();
    fechadura();

    glPushMatrix();
    if(portaAberta){
        glRotatef(90.0, 0.0f, 1.0f, 0.0f);
        glTranslatef(6.0f,0.0f,-25.0f);
    }
    porta();
    glPopMatrix();
    // plano();
    janelaEsquerda();
    janelaDireita();
    // CADEIRAS A DIREITA
    //cadeira 1
    cadeira();
    //cadeira 2
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 10.0f);
    cadeira();
    glPopMatrix();
    //cadeira 3
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 19.0f);
    cadeira();
    glPopMatrix();
    //cadeira 4
    glPushMatrix();
    glTranslatef(15.0f,0.0f,-30.0f);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    cadeira();
    glPopMatrix();
    //cadeira 5
    glPushMatrix();
    glTranslatef(15.0f,0.0f,-20.0f);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    cadeira();
    glPopMatrix();
    //cadeira 6
    glPushMatrix();
    glTranslatef(15.0f,0.0f,-10.0f);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    cadeira();
    glPopMatrix();
    //cadeira 7
    glPushMatrix();
    glTranslatef(26.0f,0.0f,0.0f);
    cadeira();
    glPopMatrix();
    //cadeira 8
    glPushMatrix();
    glTranslatef(26.0f, 0.0f, 10.0f);
    cadeira();
    glPopMatrix();
    //cadeira 9
    glPushMatrix();
    glTranslatef(26.0f, 0.0f, 19.0f);
    cadeira();
    glPopMatrix();
    //cadeira 10
    glPushMatrix();
    glTranslatef(15.0f+26.0f,0.0f,-30.0f);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    cadeira();
    glPopMatrix();
    //cadeira 11
    glPushMatrix();
    glTranslatef(15.0f+26.0f,0.0f,-20.0f);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    cadeira();
    glPopMatrix();
    //cadeira 12
    glPushMatrix();
    glTranslatef(15.0f +26.0f,0.0f,-10.0f);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    cadeira();
    glPopMatrix();
    //cadeira 13
    glPushMatrix();
    glTranslatef(48.0f, 0.0f, 0.0f);
    cadeira();
    glPopMatrix();
    //cadeira 14
    glPushMatrix();
    glTranslatef(48.0f, 0.0f, 10.0f);
    cadeira();
    glPopMatrix();
    //cadeira 15
    glPushMatrix();
    glTranslatef(48.0f, 0.0f, 19.0f);
    cadeira();
    glPopMatrix();
    //CADEIRAS A ESQUERDA
    //cadeira 1
    glPushMatrix();
    glTranslatef(0.0f,0.0f,-60.0f);
    cadeira();
    glPopMatrix();
    //cadeira 2
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 10.0f-60.0f);
    cadeira();
    glPopMatrix();
    //cadeira 3
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 19.0f-60.0f);
    cadeira();
    glPopMatrix();
    //cadeira 4
    glPushMatrix();
    glTranslatef(15.0f,0.0f,-30.0f-60.0f);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    cadeira();
    glPopMatrix();
    //cadeira 5
    glPushMatrix();
    glTranslatef(15.0f,0.0f,-20.0f-60.0f);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    cadeira();
    glPopMatrix();
    //cadeira 6
    glPushMatrix();
    glTranslatef(15.0f,0.0f,-10.0f-60.0f);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    cadeira();
    glPopMatrix();
    //cadeira 7
    glPushMatrix();
    glTranslatef(26.0f,0.0f,0.0f-60.0f);
    cadeira();
    glPopMatrix();
    //cadeira 8
    glPushMatrix();
    glTranslatef(26.0f, 0.0f, 10.0f-60.0f);
    cadeira();
    glPopMatrix();
    //cadeira 9
    glPushMatrix();
    glTranslatef(26.0f, 0.0f, 19.0f-60.0f);
    cadeira();
    glPopMatrix();
    //cadeira 10
    glPushMatrix();
    glTranslatef(15.0f+26.0f,0.0f,-30.0f-60.0f);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    cadeira();
    glPopMatrix();
    //cadeira 11
    glPushMatrix();
    glTranslatef(15.0f+26.0f,0.0f,-20.0f-60.0f);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    cadeira();
    glPopMatrix();
    //cadeira 12
    glPushMatrix();
    glTranslatef(15.0f +26.0f,0.0f,-10.0f-60.0f);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    cadeira();
    glPopMatrix();
    //cadeira 13
    glPushMatrix();
    glTranslatef(48.0f, 0.0f, 0.0f-60.0f);
    cadeira();
    glPopMatrix();
    //cadeira 14
    glPushMatrix();
    glTranslatef(48.0f, 0.0f, 10.0f-60.0f);
    cadeira();
    glPopMatrix();
    //cadeira 15
    glPushMatrix();
    glTranslatef(48.0f, 0.0f, 19.0f-60.0f);
    cadeira();
    glPopMatrix();
    //mesa1
    mesa();
    //mesa2
    glPushMatrix();
    glTranslatef(25.0f,0.0f,0.0f);
    mesa();
    glPopMatrix();
    //mesa3
    glPushMatrix();
    glTranslatef(0.0f,0.0f,-60.0f);
    mesa();
    glPopMatrix();
    //mesa4
    glPushMatrix();
    glTranslatef(25.0f,0.0f,-60.0f);
    mesa();
    glPopMatrix();
    //mesa5
    glPushMatrix();
    glColor3f(0.84f, 0.6f, 0.35f);
    glTranslatef(54.0f,-5.0f,-36.0);
    paralelepipedo(10.0f,1.0f,91.0f);
    glPopMatrix();
    //mesa6
    glPushMatrix();
    glColor3f(0.84f, 0.6f, 0.36f);
    glTranslatef(-15.0f,-5.0f, -62.0);
    paralelepipedo(10.0f,1.0f,36.0f);
    glPopMatrix();
    //FRIGOBAR - parte1
    glPushMatrix();
    glTranslatef(-15.0f, -2.0f, -12.0f);
    frigobar();
    portaFrigobar();
    glPopMatrix();
    //FRIGOBAR - parte2
    glPushMatrix();
    glTranslatef(-15.0f, -5.0f-2.0f, -12.0f);
    frigobar();
    portaFrigobar();
    glPopMatrix();
    //armario - parte1
    glPushMatrix();
    glTranslatef(-15.0f, -2.0f, -30.0f);
    armario();
    portaArmario();
    glPopMatrix();
    //armario - parte2
    glPushMatrix();
    glTranslatef(-15.0f, -5.0f-2.0f, -30.0f);
    armario();
    glPopMatrix();
    //armario - parte3
    glPushMatrix();
    glTranslatef(-15.0f, +5.0f-2.0f, -30.0f);
    armario();
    glPopMatrix();
    //armario - parte4
    glPushMatrix();
    glTranslatef(-15.0f, -2.0f, -35.0f);
    armario();
    portaArmario();
    glPopMatrix();
    //armario - parte5
    glPushMatrix();
    glTranslatef(-15.0f, -5.0f-2.0f, -35.0f);
    armario();
    portaArmario();
    glPopMatrix();
    //armario - parte6
    glPushMatrix();
    glTranslatef(-15.0f, +5.0f-2.0f, -35.0f);
    armario();
    portaArmario();
    glPopMatrix();
    //armario - parte7
    glPushMatrix();
    glTranslatef(-15.0f, -2.0f, -40.0f);
    armario();
    portaArmario();
    glPopMatrix();
    //armario - parte8
    glPushMatrix();
    glTranslatef(-15.0f, -5.0f-2.0f, -40.0f);
    armario();
    glPopMatrix();
    //armario - parte9
    glPushMatrix();
    glTranslatef(-15.0f, +5.0f-2.0f, -40.0f);
    armario();
    glPopMatrix();

    //ventilador 1
    glPushMatrix();
    glTranslatef(0.0f,6.0f,-40.0f);
    ventilador();
    glPopMatrix();

    //ventilador 2
    glPushMatrix();
    glTranslatef(40.0f,6.0f,-40.0f);
    ventilador();
    glPopMatrix();
    glutSwapBuffers(); // Troca os buffers de vídeo utilizados para renderizar a cena
}

//OBJETOS
void parede(){

    glPushMatrix();
    //FACE FRENTE
    //FACE ESQUERDA DA FRENTE
    glBegin(GL_QUADS);
        //face frente
        glColor3f(0.7, 0.7, 0.7);
        glVertex3f(-20.0,6.0,10.0);
        glVertex3f(-20.0,-10.0,10.0);
        glVertex3f(-16.0,-10.0,10.0);
        glVertex3f(-16.0,6.0,10.0);
        //espessura
        glVertex3f(-20.0,6.0,10.0 - espessuraParede);
        glVertex3f(-20.0,-10.0,10.0 - espessuraParede);
        glVertex3f(-16.0,-10.0,10.0 - espessuraParede);
        glVertex3f(-16.0,6.0,10.0 - espessuraParede);
        //face direita
        glVertex3f(-16.0,6.0,10.0 - espessuraParede);
        glVertex3f(-16.0,-10.0,10.0 - espessuraParede);
        glVertex3f(-16.0,-10.0,10.0);
        glVertex3f(-16.0,6.0,10.0);
        //face esquerda
        glVertex3f(-20.0,6.0,10.0 - espessuraParede);
        glVertex3f(-20.0,-10.0,10.0 - espessuraParede);
        glVertex3f(-20.0,-10.0,10.0);
        glVertex3f(-20.0,6.0,10.0);
        //face baixo
        glVertex3f(-20.0,-10.0,10.0 - espessuraParede);
        glVertex3f(-20.0,-10.0,10.0);
        glVertex3f(-16.0,-10.0,10.0);
        glVertex3f(-16.0,-10.0,10.0 - espessuraParede);
        //
        //FACE DIREITA - FRENTE
        //frente
        glColor3f(0.7,0.7,0.7);
        glVertex3f(-8.0,6.0,10.0);
        glVertex3f(-8.0,-10.0,10.0);
        glVertex3f(comprimentoMaximo,-10.0,10.0);
        glVertex3f(comprimentoMaximo,6.0,10.0);
        //expessura
        glVertex3f(-8.0,6.0,10.0 - espessuraParede);
        glVertex3f(-8.0,-10.0,10.0 - espessuraParede);
        glVertex3f(comprimentoMaximo,-10.0,10.0 - espessuraParede);
        glVertex3f(comprimentoMaximo,6.0,10.0 - espessuraParede);
        //direita
        glVertex3f(comprimentoMaximo,6.0,10.0 - espessuraParede);
        glVertex3f(comprimentoMaximo,-10.0,10.0 - espessuraParede);
        glVertex3f(comprimentoMaximo,-10.0,10.0);
        glVertex3f(comprimentoMaximo,6.0,10.0);
        //esquerda
        glVertex3f(-8.0,6.0,10.0 - espessuraParede);
        glVertex3f(-8.0,-10.0,10.0 - espessuraParede);
        glVertex3f(-8.0,-10.0,10.0);
        glVertex3f(-8.0,6.0,10.0);
        //face baixo
        glVertex3f(-8.0,-10.0,10.0 - espessuraParede);
        glVertex3f(-8.0,-10.0,10.0);
        glVertex3f(comprimentoMaximo,-10.0,10.0);
        glVertex3f(comprimentoMaximo,-10.0,10.0 - espessuraParede);
        //FACE CIMA - FRENTE
        //Face cima - frente
        glColor3f(0.7,0.7,0.7);
        glVertex3f(-20.0,10.0,10.0);
        glVertex3f(-20.0,6.0,10.0);
        glVertex3f(comprimentoMaximo,6.0,10.0);
        glVertex3f(comprimentoMaximo,10.0,10.0);
        //expessura
        glVertex3f(-20.0,10.0,10.0 - espessuraParede);
        glVertex3f(-20.0,6.0,10.0 - espessuraParede);
        glVertex3f(comprimentoMaximo,6.0,10.0 - espessuraParede);
        glVertex3f(comprimentoMaximo,10.0,10.0 - espessuraParede);
        //direita
        glVertex3f(comprimentoMaximo,10.0,10.0 - espessuraParede);
        glVertex3f(comprimentoMaximo,6.0,10.0 - espessuraParede);
        glVertex3f(comprimentoMaximo,6.0,10.0);
        glVertex3f(comprimentoMaximo,10.0,10.0);
        //esquerda
        glVertex3f(-20.0,10.0,10.0 - espessuraParede);
        glVertex3f(-20.0,6.0,10.0 - espessuraParede);
        glVertex3f(-20.0,6.0,10.0);
        glVertex3f(-20.0,10.0,10.0);
        //cima
        glVertex3f(-20.0,10.0,10.0 - espessuraParede);
        glVertex3f(-20.0,10.0,10.0);
        glVertex3f(comprimentoMaximo,10.0,10.0);
        glVertex3f(comprimentoMaximo,10.0,10.0 - espessuraParede);
        //baixo
        glVertex3f(-20.0,6.0,10.0 - espessuraParede);
        glVertex3f(-20.0,6.0,10.0);
        glVertex3f(comprimentoMaximo,6.0,10.0);
        glVertex3f(comprimentoMaximo,6.0,10.0 - espessuraParede);
        //  
        //
        // FACE DE TRÁS
        // FACE DA FRENTE - TRÁS - ESUQERDA
        glColor3f(0.7,0.7,0.7);
        glVertex3f(-20.0,10.0,larguraMaxima);
        glVertex3f(-20.0,-10.0,larguraMaxima);
        glVertex3f(-10.0,-10.0,larguraMaxima);
        glVertex3f(-10.0,10.0,larguraMaxima);
        //
        //espessura
        glVertex3f(-20.0,10.0,larguraMaxima - espessuraParede);
        glVertex3f(-20.0,-10.0,larguraMaxima - espessuraParede);
        glVertex3f(-10.0,-10.0,larguraMaxima - espessuraParede);
        glVertex3f(-10.0,10.0,larguraMaxima - espessuraParede);
        // FACE DA FRENTE - TRÁS - DIREITA
        glColor3f(0.7,0.7,0.7);
        glVertex3f(50.0,10.0,larguraMaxima);
        glVertex3f(50.0,-10.0,larguraMaxima);
        glVertex3f(60.0,-10.0,larguraMaxima);
        glVertex3f(60.0,10.0,larguraMaxima);
        //
        //espessura
        glVertex3f(50.0,10.0,larguraMaxima - espessuraParede);
        glVertex3f(50.0,-10.0,larguraMaxima - espessuraParede);
        glVertex3f(60.0,-10.0,larguraMaxima - espessuraParede);
        glVertex3f(60.0,10.0,larguraMaxima - espessuraParede);
        // FACE DA FRENTE - TRÁS - CIMA
        glColor3f(0.7,0.7,0.7);
        glVertex3f(-20.0,10.0,larguraMaxima);
        glVertex3f(-20.0,5.0,larguraMaxima);
        glVertex3f(comprimentoMaximo,5.0,larguraMaxima);
        glVertex3f(comprimentoMaximo,10.0,larguraMaxima);
        //
        //espessura
        glVertex3f(-10.0,10.0,larguraMaxima - espessuraParede);
        glVertex3f(-10.0,5.0,larguraMaxima - espessuraParede);
        glVertex3f(comprimentoMaximo,5.0,larguraMaxima - espessuraParede);
        glVertex3f(comprimentoMaximo,10.0,larguraMaxima - espessuraParede);
        // FACE DA FRENTE - TRÁS - BAIXO
        glColor3f(0.7,0.7,0.7);
        glVertex3f(-20.0,-5.0,larguraMaxima);
        glVertex3f(-20.0,-10.0,larguraMaxima);
        glVertex3f(comprimentoMaximo,-10.0,larguraMaxima);
        glVertex3f(comprimentoMaximo,-5.0,larguraMaxima);
        //
        //espessura
        glVertex3f(-20.0,-5.0,larguraMaxima - espessuraParede);
        glVertex3f(-20.0,-10.0,larguraMaxima - espessuraParede);
        glVertex3f(comprimentoMaximo,-10.0,larguraMaxima - espessuraParede);
        glVertex3f(comprimentoMaximo,-5.0,larguraMaxima - espessuraParede);
        // FACE DA FRENTE - TRÁS - MEIO
        glColor3f(0.7,0.7,0.7);
        glVertex3f(10.0,10.0,larguraMaxima);
        glVertex3f(10.0,-10.0,larguraMaxima);
        glVertex3f(30.0,-10.0,larguraMaxima);
        glVertex3f(30.0,10.0,larguraMaxima);
        //
        //espessura
        glVertex3f(10.0,10.0,larguraMaxima - espessuraParede);
        glVertex3f(10.0,-10.0,larguraMaxima - espessuraParede);
        glVertex3f(30.0,-10.0,larguraMaxima - espessuraParede);
        glVertex3f(30.0,10.0,larguraMaxima - espessuraParede);
        //face esquerda
        glVertex3f(-20.0,10.0,larguraMaxima- espessuraParede);
        glVertex3f(-20.0,-10.0,larguraMaxima - espessuraParede);
        glVertex3f(-20.0,-10.0,larguraMaxima);
        glVertex3f(-20.0,10.0,larguraMaxima);
        //face cima
        glVertex3f(-20.0,10.0,larguraMaxima - espessuraParede);
        glVertex3f(-20.0,10.0,larguraMaxima);
        glVertex3f(comprimentoMaximo,10.0,larguraMaxima);
        glVertex3f(comprimentoMaximo,10.0,larguraMaxima - espessuraParede);
        //face baixo
        glVertex3f(-20.0,-10.0,larguraMaxima - espessuraParede);
        glVertex3f(-20.0,-10.0,larguraMaxima);
        glVertex3f(comprimentoMaximo,-10.0,larguraMaxima);
        glVertex3f(comprimentoMaximo,-10.0,larguraMaxima - espessuraParede);
        //FACE DE TRAS - TRÁS - DIREITA
        glVertex3f(comprimentoMaximo,10.0,larguraMaxima- espessuraParede);
        glVertex3f(comprimentoMaximo,-10.0,larguraMaxima - espessuraParede);
        glVertex3f(comprimentoMaximo,-10.0,larguraMaxima);
        glVertex3f(comprimentoMaximo,10.0,larguraMaxima);
        // FACE DIREITA
        //frente
        glVertex3f(comprimentoMaximo,10.0,10.0);
        glVertex3f(comprimentoMaximo,-10.0,10.0);
        glVertex3f(comprimentoMaximo,-10.0,larguraMaxima);
        glVertex3f(comprimentoMaximo,10.0,larguraMaxima);
        //espessura
        glVertex3f(comprimentoMaximo - espessuraParede,10.0,10.0);
        glVertex3f(comprimentoMaximo - espessuraParede,-10.0,10.0);
        glVertex3f(comprimentoMaximo - espessuraParede,-10.0,larguraMaxima);
        glVertex3f(comprimentoMaximo - espessuraParede,10.0,larguraMaxima);
        // FACE DIREITA DENTRO
        //frente
        glVertex3f(-6.0,10.0,10.0);
        glVertex3f(-6.0,-10.0,10.0);
        glVertex3f(-6.0,-10.0,-10.0);
        glVertex3f(-6.0,10.0,-10.0);
        //espessura
        glVertex3f(-6.0 - espessuraParede,10.0,10.0);
        glVertex3f(-6.0 - espessuraParede,-10.0,10.0);
        glVertex3f(-6.0 - espessuraParede,-10.0,-10.0);
        glVertex3f(-6.0 - espessuraParede,10.0,-10.0);
        //tras
        glVertex3f(-6.0,10.0,-10.0);
        glVertex3f(-6.0 - espessuraParede,10.0,-10.0);
        glVertex3f(-6.0 - espessuraParede,-10.0,-10.0);
        glVertex3f(-6.0,-10.0,-10.0);
        // FACE ESQUERDA
        //frente
        glColor3f(0.7,0.7,0.7);
        glVertex3f(-20.0,10.0,10.0);
        glVertex3f(-20.0,-10.0,10.0);
        glVertex3f(-20.0,-10.0,larguraMaxima);
        glVertex3f(-20.0,10.0,larguraMaxima);
        //espessura
        glVertex3f(-20.0 + espessuraParede,10.0,10.0);
        glVertex3f(-20.0 + espessuraParede,-10.0,10.0);
        glVertex3f(-20.0 + espessuraParede,-10.0,larguraMaxima);
        glVertex3f(-20.0 + espessuraParede,10.0,larguraMaxima);
        //FACE DE CIMA
        //frente
        glColor3f(0.9,0.9,0.9);
        glVertex3f(-20.0,10.0,larguraMaxima);
        glVertex3f(-20.0,10.0,10.0);
        glVertex3f(comprimentoMaximo,10.0,10.0);
        glVertex3f(comprimentoMaximo,10.0,larguraMaxima);
        //espessura
        glVertex3f(-20.0,10.0 - espessuraParede,larguraMaxima);
        glVertex3f(-20.0,10.0 - espessuraParede,10.0);
        glVertex3f(comprimentoMaximo,10.0 - espessuraParede,10.0);
        glVertex3f(comprimentoMaximo,10.0 - espessuraParede,larguraMaxima);
    glEnd();
    glPopMatrix();
}

void chao(){
    glPushMatrix();
    glBegin(GL_QUADS);
        //Face de baixo
        glColor3f(0.9,0.9,0.9);
        glVertex3f(-20.0,-10.0,larguraMaxima);
        glVertex3f(-20.0,-10.0,10.0);
        glVertex3f(comprimentoMaximo,-10.0,10.0);
        glVertex3f(comprimentoMaximo,-10.0,larguraMaxima);
    glEnd();
    glPopMatrix();
};

void fechadura(){
    glPushMatrix();
        //FECHADURA
        glBegin(GL_QUADS);
            //Visor
            glColor3f(0.0,1.0,1.0);
            glVertex3f(-5.8,1.7,10.2);
            glVertex3f(-5.8,0.5,10.2);
            glVertex3f(-4.7,0.5,10.2);
            glVertex3f(-4.7,1.7,10.2);
            //frente
            glColor3f(0,0,0);
            glVertex3f(-6.0,2.0,10.2);
            glVertex3f(-6.0,-1.0,10.2);
            glVertex3f(-4.5,-1.0,10.2);
            glVertex3f(-4.5,2.0,10.2);
            //tras
            glVertex3f(-6.0,2.0,10.2 - 0.2);
            glVertex3f(-6.0,-1.0,10.2 - 0.2);
            glVertex3f(-4.5,-1.0,10.2 - 0.2);
            glVertex3f(-4.5,2.0,10.2 - 0.2);
            //direita
            glVertex3f(-4.5,2.0,10.2 - 0.2);
            glVertex3f(-4.5,-1.0,10.2 - 0.2);
            glVertex3f(-4.5,-1.0,10.2);
            glVertex3f(-4.5,2.0,10.2);
            //esquerda
            glVertex3f(-6.0,2.0,10.2 - 0.2);
            glVertex3f(-6.0,-1.0,10.2 - 0.2);
            glVertex3f(-6.0,-1.0,10.2);
            glVertex3f(-6.0,2.0,10.2);
        glEnd();
        //
        glPopMatrix();
}

void porta(){
    glPushMatrix();
    glBegin(GL_QUADS);
        glColor3f(0.6f, 0.3f, 0.1f);
        glRotatef(anguloPorta, 0.0,1.0,0.0);
        //face frente
        glVertex3f(-16.0,6.0,10.0);
        glVertex3f(-16.0,-10.0,10.0);
        glVertex3f(-8.0,-10.0,10.0);
        glVertex3f(-8.0,6.0,10.0);
        //espessura
        glVertex3f(-16.0,6.0,10.0 - 1.0);
        glVertex3f(-16.0,-10.0,10.0 - 1.0);
        glVertex3f(-8.0,-10.0,10.0 - 1.0);
        glVertex3f(-8.0,6.0,10.0 - 1.0);
        //face direita
        glVertex3f(-16.0,6.0,10.0 - 1.0);
        glVertex3f(-16.0,-10.0,10.0 - 1.0);
        glVertex3f(-16.0,-10.0,10.0);
        glVertex3f(-16.0,6.0,10.0);
        //face esquerda
        glVertex3f(-8.0,6.0,10.0 - 1.0);
        glVertex3f(-8.0,-10.0,10.0 - 1.0);
        glVertex3f(-8.0,-10.0,10.0);
        glVertex3f(-8.0,6.0,10.0);
        //face baixo
        glVertex3f(-8.0,-10.0,10.0 - 1.0);
        glVertex3f(-8.0,-10.0,10.0);
        glVertex3f(-16.0,-10.0,10.0);
        glVertex3f(-16.0,-10.0,10.0 - 1.0);
        //
    glEnd();
    glPopMatrix();

}

void janelaEsquerda(){
    glPushMatrix();
    glBegin(GL_QUADS);
        //bordas brancas - frente
        glColor3f(1.0,1.0,1.0);
        glVertex3f(-10.0,5.0,larguraMaxima);
        glVertex3f(-10.0,-5.0,larguraMaxima);
        glVertex3f(10.0,-5.0,larguraMaxima);
        glVertex3f(10.0,5.0,larguraMaxima);
        //bordas brancas - espessura
        glColor3f(1.0,1.0,1.0);
        glVertex3f(-10.0,5.0,larguraMaxima - espessuraParede);
        glVertex3f(-10.0,-5.0,larguraMaxima - espessuraParede);
        glVertex3f(10.0,-5.0,larguraMaxima - espessuraParede);
        glVertex3f(10.0,5.0,larguraMaxima - espessuraParede);
        //bordas brancas - direita
        glColor3f(1.0,1.0,1.0);
        glVertex3f(10.0,5.0,larguraMaxima - espessuraParede);
        glVertex3f(10.0,-5.0,larguraMaxima - espessuraParede);
        glVertex3f(10.0,-5.0,larguraMaxima);
        glVertex3f(10.0,5.0,larguraMaxima);
        //bordas brancas - esquerda
        glColor3f(1.0,1.0,1.0);
        glVertex3f(-10.0,5.0,larguraMaxima - espessuraParede);
        glVertex3f(-10.0,-5.0,larguraMaxima - espessuraParede);
        glVertex3f(-10.0,-5.0,larguraMaxima);
        glVertex3f(-10.0,5.0,larguraMaxima);
        //espelho
        glColor3f(.0,1.0,1.0);
        glVertex3f(-10.0+0.5,5.0-0.5,larguraMaxima+0.01);
        glVertex3f(-10.0+0.5,-5.0+0.5,larguraMaxima+0.01);
        glVertex3f(10.0-0.5,-5.0+0.5,larguraMaxima+0.01);
        glVertex3f(10.0-0.5,5.0-0.5,larguraMaxima+0.01);
        //espelho
        glColor3f(.0,1.0,1.0);
        glVertex3f(-10.0+0.5,5.0-0.5,larguraMaxima-0.01 - espessuraParede);
        glVertex3f(-10.0+0.5,-5.0+0.5,larguraMaxima-0.01 - espessuraParede);
        glVertex3f(10.0-0.5,-5.0+0.5,larguraMaxima-0.01 - espessuraParede);
        glVertex3f(10.0-0.5,5.0-0.5,larguraMaxima-0.01 - espessuraParede);
    glEnd();
    glPopMatrix();
}
void janelaDireita(){
    glPushMatrix();
    glBegin(GL_QUADS);
        //bordas brancas - frente
        glColor3f(1.0,1.0,1.0);
        glVertex3f(30.0,5.0,larguraMaxima);
        glVertex3f(30.0,-5.0,larguraMaxima);
        glVertex3f(50.0,-5.0,larguraMaxima);
        glVertex3f(50.0,5.0,larguraMaxima);
        //bordas brancas - espessura
        glColor3f(1.0,1.0,1.0);
        glVertex3f(30.0,5.0,larguraMaxima - espessuraParede);
        glVertex3f(30.0,-5.0,larguraMaxima - espessuraParede);
        glVertex3f(50.0,-5.0,larguraMaxima - espessuraParede);
        glVertex3f(50.0,5.0,larguraMaxima - espessuraParede);
        //bordas brancas - direita
        glColor3f(1.0,1.0,1.0);
        glVertex3f(50.0,5.0,larguraMaxima - espessuraParede);
        glVertex3f(50.0,-5.0,larguraMaxima - espessuraParede);
        glVertex3f(50.0,-5.0,larguraMaxima);
        glVertex3f(50.0,5.0,larguraMaxima);
        //bordas brancas - esquerda
        glColor3f(1.0,1.0,1.0);
        glVertex3f(30.0,5.0,larguraMaxima - espessuraParede);
        glVertex3f(30.0,-5.0,larguraMaxima - espessuraParede);
        glVertex3f(30.0,-5.0,larguraMaxima);
        glVertex3f(30.0,5.0,larguraMaxima);
        //espelho
        glColor3f(.0,1.0,1.0);
        glVertex3f(30.0+0.5,5.0-0.5,larguraMaxima+0.01);
        glVertex3f(30.0+0.5,-5.0+0.5,larguraMaxima+0.01);
        glVertex3f(50.0-0.5,-5.0+0.5,larguraMaxima+0.01);
        glVertex3f(50.0-0.5,5.0-0.5,larguraMaxima+0.01);
        //espelho
        glColor3f(.0,1.0,1.0);
        glVertex3f(30.0+0.5,5.0-0.5,larguraMaxima-0.01 - espessuraParede);
        glVertex3f(30.0+0.5,-5.0+0.5,larguraMaxima-0.01 - espessuraParede);
        glVertex3f(50.0-0.5,-5.0+0.5,larguraMaxima-0.01 - espessuraParede);
        glVertex3f(50.0-0.5,5.0-0.5,larguraMaxima-0.01 - espessuraParede);
    glEnd();
    glPopMatrix();
}

void paralelepipedo(float comprimento, float altura, float profundidade) {
    float c = comprimento/2.0;
    float a = altura/2.0;
    float p = profundidade/2.0;

    glBegin(GL_QUADS);

    // Face frontal
    glVertex3f(-c, -a, p);
    glVertex3f(c, -a, p);
    glVertex3f(c, a, p);
    glVertex3f(-c, a, p);

    // Face traseira
    glVertex3f(-c, -a, -p);
    glVertex3f(-c, a, -p);
    glVertex3f(c, a, -p);
    glVertex3f(c, -a, -p);

    // Face lateral esquerda
    glVertex3f(-c, -a, p);
    glVertex3f(-c, a, p);
    glVertex3f(-c, a, -p);
    glVertex3f(-c, -a, -p);

    // Face lateral direita
    glVertex3f(c, -a, p);
    glVertex3f(c, -a, -p);
    glVertex3f(c, a, -p);
    glVertex3f(c, a, p);

    // Face superior
    glVertex3f(-c, a, p);
    glVertex3f(c, a, p);
    glVertex3f(c, a, -p);
    glVertex3f(-c, a, -p);

    // Face inferior
    glVertex3f(-c, -a, p);
    glVertex3f(-c, -a, -p);
    glVertex3f(c, -a, -p);
    glVertex3f(c, -a, p);

    glEnd();
}

void mesa(){
    //mesas
    glPushMatrix();
    glColor3f(0.84f, 0.6f, 0.35f);
    glTranslatef(5.0f,-5.0f,-6.0);
    paralelepipedo(5.0f,1.0f,30.0f);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.84f, 0.6f, 0.35f);
    glTranslatef(8.0f,-5.0f,-6.0);
    paralelepipedo(1.0f,10.0f,30.0f);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.84f, 0.6f, 0.35f);
    glTranslatef(11.0f,-5.0f,-6.0);
    paralelepipedo(5.0f,1.0f,30.0f);
    glPopMatrix();
}

void cadeira(){
    glPushMatrix();
    glColor3f(0.2f, 0.2f, 0.2f);
    glTranslatef(2.0f,-8.0f,-14.0);
    paralelepipedo(5.0f,5.0f,5.0f);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0f,-4.0f,-14.0);
    paralelepipedo(1.0f,4.0f,5.0f);
    glPopMatrix();
}

void armario(){
    // FACE ESQUERDA
    glPushMatrix();
    glScalef(5.0,5.0,5.0);
    glRotatef(-90.0f,0.0f,1.0f,0.0f);
    // Desenha a face frontal do cubo

    // Desenha a face superior do cubo
    glBegin(GL_QUADS);
    glColor3f(0.8,0.8,0.8);
    glVertex3f(-0.5, 0.5, -0.5); // Vértice 1
    glVertex3f(0.5, 0.5, -0.5); // Vértice 2
    glVertex3f(0.5, 0.5, 0.5); // Vértice 3
    glVertex3f(-0.5, 0.5,0.5); // Vértice 4
    glEnd();

    // Desenha a face traseira do cubo
    glBegin(GL_QUADS);
    glColor3f(0.6,0.6,0.6);
    glVertex3f(-0.5, -0.5, 0.5); // Vértice 1
    glVertex3f(0.5, -0.5, 0.5); // Vértice 2
    glVertex3f(0.5, 0.5, 0.5); // Vértice 3
    glVertex3f(-0.5, 0.5, 0.5); // Vértice 4
    glEnd();

    // Desenha a face esquerda do cubo
    glBegin(GL_QUADS);
    glColor3f(0.8,0.8,0.8);
    glVertex3f(-0.5, -0.5, -0.5); // Vértice 1
    glVertex3f(-0.5, -0.5, 0.5); // Vértice 2
    glVertex3f(-0.5, 0.5, 0.5); // Vértice 3
    glVertex3f(-0.5, 0.5, -0.5); // Vértice 4
    glEnd();

    // Desenha a face direita do cubo
    glBegin(GL_QUADS);
    glColor3f(0.8,0.8,0.8);
    glVertex3f(0.5, -0.5, -0.5); // Vértice 1
    glVertex3f(0.5, -0.5, 0.5); // Vértice 2
    glVertex3f(0.5, 0.5, 0.5); // Vértice 3
    glVertex3f(0.5, 0.5, -0.5); // Vértice 4
    glEnd();

    // Desenha a face inferior do cubo
    glBegin(GL_QUADS);
    glColor3f(0.8,0.8,0.8);
    glVertex3f(-0.5, -0.5, -0.5); // Vértice 1
    glVertex3f(0.5, -0.5, -0.5); // Vértice 2
    glVertex3f(0.5, -0.5, 0.5); // Vértice 3
    glVertex3f(-0.5, -0.5, 0.5); // Vértice 4
    glEnd();

    glPopMatrix();
}

void portaArmario(){
    glPushMatrix();
    glScalef(5.0,5.0,5.0);
    glRotatef(-90.0f,0.0f,1.0f,0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.95,0.95,0.95);
    glVertex3f(-0.5, -0.5, -0.5); // Vértice 1
    glVertex3f(0.5, -0.5, -0.5); // Vértice 2
    glVertex3f(0.5, 0.5, -0.5); // Vértice 3
    glVertex3f(-0.5, 0.5, -0.5); // Vértice 4
    glEnd();
    glPopMatrix();
}
void frigobar(){
    // FACE ESQUERDA
    glPushMatrix();
    glScalef(5.0,5.0,5.0);
    glRotatef(-90.0f,0.0f,1.0f,0.0f);
    // Desenha a face frontal do cubo

    // Desenha a face superior do cubo
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.0, 0.0);
    glVertex3f(-0.5, 0.5, -0.5); // Vértice 1
    glVertex3f(0.5, 0.5, -0.5); // Vértice 2
    glVertex3f(0.5, 0.5, 0.5); // Vértice 3
    glVertex3f(-0.5, 0.5,0.5); // Vértice 4
    glEnd();

    // Desenha a face traseira do cubo
    glBegin(GL_QUADS);
    glColor3f(0.2, 0.0, 0.0);
    glVertex3f(-0.5, -0.5, 0.5); // Vértice 1
    glVertex3f(0.5, -0.5, 0.5); // Vértice 2
    glVertex3f(0.5, 0.5, 0.5); // Vértice 3
    glVertex3f(-0.5, 0.5, 0.5); // Vértice 4
    glEnd();

    // Desenha a face esquerda do cubo
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.0, 0.0);
    glVertex3f(-0.5, -0.5, -0.5); // Vértice 1
    glVertex3f(-0.5, -0.5, 0.5); // Vértice 2
    glVertex3f(-0.5, 0.5, 0.5); // Vértice 3
    glVertex3f(-0.5, 0.5, -0.5); // Vértice 4
    glEnd();

    // Desenha a face direita do cubo
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.0, 0.0);
    glVertex3f(0.5, -0.5, -0.5); // Vértice 1
    glVertex3f(0.5, -0.5, 0.5); // Vértice 2
    glVertex3f(0.5, 0.5, 0.5); // Vértice 3
    glVertex3f(0.5, 0.5, -0.5); // Vértice 4
    glEnd();

    // Desenha a face inferior do cubo
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.0, 0.0);
    glVertex3f(-0.5, -0.5, -0.5); // Vértice 1
    glVertex3f(0.5, -0.5, -0.5); // Vértice 2
    glVertex3f(0.5, -0.5, 0.5); // Vértice 3
    glVertex3f(-0.5, -0.5, 0.5); // Vértice 4
    glEnd();

    glPopMatrix();
}

void portaFrigobar(){
    glPushMatrix();
    glScalef(5.0,5.0,5.0);
    glRotatef(-90.0f,0.0f,1.0f,0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.6,0.1,0.1);
    glVertex3f(-0.5, -0.5, -0.5); // Vértice 1
    glVertex3f(0.5, -0.5, -0.5); // Vértice 2
    glVertex3f(0.5, 0.5, -0.5); // Vértice 3
    glVertex3f(-0.5, 0.5, -0.5); // Vértice 4
    glEnd();
    glPopMatrix();
}

void ventilador(){
    glPushMatrix();
    glColor3f(0.4, 0.2, 0.0);
    glRotatef(anguloVentilador, 0.0, 1.0, 0.0);
    paralelepipedo(2.0f,0.5f,12.0f);
    paralelepipedo(12.0f,0.5f,2.0f);
    glPushMatrix();
    glPopMatrix();

    glTranslatef(0.0f,2.0f,0.0f);
    paralelepipedo(0.2f,4.0f,0.2f);
    glPopMatrix();
}

void handleKeyDown(unsigned char key, int x, int y) {
    if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) {
        run = TRUE;
    } 
    if (key == 'w' || key == 'W'){
        front = TRUE;
    }
    if(key == 's' || key == 'S'){
        back = TRUE;
    }
    if(key == 'd' || key == 'D'){
        right = TRUE;
    }
    if(key == 'a' || key == 'A'){
        left = TRUE;
    }
    if(key == 'f' || key == 'F'){
        if(portaAberta){
            portaAberta = FALSE;
        }
        else{
            portaAberta = TRUE;
        }
    }
    if(key == 'c' || key == 'C'){
        if(ventiladorLigado){
            ventiladorLigado = FALSE;
        }
        else{
            ventiladorLigado = TRUE;
        }
    }
}

void handleKeyUp(unsigned char key, int x, int y) {
    if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) {
        run = FALSE;
    } 
    if(key == 'w' || key == 'W'){
        front = FALSE;
    }
    if(key == 's' || key == 'S'){
        back = FALSE;
    }
    if(key == 'd' || key == 'D'){
        right = FALSE;
    }
    if(key == 'a' || key == 'A'){
        left = FALSE;
    }
}

void update(){
    move();
    movSpeed();
    
    if(ventiladorLigado){
        anguloVentilador+=10.0;
        if(anguloVentilador == 360){
            anguloVentilador =0;
        }
    }

    glutPostRedisplay(); 
}
void movSpeed(){
    if(run){
        cameraSpeed = 0.4f; // Velocidade de movimento da câmera
    }
    else{
        cameraSpeed = 0.1f; // Velocidade de movimento da câmera
    }
}
void move() {
    
    if(front){
        cameraPosX += cameraSpeed * cameraFrontX;
        cameraPosZ += cameraSpeed * cameraFrontZ;
    }
    if(back){
        cameraPosX -= cameraSpeed * cameraFrontX;
        cameraPosZ -= cameraSpeed * cameraFrontZ;
    }
    if(right){
        cameraPosX -= cameraSpeed * cameraFrontZ;
        cameraPosZ += cameraSpeed * cameraFrontX;
    }
    if(left){
        cameraPosX += cameraSpeed * cameraFrontZ;
        cameraPosZ -= cameraSpeed * cameraFrontX;
    }
}
void mouseMove(int x, int y)
{
    
    if(x < positionMouseX){
        cameraRotateX += mouseRateMove;
    }
    else if(x > positionMouseX){
        cameraRotateX -= mouseRateMove;
    }
    else if(height - y < positionMouseY){
        cameraRotateY -= mouseRateMove;
    }
    else if(height - y > positionMouseY){
        cameraRotateY += mouseRateMove;
    }

    positionMouseX = x;
    positionMouseY = height - y;
}