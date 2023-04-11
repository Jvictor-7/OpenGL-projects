#include <GL/glut.h>

int width = 800; //largura da janela
int height = 600; // altura da janela

float cameraPosX = 0.0f; // posição da câmera no eixo X
float cameraPosY = 0.0f; // posição da câmera no eixo Y
float cameraPosZ = 3.0f; // posição da câmera no eixo Z

float cameraFrontX = 0.0f; // direção que a câmera está apontando no eixo X
float cameraFrontY = 0.0f; // direção que a câmera está apontando no eixo Y
float cameraFrontZ = -1.0f; // direção que a câmera está apontando no eixo Z

float cameraUpX = 0.0f; // direção "para cima" da câmera no eixo X
float cameraUpY = 1.0f; // direção "para cima" da câmera no eixo Y
float cameraUpZ = 0.0f; // direção "para cima" da câmera no eixo Z

float cameraRotateX = 0.0f; // rotação horizontal da câmera
float cameraRotateY = 0.0f; // rotação vertical da câmera

float comprimentoMaximo = 60.0; //Comprimeneto do lab
float larguraMaxima = -80.0; // largura do lab
//PAREDE
float espessuraParede = 1.5f;

void init(); // Função de inicialização
void renderScene(); // Função de renderização da cena
void keyboard(unsigned char key, int x, int y); // Função de entrada do teclado

//PARTES LAB
void parede();
void chao();

//OBJETOS
void fechadura();
void porta();
void janelaEsquerda();
void janelaDireita();
void mesa();
void cadeira();

//PARALELEPIPEDO
void paralelepipedo(float comprimento, float altura, float profundidade);

int main(int argc, char** argv) {
    glutInit(&argc, argv); // Inicializa o GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // Define o modo de exibição
    glutInitWindowSize(width, height); // Define o tamanho da janela
    glutCreateWindow("Camera"); // Cria a janela

    glutDisplayFunc(renderScene); // Define a função de renderização da cena
    glutKeyboardFunc(keyboard); // Define a função de entrada do teclado

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
    // Desenhe um cubo colorido

    chao();
    parede();
    fechadura();
    porta();
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

    glutSwapBuffers(); // Troca os buffers de vídeo utilizados para renderizar a cena
}

void keyboard(unsigned char key, int x, int y) {

    float cameraSpeed = 1.0f; // Velocidade de movimento da câmera
    float cameraRotationSpeed = 5.0f; // Velocidade de rotação da câmera

    switch (key) {
    // Aperte d ou D, para movimentar a camera para direita
    case 'd':
    case 'D':
        cameraPosX -= cameraSpeed * cameraFrontZ;
        cameraPosZ += cameraSpeed * cameraFrontX;
        break;
    // Aperte a ou A, para movimentar a camera para esquerda
    case 'a':
    case 'A':
        cameraPosX += cameraSpeed * cameraFrontZ;
        cameraPosZ -= cameraSpeed * cameraFrontX;
        break;
    // Aperte w ou W, para movimentar a camera para frente
    case 'w':
    case 'W':
        cameraPosX += cameraSpeed * cameraFrontX;
        cameraPosZ += cameraSpeed * cameraFrontZ;
        break;
    // Aperte s ou S, para movimentar a camera para trás
    case 's':
    case 'S':
        cameraPosX -= cameraSpeed * cameraFrontX;
        cameraPosZ -= cameraSpeed * cameraFrontZ;
        break;
    // Aperte q ou Q, para rotacionar a câmera para a esquerda
    case 'e':
    case 'E':
        cameraRotateX += cameraRotationSpeed;
        break;
    // Aperte e ou E, para rotacionar a câmera para a direita
    case 'q':
    case 'Q':
        cameraRotateX -= cameraRotationSpeed;
        break;
    // Aperte b ou B, para rotacionar a câmera para a baixo
    case 'b':
    case 'B':
        cameraRotateY += cameraRotationSpeed;
        if (cameraRotateY > 89.0f) {
            cameraRotateY = 89.0f;
        }
        break;
    // Aperte c ou C, para rotacionar a câmera para a cima
    case 'c':
    case 'C':
        cameraRotateY -= cameraRotationSpeed;
        if (cameraRotateY < -89.0f) {
            cameraRotateY = -89.0f;
        }
        break;
    case 27:
        exit(0);
        break;
    }
    glutPostRedisplay(); 

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