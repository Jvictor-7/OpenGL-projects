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

float comprimentoMaximo = 30.0; //Comprimeneto do lab
float larguraMaxima = -30.0; // largura do lab

void init(); // Função de inicialização
void renderScene(); // Função de renderização da cena
void keyboard(unsigned char key, int x, int y); // Função de entrada do teclado

//PARTES LAB
void parede();
void chao();

//OBJETOS
void fechadura();
void porta();

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
    glPushMatrix(); // Salva a matriz atual na pilha de matrizes.
    glTranslatef(0.0f, 0.0f, -5.0f); // Transla a cena para a posição (-5, 0, 0).

    chao();
    parede();
    fechadura();
    porta();

    glBegin(GL_QUADS); //  Inicia a definição de um conjunto de quadriláteros.

    glEnd();

    glPopMatrix(); // Remove a matriz de transformação mais recente da pilha de matrizes de transformação do OpenGL. É importante usar essa função após desenhar um objeto com transformações aplicadas para evitar que essas transformações sejam aplicadas a outros objetos desenhados posteriormente

    glutSwapBuffers(); // Troca os buffers de vídeo utilizados para renderizar a cena
}

void keyboard(unsigned char key, int x, int y) {

    float cameraSpeed = 0.3f; // Velocidade de movimento da câmera
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
    //PAREDE
    float espessuraParede = 1.5f;

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
        //FACE DE TRÁS
        //FACE DA FRENTE - TRÁS
        glColor3f(0.7,0.7,0.7);
        glVertex3f(-20.0,10.0,larguraMaxima);
        glVertex3f(-20.0,-10.0,larguraMaxima);
        glVertex3f(comprimentoMaximo,-10.0,larguraMaxima);
        glVertex3f(comprimentoMaximo,10.0,larguraMaxima);
        //
        //espessura
        glVertex3f(-20.0,10.0,larguraMaxima - espessuraParede);
        glVertex3f(-20.0,-10.0,larguraMaxima - espessuraParede);
        glVertex3f(comprimentoMaximo,-10.0,larguraMaxima - espessuraParede);
        glVertex3f(comprimentoMaximo,10.0,larguraMaxima - espessuraParede);
        //face direita
        glVertex3f(comprimentoMaximo,10.0,larguraMaxima - espessuraParede);
        glVertex3f(comprimentoMaximo,-10.0,larguraMaxima - espessuraParede);
        glVertex3f(comprimentoMaximo,-10.0,larguraMaxima);
        glVertex3f(comprimentoMaximo,10.0,larguraMaxima);
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
        //
        // FACE DIREITA
        //frente
        glColor3f(0.7,0.7,0.7);
        glVertex3f(comprimentoMaximo,10.0,10.0);
        glVertex3f(comprimentoMaximo,-10.0,10.0);
        glVertex3f(comprimentoMaximo,-10.0,larguraMaxima);
        glVertex3f(comprimentoMaximo,10.0,larguraMaxima);
        //espessura
        glVertex3f(comprimentoMaximo - espessuraParede,10.0,10.0);
        glVertex3f(comprimentoMaximo - espessuraParede,-10.0,10.0);
        glVertex3f(comprimentoMaximo - espessuraParede,-10.0,larguraMaxima);
        glVertex3f(comprimentoMaximo - espessuraParede,10.0,larguraMaxima);
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
        glColor3f(0.0,1.0,0.0);
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
}

void chao(){
    glBegin(GL_QUADS);
        //Face de baixo
        glColor3f(0.0,1.0,1.0);
        glVertex3f(-20.0,-10.0,larguraMaxima);
        glVertex3f(-20.0,-10.0,10.0);
        glVertex3f(comprimentoMaximo,-10.0,10.0);
        glVertex3f(comprimentoMaximo,-10.0,larguraMaxima);
    glEnd();
};

void fechadura(){
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
}

void porta(){
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

}