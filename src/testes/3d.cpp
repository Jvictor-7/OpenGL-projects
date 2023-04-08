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

void init(); // Função de inicialização
void renderScene(); // Função de renderização da cena
void keyboard(unsigned char key, int x, int y); // Função de entrada do teclado

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
    glBegin(GL_QUADS); //  Inicia a definição de um conjunto de quadriláteros.
        //Face da frente
        glColor3f(1.0,0.0,0.0);
        glVertex3f(-10.0,10.0,10.0);
        glVertex3f(-10.0,-10.0,10.0);
        glVertex3f(10.0,-10.0,10.0);
        glVertex3f(10.0,10.0,10.0);
        //Face de trás
        glColor3f(0.0,1.0,0.0);
        glVertex3f(10.0,10.0,-10.0);
        glVertex3f(10.0,-10.0,-10.0);
        glVertex3f(-10.0,-10.0,-10.0);
        glVertex3f(-10.0,10.0,-10.0);
        //Face da direita
        glColor3f(0.0,0.0,1.0);
        glVertex3f(10.0,10.0,10.0);
        glVertex3f(10.0,-10.0,10.0);
        glVertex3f(10.0,-10.0,-10.0);
        glVertex3f(10.0,10.0,-10.0);
        //Face da esquerda
        glColor3f(1.0,1.0,0.0);
        glVertex3f(-10.0,10.0,-10.0);
        glVertex3f(-10.0,-10.0,-10.0);
        glVertex3f(-10.0,-10.0,10.0);
        glVertex3f(-10.0,10.0,10.0);
        //Face de cima
        glColor3f(0.0,1.0,1.0);
        glVertex3f(-10.0,10.0,-10.0);
        glVertex3f(-10.0,10.0,10.0);
        glVertex3f(10.0,10.0,10.0);
        glVertex3f(10.0,10.0,-10.0);
        //Face de baixo
        glColor3f(1.0,0.0,1.0);
        glVertex3f(-10.0,-10.0,-10.0);
        glVertex3f(-10.0,-10.0,10.0);
        glVertex3f(10.0,-10.0,10.0);
        glVertex3f(10.0,-10.0,-10.0);
    glEnd();

    glPopMatrix(); // Remove a matriz de transformação mais recente da pilha de matrizes de transformação do OpenGL. É importante usar essa função após desenhar um objeto com transformações aplicadas para evitar que essas transformações sejam aplicadas a outros objetos desenhados posteriormente

    glutSwapBuffers(); // Troca os buffers de vídeo utilizados para renderizar a cena
}

void keyboard(unsigned char key, int x, int y) {

    float cameraSpeed = 0.3f; // Velocidade de movimento da câmera
    float cameraRotationSpeed = 5.0f; // Velocidade de rotação da câmera

    switch (key) {
    case 'a':
    case 'A':
        cameraPosX -= cameraSpeed * cameraFrontZ;
        cameraPosZ += cameraSpeed * cameraFrontX;
        break;
    case 'd':
    case 'D':
        cameraPosX += cameraSpeed * cameraFrontZ;
        cameraPosZ -= cameraSpeed * cameraFrontX;
        break;
    case 'w':
    case 'W':
        cameraPosX += cameraSpeed * cameraFrontX;
        cameraPosZ += cameraSpeed * cameraFrontZ;
        break;
    case 's':
    case 'S':
        cameraPosX -= cameraSpeed * cameraFrontX;
        cameraPosZ -= cameraSpeed * cameraFrontZ;
        break;
    case 'q':
    case 'Q':
        cameraRotateX += cameraRotationSpeed;
        break;
    case 'e':
    case 'E':
        cameraRotateX -= cameraRotationSpeed;
        break;
    case 'c':
    case 'C':
        cameraRotateY += cameraRotationSpeed;
        if (cameraRotateY > 89.0f) {
            cameraRotateY = 89.0f;
        }
        break;
    case 'b':
    case 'B':
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
