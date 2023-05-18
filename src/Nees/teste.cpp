#include <GL/glut.h>

// Função de renderização
void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Limpa o buffer de cores e de profundidade

    // Configuração da câmera
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0f, 0.0f, 5.0f,  // Posição da câmera
              0.0f, 0.0f, 0.0f,  // Ponto para onde a câmera está olhando
              0.0f, 1.0f, 0.0f); // Vetor de orientação da câmera

    // Configuração da luz
    GLfloat lightPosition[] = {0.0f, 1.0f, 1.0f, 0.0f};  // Posição da luz
    GLfloat lightAmbient[] = {0.2f, 0.2f, 0.2f, 1.0f};   // Componente ambiente da luz
    GLfloat lightDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};   // Componente difusa da luz
    GLfloat lightSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};  // Componente especular da luz

    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Configuração dos materiais
    GLfloat matAmbient[] = {0.2f, 0.2f, 0.2f, 1.0f};    // Componente ambiente do material
    GLfloat matDiffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};    // Componente difusa do material
    GLfloat matSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};   // Componente especular do material
    GLfloat matShininess[] = {50.0f};                   // Brilho do material

    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);

    // Desenhar a geometria do abajur
    glutSolidSphere(1.0f, 20, 20);  // Exemplo: um abajur esférico

    glutSwapBuffers();  // Troca os buffers para exibir a cena na tela
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);  // Modo de exibição com buffer duplo, RGBA e profundidade
    glutInitWindowSize(800, 600);  // Define o tamanho da janela
    glutCreateWindow("Abajur em OpenGL");
    
    glEnable(GL_DEPTH_TEST);  // Habilita teste de profundidade

    glutDisplayFunc(renderScene);  // Define a função de renderização
    glutMainLoop();  // Inicia o loop principal do OpenGL

    return 0;
}