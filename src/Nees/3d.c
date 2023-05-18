#include <GL/glut.h>
#include <stdio.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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
bool abajuresLigado = FALSE;
bool lampadasLigado = FALSE;
bool janelaAberta = FALSE;

float anguloVentilador = 0.0;
float posicaoJanelaEsquerda = 0.0;
float posicaoJanelaDireita = 0.0;
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

//TEXTURAS
GLuint texID[5];


void init(); // Função de inicialização
void renderScene(); // Função de renderização da cena
void setup_lighting();


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
void abajur();

//PARALELEPIPEDO
void paralelepipedo(float comprimento, float altura, float profundidade);
void plano();



void mouseMove(int x, int y);

void carregaTextura(GLuint tex_id, const char* filePath) {
    // Variáveis para armazenar os dados da imagem
    unsigned char* imgData;
    int largura, altura, canais;

    // Carrega a imagem usando a biblioteca STB Image
    imgData = stbi_load(filePath, &largura, &altura, &canais, 4);

    if (imgData) {
        // Vincula a textura atual para configuração
        glBindTexture(GL_TEXTURE_2D, tex_id);

        // Define os parâmetros da textura e envia os dados da imagem para o OpenGL
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, largura, altura, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgData);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Define o comportamento de repetição da textura nos eixos S e T
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);

        // Libera a memória alocada para os dados da imagem
        stbi_image_free(imgData);
    } else {
        // Imprime uma mensagem de erro se a imagem não pôde ser carregada
        printf("Erro ao carregar a textura: %s\n", stbi_failure_reason());
        return;
    }
}

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

    glDisable(GL_TEXTURE_2D);
    glDeleteTextures(5, texID);

    return 0;
}

void setup_lighting(){
    glEnable(GL_LIGHTING); // HABILITA A ILUMINAÇÃO
    if(abajuresLigado){
        glEnable(GL_LIGHT0); // HABILITA A LUZ 0
        glEnable(GL_LIGHT1); // HABILITA A LUZ 1
        glEnable(GL_LIGHT2); // HABILITA A LUZ 2
    } else {
        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHT1);
        glDisable(GL_LIGHT2);
    }
    if(lampadasLigado){
        glEnable(GL_LIGHT3); // HABILITA A LUZ 3
        glEnable(GL_LIGHT4); // HABILITA A LUZ 4
        glEnable(GL_LIGHT5); // HABILITA A LUZ 5
        glEnable(GL_LIGHT6); // HABILITA A LUZ 6

    } else {
        glDisable(GL_LIGHT3);
        glDisable(GL_LIGHT4);
        glDisable(GL_LIGHT5);
        glDisable(GL_LIGHT6);
    }
    glEnable(GL_COLOR_MATERIAL); // Habilita a cor de material
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);


    float light_ambient[] = { 0.2f, 0.2f, 0.2f}; // Inicialmente vale 0.2f, 0.2f, 0.2f
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);

    // float light_diffuse[] = { 0.2f, 0.2f, 0.2f }; // luz branca
    // glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

    // float light_specular[] = { 0.2f, 0.2f, 0.2f }; // luz branca
    // glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    // LUZ DA PRIMEIRA LUMINARIA
    float light_position[] = { 6.5f,-1.0f,-5.0f, 1.0 };
    float spot_direction[] = { -1.f, -4.0f, -1.0f };
    float spot_cutoff[] = { 30.0f };
    float spot_diffuse[] = { 1.0f, 1.0f, 0.0f };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, spot_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, spot_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
    glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, spot_cutoff);
    // LUZ DA SEGUNDA LUMINARIA
    float light1_position[] = { 6.5f + 25.0f,0.0f,- 60.0f, 1.0 };
    float spot1_direction[] = { -1.f,-4.0f, -1.0f};
    float spot1_cutoff[] = { 45.0f };
    float spot1_diffuse[] = { 1.0f, 1.0f, 0.0f };
    glLightfv(GL_LIGHT1, GL_DIFFUSE, spot1_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, spot1_diffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot1_direction);
    glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, spot1_cutoff);
    // LUZ DA TERCEIRA LUMINARIA
    float light2_position[] = { 56.0f,-0.0f,-35.0f, 1.0 };
    float spot2_direction[] = { -1.f,-4.0f, -1.0f};
    float spot2_cutoff[] = { 45.0f };
    float spot2_diffuse[] = { 1.0f, 1.0f, 0.0f };
    glLightfv(GL_LIGHT2, GL_DIFFUSE, spot2_diffuse);
    glLightfv(GL_LIGHT2, GL_SPECULAR, spot2_diffuse);
    glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot2_direction);
    glLightfv(GL_LIGHT2, GL_SPOT_CUTOFF, spot2_cutoff);
    // LUZ DO TETO 1
    float light3_position[] = { 10.0f,10.0f,-20.0f, 1.0 };
    float spot3_direction[] = { -1.f,-4.0f, -1.0f};
    float spot3_cutoff[] = { 80.0f };
    float spot3_diffuse[] = { 1.0f, 1.0f, 1.0f };
    glLightfv(GL_LIGHT3, GL_DIFFUSE, spot3_diffuse);
    glLightfv(GL_LIGHT3, GL_SPECULAR, spot3_diffuse);
    glLightfv(GL_LIGHT3, GL_POSITION, light3_position);
    glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spot3_direction);
    glLightfv(GL_LIGHT3, GL_SPOT_CUTOFF, spot3_cutoff);
    // LUZ DO TETO 2
    float light4_position[] = { 10.0f,10.0f,-60.0f, 1.0 };
    float spot4_direction[] = { -1.f,-4.0f, -1.0f};
    float spot4_cutoff[] = { 80.0f };
    float spot4_diffuse[] = { 1.0f, 1.0f, 1.0f };
    glLightfv(GL_LIGHT4, GL_DIFFUSE, spot4_diffuse);
    glLightfv(GL_LIGHT4, GL_SPECULAR, spot4_diffuse);
    glLightfv(GL_LIGHT4, GL_POSITION, light4_position);
    glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, spot4_direction);
    glLightfv(GL_LIGHT4, GL_SPOT_CUTOFF, spot4_cutoff);
    // LUZ DO TETO 3
    float light5_position[] = { 50.0f,10.0f,-20.0f, 1.0 };
    float spot5_direction[] = { -1.f,-4.0f, -1.0f};
    float spot5_cutoff[] = { 80.0f };
    float spot5_diffuse[] = { 1.0f, 1.0f, 1.0f };
    glLightfv(GL_LIGHT5, GL_DIFFUSE, spot5_diffuse);
    glLightfv(GL_LIGHT5, GL_SPECULAR, spot5_diffuse);
    glLightfv(GL_LIGHT5, GL_POSITION, light5_position);
    glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, spot5_direction);
    glLightfv(GL_LIGHT5, GL_SPOT_CUTOFF, spot5_cutoff);
    // LUZ DO TETO 4
    float light6_position[] = { 50.0f,10.0f,-60.0f, 1.0 };
    float spot6_direction[] = { -1.f,-4.0f, -1.0f};
    float spot6_cutoff[] = { 80.0f };
    float spot6_diffuse[] = { 1.0f, 1.0f, 1.0f };
    glLightfv(GL_LIGHT6, GL_DIFFUSE, spot6_diffuse);
    glLightfv(GL_LIGHT6, GL_SPECULAR, spot6_diffuse);
    glLightfv(GL_LIGHT6, GL_POSITION, light6_position);
    glLightfv(GL_LIGHT6, GL_SPOT_DIRECTION, spot6_direction);
    glLightfv(GL_LIGHT6, GL_SPOT_CUTOFF, spot6_cutoff);

}

void init(){ // Função de inicialização

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpa o buffer de cor e o buffer de profundidade
    //TEXTURAS
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glEnable(GL_DEPTH_TEST); // HABILITA O TESTE DE PROFUNDIDADE
    glGenTextures(5, texID);
    carregaTextura(texID[0], "texturas/floor2.jpg");
    carregaTextura(texID[1], "texturas/parede2.png");
    carregaTextura(texID[2], "texturas/frente_frigobar.png");
    carregaTextura(texID[3], "texturas/livros.jpg");

    setup_lighting();
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
    glEnable(GL_TEXTURE_2D);
    chao(texID[0]);
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
    parede(texID[1]);
    glDisable(GL_TEXTURE_2D);
    fechadura();

    glPushMatrix();
    if(portaAberta){
        glRotatef(90.0, 0.0f, 1.0f, 0.0f);
        glTranslatef(6.0f,0.0f,-25.0f);
    }
    porta();
    glPopMatrix();
    // plano();
    if(janelaAberta){
        glPushMatrix();
        glTranslatef(posicaoJanelaEsquerda,0.0f,0.0f);
        janelaEsquerda();
        glPopMatrix();
        glPushMatrix();
        glTranslatef(posicaoJanelaDireita,0.0f,0.0f);
        janelaDireita();
        glPopMatrix();
    } else {
        glPushMatrix();
        glTranslatef(posicaoJanelaEsquerda,0.0f,0.0f);
        janelaEsquerda();
        glPopMatrix();
        glPushMatrix();
        glTranslatef(posicaoJanelaDireita,0.0f,0.0f);
        janelaDireita();
        glPopMatrix();
    }
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
    glEnable(GL_TEXTURE_2D);
    portaFrigobar(texID[2]);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    //FRIGOBAR - parte2
    glPushMatrix();
    glTranslatef(-15.0f, -5.0f-2.0f, -12.0f);
    frigobar();
    glEnable(GL_TEXTURE_2D);
    portaFrigobar(texID[2]);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    //armario - parte1
    glPushMatrix();
    glTranslatef(-15.0f, -2.0f, -30.0f);
    glEnable(GL_TEXTURE_2D);
    armario(texID[3]);
    glDisable(GL_TEXTURE_2D);
    portaArmario();
    glPopMatrix();
    //armario - parte2
    glPushMatrix();
    glTranslatef(-15.0f, -5.0f-2.0f, -30.0f);
    glEnable(GL_TEXTURE_2D);
    armario(texID[3]);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    //armario - parte3
    glPushMatrix();
    glTranslatef(-15.0f, +5.0f-2.0f, -30.0f);
    glEnable(GL_TEXTURE_2D);
    armario(texID[3]);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    //armario - parte4
    glPushMatrix();
    glTranslatef(-15.0f, -2.0f, -35.0f);
    glEnable(GL_TEXTURE_2D);
    armario(texID[3]);
    glDisable(GL_TEXTURE_2D);
    portaArmario();
    glPopMatrix();
    //armario - parte5
    glPushMatrix();
    glTranslatef(-15.0f, -5.0f-2.0f, -35.0f);
    glEnable(GL_TEXTURE_2D);
    armario(texID[3]);
    glDisable(GL_TEXTURE_2D);
    portaArmario();
    glPopMatrix();
    //armario - parte6
    glPushMatrix();
    glTranslatef(-15.0f, +5.0f-2.0f, -35.0f);
    glEnable(GL_TEXTURE_2D);
    armario(texID[3]);
    glDisable(GL_TEXTURE_2D);
    portaArmario();
    glPopMatrix();
    //armario - parte7
    glPushMatrix();
    glTranslatef(-15.0f, -2.0f, -40.0f);
    glEnable(GL_TEXTURE_2D);
    armario(texID[3]);
    glDisable(GL_TEXTURE_2D);
    portaArmario();
    glPopMatrix();
    //armario - parte8
    glPushMatrix();
    glTranslatef(-15.0f, -5.0f-2.0f, -40.0f);
    glEnable(GL_TEXTURE_2D);
    armario(texID[3]);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    //armario - parte9
    glPushMatrix();
    glTranslatef(-15.0f, +5.0f-2.0f, -40.0f);
    glEnable(GL_TEXTURE_2D);
    armario(texID[3]);
    glDisable(GL_TEXTURE_2D);
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
    // PRIMEIRA LUMINARIA
    glPushMatrix();
    glTranslatef(6.5f,-3.0f,-5.0f);
    glRotatef(45.0f,0.0f,1.0f,0.0f);
    abajur();
    glPopMatrix();
    // ESFERA EM BAIXO DA PRIMEIRA LUMINARIA
    glPushMatrix();
    glTranslatef(6.5 - 2.f,-3.0f - 1.f,-5.0f - 2.0f);
    glutSolidSphere(0.2f, 100.f, 200.f);
    glPopMatrix();
    // SEGUNDA LUMINARIA
    glPushMatrix();
    glTranslatef(6.5f + 25.0f,-3.0f,- 60.0f);
    glRotatef(120.0f,0.0f,1.0f,0.0f);
    abajur();
    glPopMatrix();
    // ESFERA EM BAIXO DA SEGUNDA LUMINARIA
    glPushMatrix();
    glTranslatef(6.5f + 25.0f - 2.f,-3.0f - 1.f,- 2.0f - 60.0f + 4.0f);
    glutSolidSphere(0.2f, 100.f, 200.f);
    glPopMatrix();
    // TERCEIRA LUMINARIA
    glPushMatrix();
    glTranslatef(56.0f,-3.0f,-35.0f);
    glRotatef(90.0f,0.0f,1.0f,0.0f);
    abajur();
    glPopMatrix();
    // ESFERA EM BAIXO DA TERCEIRA LUMINARIA
    glPushMatrix();
    glTranslatef(56.0f - 2.f,-3.0f - 1.f,-35.0f);
    glutSolidSphere(0.2f, 100.f, 200.f);
    glPopMatrix();

    // glPushMatrix();
    // glColor3f(1.0,0.0,0.0);
    // glTranslatef(6.5f + 25.0f,-2.0,- 60.0f);
    // glutSolidSphere(0.2f, 100.f, 200.f);
    // glPopMatrix();

    //LAMPADAS TETO
    //lampada 1
    glPushMatrix();
    glTranslatef(0.0f,8.0f,-20.0f);
    glColor3f(1.0f,1.0f,1.0f);
    paralelepipedo(12.0f,0.5f,2.0f);
    glPopMatrix();
    //lampada 2
    glPushMatrix();
    glTranslatef(0.0f,8.0f,-60.0f);
    glColor3f(1.0f,1.0f,1.0f);
    paralelepipedo(12.0f,0.5f,2.0f);
    glPopMatrix();
    //lampada 3
    glPushMatrix();
    glTranslatef(40.0f,8.0f,-20.0f);
    glColor3f(1.0f,1.0f,1.0f);
    paralelepipedo(12.0f,0.5f,2.0f);
    glPopMatrix();
    //lampada 4
    glPushMatrix();
    glTranslatef(40.0f,8.0f,-60.0f);
    glColor3f(1.0f,1.0f,1.0f);
    paralelepipedo(12.0f,0.5f,2.0f);
    glPopMatrix();



    glutSwapBuffers(); // Troca os buffers de vídeo utilizados para renderizar a cena
}

//OBJETOS
void parede(GLuint texID){

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texID);
    //FACE FRENTE
    //FACE ESQUERDA DA FRENTE
    glBegin(GL_QUADS);
        //face frente
        glColor3f(0.7, 0.7, 0.7);
        glTexCoord2f(0.0,0.0);
        glVertex3f(-20.0,6.0,10.0);
        glTexCoord2f(1.0,0.0);
        glVertex3f(-20.0,-10.0,10.0);
        glTexCoord2f(1.0,1.0);
        glVertex3f(-16.0,-10.0,10.0);
        glTexCoord2f(0.0,1.0);
        glVertex3f(-16.0,6.0,10.0);
        //espessura
        glTexCoord2f(0.0,0.0);
        glVertex3f(-20.0,6.0,10.0 - espessuraParede);
        glTexCoord2f(1.0,0.0);
        glVertex3f(-20.0,-10.0,10.0 - espessuraParede);
        glTexCoord2f(1.0,1.0);
        glVertex3f(-16.0,-10.0,10.0 - espessuraParede);
        glTexCoord2f(0.0,1.0);
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
        glTexCoord2f(0.0,0.0);
        glVertex3f(-8.0,6.0,10.0);
        glTexCoord2f(1.0,0.0);
        glVertex3f(-8.0,-10.0,10.0);
        glTexCoord2f(1.0,1.0);
        glVertex3f(comprimentoMaximo,-10.0,10.0);
        glTexCoord2f(0.0,1.0);
        glVertex3f(comprimentoMaximo,6.0,10.0);
        //expessura
        glTexCoord2f(0.0,0.0);
        glVertex3f(-8.0,6.0,10.0 - espessuraParede);
        glTexCoord2f(1.0,0.0);
        glVertex3f(-8.0,-10.0,10.0 - espessuraParede);
        glTexCoord2f(1.0,1.0);
        glVertex3f(comprimentoMaximo,-10.0,10.0 - espessuraParede);
        glTexCoord2f(0.0,1.0);
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
        glTexCoord2f(1.0,0.0);
        glVertex3f(-20.0,10.0,10.0);
        glTexCoord2f(0.0,0.0);
        glVertex3f(-20.0,6.0,10.0);
        glTexCoord2f(0.0,1.0);
        glVertex3f(comprimentoMaximo,6.0,10.0);
        glTexCoord2f(1.0,1.0);
        glVertex3f(comprimentoMaximo,10.0,10.0);
        //expessura
        glTexCoord2f(0.0,0.0);
        glVertex3f(-20.0,10.0,10.0 - espessuraParede);
        glTexCoord2f(1.0,0.0);
        glVertex3f(-20.0,6.0,10.0 - espessuraParede);
        glTexCoord2f(1.0,1.0);
        glVertex3f(comprimentoMaximo,6.0,10.0 - espessuraParede);
        glTexCoord2f(0.0,1.0);
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
        glTexCoord2f(0.0,0.0);
        glVertex3f(-20.0,10.0,larguraMaxima);
        glTexCoord2f(1.0,0.0);
        glVertex3f(-20.0,-10.0,larguraMaxima);
        glTexCoord2f(1.0,1.0);
        glVertex3f(-10.0,-10.0,larguraMaxima);
        glTexCoord2f(0.0,1.0);
        glVertex3f(-10.0,10.0,larguraMaxima);
        //
        //espessura
        glTexCoord2f(0.0,0.0);
        glVertex3f(-20.0,10.0,larguraMaxima - espessuraParede);
        glTexCoord2f(1.0,0.0);
        glVertex3f(-20.0,-10.0,larguraMaxima - espessuraParede);
        glTexCoord2f(1.0,1.0);
        glVertex3f(-10.0,-10.0,larguraMaxima - espessuraParede);
        glTexCoord2f(0.0,1.0);
        glVertex3f(-10.0,10.0,larguraMaxima - espessuraParede);
        // FACE DA FRENTE - TRÁS - DIREITA
        glColor3f(0.7,0.7,0.7);
        glTexCoord2f(0.0,0.0);
        glVertex3f(50.0,10.0,larguraMaxima);
        glTexCoord2f(1.0,0.0);
        glVertex3f(50.0,-10.0,larguraMaxima);
        glTexCoord2f(1.0,1.0);
        glVertex3f(60.0,-10.0,larguraMaxima);
        glTexCoord2f(0.0,1.0);
        glVertex3f(60.0,10.0,larguraMaxima);
        //
        //espessura
        glTexCoord2f(0.0,0.0);
        glVertex3f(50.0,10.0,larguraMaxima - espessuraParede);
        glTexCoord2f(1.0,0.0);
        glVertex3f(50.0,-10.0,larguraMaxima - espessuraParede);
        glTexCoord2f(1.0,1.0);
        glVertex3f(60.0,-10.0,larguraMaxima - espessuraParede);
        glTexCoord2f(0.0,1.0);
        glVertex3f(60.0,10.0,larguraMaxima - espessuraParede);
        // FACE DA FRENTE - TRÁS - CIMA
        glTexCoord2f(0.0,0.0);
        glVertex3f(-20.0,10.0,larguraMaxima);
        glTexCoord2f(1.0,0.0);
        glVertex3f(-20.0,5.0,larguraMaxima);
        glTexCoord2f(1.0,1.0);
        glVertex3f(comprimentoMaximo,5.0,larguraMaxima);
        glTexCoord2f(0.0,1.0);
        glVertex3f(comprimentoMaximo,10.0,larguraMaxima);
        //
        //espessura
        glTexCoord2f(0.0,0.0);
        glVertex3f(-10.0,10.0,larguraMaxima - espessuraParede);
        glTexCoord2f(1.0,0.0);
        glVertex3f(-10.0,5.0,larguraMaxima - espessuraParede);
        glTexCoord2f(1.0,1.0);
        glVertex3f(comprimentoMaximo,5.0,larguraMaxima - espessuraParede);
        glTexCoord2f(0.0,1.0);
        glVertex3f(comprimentoMaximo,10.0,larguraMaxima - espessuraParede);
        // FACE DA FRENTE - TRÁS - BAIXO
        glColor3f(0.7,0.7,0.7);
        glVertex3f(-20.0,-5.0,larguraMaxima);
        glVertex3f(-20.0,-10.0,larguraMaxima);
        glVertex3f(comprimentoMaximo,-10.0,larguraMaxima);
        glVertex3f(comprimentoMaximo,-5.0,larguraMaxima);
        //
        //espessura
        glTexCoord2f(0.0,0.0);
        glVertex3f(-20.0,-5.0,larguraMaxima - espessuraParede);
        glTexCoord2f(1.0,0.0);
        glVertex3f(-20.0,-10.0,larguraMaxima - espessuraParede);
        glTexCoord2f(1.0,1.0);
        glVertex3f(comprimentoMaximo,-10.0,larguraMaxima - espessuraParede);
        glTexCoord2f(0.0,1.0);
        glVertex3f(comprimentoMaximo,-5.0,larguraMaxima - espessuraParede);
        // FACE DA FRENTE - TRÁS - MEIO
        glColor3f(0.7,0.7,0.7);
        glTexCoord2f(0.0,0.0);
        glVertex3f(10.0,10.0,larguraMaxima);
        glTexCoord2f(1.0,0.0);
        glVertex3f(10.0,-10.0,larguraMaxima);
        glTexCoord2f(1.0,1.0);
        glVertex3f(30.0,-10.0,larguraMaxima);
        glTexCoord2f(0.0,1.0);
        glVertex3f(30.0,10.0,larguraMaxima);
        //
        //espessura
        glTexCoord2f(0.0,0.0);
        glVertex3f(10.0,10.0,larguraMaxima - espessuraParede);
        glTexCoord2f(1.0,0.0);
        glVertex3f(10.0,-10.0,larguraMaxima - espessuraParede);
        glTexCoord2f(1.0,1.0);
        glVertex3f(30.0,-10.0,larguraMaxima - espessuraParede);
        glTexCoord2f(0.0,1.0);
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
        glTexCoord2f(0.0,0.0);
        glVertex3f(comprimentoMaximo,10.0,larguraMaxima- espessuraParede);
        glTexCoord2f(1.0,0.0);
        glVertex3f(comprimentoMaximo,-10.0,larguraMaxima - espessuraParede);
        glTexCoord2f(1.0,1.0);
        glVertex3f(comprimentoMaximo,-10.0,larguraMaxima);
        glTexCoord2f(0.0,1.0);
        glVertex3f(comprimentoMaximo,10.0,larguraMaxima);
        // FACE DIREITA
        //frente
        glTexCoord2f(0.0,0.0);
        glVertex3f(comprimentoMaximo,10.0,10.0);
        glTexCoord2f(1.0,0.0);
        glVertex3f(comprimentoMaximo,-10.0,10.0);
        glTexCoord2f(1.0,1.0);
        glVertex3f(comprimentoMaximo,-10.0,larguraMaxima);
        glTexCoord2f(0.0,1.0);
        glVertex3f(comprimentoMaximo,10.0,larguraMaxima);
        //espessura
        glTexCoord2f(0.0,0.0);
        glVertex3f(comprimentoMaximo - espessuraParede,10.0,10.0);
        glTexCoord2f(1.0,0.0);
        glVertex3f(comprimentoMaximo - espessuraParede,-10.0,10.0);
        glTexCoord2f(1.0,1.0);
        glVertex3f(comprimentoMaximo - espessuraParede,-10.0,larguraMaxima);
        glTexCoord2f(0.0,1.0);
        glVertex3f(comprimentoMaximo - espessuraParede,10.0,larguraMaxima);
        // FACE DIREITA DENTRO
        //frente
        glTexCoord2f(0.0,0.0);
        glVertex3f(-6.0,10.0,10.0);
        glTexCoord2f(1.0,0.0);
        glVertex3f(-6.0,-10.0,10.0);
        glTexCoord2f(1.0,1.0);
        glVertex3f(-6.0,-10.0,-10.0);
        glTexCoord2f(0.0,1.0);
        glVertex3f(-6.0,10.0,-10.0);
        //espessura
        glTexCoord2f(0.0,0.0);
        glVertex3f(-6.0 - espessuraParede,10.0,10.0);
        glTexCoord2f(1.0,0.0);
        glVertex3f(-6.0 - espessuraParede,-10.0,10.0);
        glTexCoord2f(1.0,1.0);
        glVertex3f(-6.0 - espessuraParede,-10.0,-10.0);
        glTexCoord2f(0.0,1.0);
        glVertex3f(-6.0 - espessuraParede,10.0,-10.0);
        //tras
        glTexCoord2f(0.0,0.0);
        glVertex3f(-6.0,10.0,-10.0);
        glTexCoord2f(1.0,0.0);
        glVertex3f(-6.0 - espessuraParede,10.0,-10.0);
        glTexCoord2f(1.0,1.0);
        glVertex3f(-6.0 - espessuraParede,-10.0,-10.0);
        glTexCoord2f(0.0,1.0);
        glVertex3f(-6.0,-10.0,-10.0);
        // FACE ESQUERDA
        //frente
        glTexCoord2f(0.0,0.0);
        glVertex3f(-20.0,10.0,10.0);
        glTexCoord2f(1.0,0.0);
        glVertex3f(-20.0,-10.0,10.0);
        glTexCoord2f(1.0,1.0);
        glVertex3f(-20.0,-10.0,larguraMaxima);
        glTexCoord2f(0.0,1.0);
        glVertex3f(-20.0,10.0,larguraMaxima);
        glColor3f(0.7,0.7,0.7);
        //espessura
        glTexCoord2f(0.0,0.0);
        glVertex3f(-20.0 + espessuraParede,10.0,10.0);
        glTexCoord2f(1.0,0.0);
        glVertex3f(-20.0 + espessuraParede,-10.0,10.0);
        glTexCoord2f(1.0,1.0);
        glVertex3f(-20.0 + espessuraParede,-10.0,larguraMaxima);
        glTexCoord2f(0.0,1.0);
        glVertex3f(-20.0 + espessuraParede,10.0,larguraMaxima);
        //FACE DE CIMA
        //frente
        glTexCoord2f(0.0,0.0);
        glVertex3f(-20.0,10.0,larguraMaxima);
        glTexCoord2f(1.0,0.0);
        glVertex3f(-20.0,10.0,10.0);
        glTexCoord2f(1.0,1.0);
        glVertex3f(comprimentoMaximo,10.0,10.0);
        glTexCoord2f(0.0,1.0);
        glVertex3f(comprimentoMaximo,10.0,larguraMaxima);
        glColor3f(0.9,0.9,0.9);
        //espessura
        glTexCoord2f(0.0,0.0);
        glVertex3f(-20.0,10.0 - espessuraParede,larguraMaxima);
        glTexCoord2f(1.0,0.0);
        glVertex3f(-20.0,10.0 - espessuraParede,10.0);
        glTexCoord2f(1.0,1.0);
        glVertex3f(comprimentoMaximo,10.0 - espessuraParede,10.0);
        glTexCoord2f(0.0,1.0);
        glVertex3f(comprimentoMaximo,10.0 - espessuraParede,larguraMaxima);
    glEnd();
    glPopMatrix();
}

void chao(GLuint texID){
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texID);
    glBegin(GL_QUADS);
        //Face de baixo
        glColor3f(0.9,0.9,0.9);
        glTexCoord2f(0.0,0.0); glVertex3f(-20.0,-10.0,larguraMaxima);
        glTexCoord2f(1.0,0.0); glVertex3f(-20.0,-10.0,10.0);
        glTexCoord2f(1.0,1.0); glVertex3f(comprimentoMaximo,-10.0,10.0);
        glTexCoord2f(0.0,1.0); glVertex3f(comprimentoMaximo,-10.0,larguraMaxima);
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
        glColor3f(1.0,1.0,1.0f);
        glVertex3f(-10.0,5.0,larguraMaxima);
        glVertex3f(-10.0,-5.0,larguraMaxima);
        glVertex3f(10.0,-5.0,larguraMaxima);
        glVertex3f(10.0,5.0,larguraMaxima);
        //bordas brancas - espessura
        glColor3f(1.0,1.0,1.0);
        glVertex3f(-10.0,5.0,larguraMaxima - espessuraParede - 0.2);
        glVertex3f(-10.0,-5.0,larguraMaxima - espessuraParede - 0.2);
        glVertex3f(10.0,-5.0,larguraMaxima - espessuraParede - 0.2);
        glVertex3f(10.0,5.0,larguraMaxima - espessuraParede - 0.2);
        //bordas brancas - direita
        glColor3f(1.0,1.0,1.0);
        glVertex3f(10.0,5.0,larguraMaxima - espessuraParede - 0.2);
        glVertex3f(10.0,-5.0,larguraMaxima - espessuraParede - 0.2);
        glVertex3f(10.0,-5.0,larguraMaxima);
        glVertex3f(10.0,5.0,larguraMaxima);
        //bordas brancas - esquerda
        glColor3f(1.0,1.0,1.0);
        glVertex3f(-10.0,5.0,larguraMaxima - espessuraParede - 0.2);
        glVertex3f(-10.0,-5.0,larguraMaxima - espessuraParede - 0.2);
        glVertex3f(-10.0,-5.0,larguraMaxima);
        glVertex3f(-10.0,5.0,larguraMaxima);
        // // //espelho
        // glColor3f(.0,1.0,1.0);
        // glVertex3f(-10.0+0.5,5.0-0.5,larguraMaxima+0.001);
        // glVertex3f(-10.0+0.5,-5.0+0.5,larguraMaxima+0.001);
        // glVertex3f(10.0-0.5,-5.0+0.5,larguraMaxima+0.001);
        // glVertex3f(10.0-0.5,5.0-0.5,larguraMaxima+0.001);
        // //espelho
        // glColor3f(.0,1.0,1.0);
        // glVertex3f(-10.0+0.5,5.0-0.5,larguraMaxima-0.001 - espessuraParede);
        // glVertex3f(-10.0+0.5,-5.0+0.5,larguraMaxima-0.001 - espessuraParede);
        // glVertex3f(10.0-0.5,-5.0+0.5,larguraMaxima-0.001 - espessuraParede);
        // glVertex3f(10.0-0.5,5.0-0.5,larguraMaxima-0.001 - espessuraParede);
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
        // glColor3f(.0,1.0,1.0);
        // glVertex3f(30.0+0.5,5.0-0.5,larguraMaxima+0.01);
        // glVertex3f(30.0+0.5,-5.0+0.5,larguraMaxima+0.01);
        // glVertex3f(50.0-0.5,-5.0+0.5,larguraMaxima+0.01);
        // glVertex3f(50.0-0.5,5.0-0.5,larguraMaxima+0.01);
        // //espelho
        // glColor3f(.0,1.0,1.0);
        // glVertex3f(30.0+0.5,5.0-0.5,larguraMaxima-0.01 - espessuraParede);
        // glVertex3f(30.0+0.5,-5.0+0.5,larguraMaxima-0.01 - espessuraParede);
        // glVertex3f(50.0-0.5,-5.0+0.5,larguraMaxima-0.01 - espessuraParede);
        // glVertex3f(50.0-0.5,5.0-0.5,larguraMaxima-0.01 - espessuraParede);
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

void armario(GLuint texID){
    glBindTexture(GL_TEXTURE_2D, texID);

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
    glTexCoord2f(0.0,0.0);
    glVertex3f(-0.5, -0.5, 0.5); // Vértice 1
    glTexCoord2f(1.0,0.0);
    glVertex3f(0.5, -0.5, 0.5); // Vértice 2
    glTexCoord2f(1.0,1.0);
    glVertex3f(0.5, 0.5, 0.5); // Vértice 3
    glTexCoord2f(0.0,1.0);
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

void portaFrigobar(GLuint texID){
    glBindTexture(GL_TEXTURE_2D, texID);

    glPushMatrix();
    glScalef(5.0,5.0,5.0);
    glRotatef(-90.0f,0.0f,1.0f,0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.6,0.1,0.1);
        glTexCoord2f(0.0,1.0);
    glVertex3f(-0.5, -0.5, -0.5); // Vértice 1
        glTexCoord2f(1.0,1.0);
    glVertex3f(0.5, -0.5, -0.5); // Vértice 2
        glTexCoord2f(1.0,0.0);
    glVertex3f(0.5, 0.5, -0.5); // Vértice 3
        glTexCoord2f(0.0,0.0);
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

void abajur(){
    // Desenhar a geometria do abajur
    glColor3f(1.f, 1.f, 1.f);  // Cor do abajur

    // Base do abajur
    glPushMatrix();
    glTranslatef(0.0f,-1.0f,0.0f);
    paralelepipedo(1.0f,0.2f,1.0f);
    glPopMatrix();
    // Tronco do abajur
    glColor3f(0.f, 0.f, 0.6f);
    glPushMatrix();
    glTranslatef(0.0f,-0.25f,0.0f);
    paralelepipedo(0.2f,1.75f,0.2f);
    glPopMatrix();

    glColor3f(1.f, 1.f, 1.f);
    // Parte superior do abajur (cone)
    GLUquadricObj* cone = gluNewQuadric();
    gluQuadricDrawStyle(cone, GLU_FILL);
    glPushMatrix();
    glRotatef(-45.0,1.0,0.0,0.0);
    glTranslatef(0.0f,0.6f,-0.5f);
    gluCylinder(cone, 0.5f, 0.2f, 1.0f, 20, 1);
    glTranslatef(0.0f,0.0f,1.f);
    gluDisk(cone, 0.0f, 0.2f, 20, 1);
    glPopMatrix();

    // Lampada em esfera
    // glColor3f(1.0f,1.0f,1.0f);
    // GLUquadricObj* sphere = gluNewQuadric();
    // gluQuadricDrawStyle(sphere, GLU_FILL);
    // glPushMatrix();
    // glRotatef(15.0,-1.0,1.0,0.0);
    // glTranslatef(0.0f,0.6f,-0.2f);
    // gluSphere(sphere, 0.25f, 20, 20);
    // glPopMatrix();

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
    if(key == 'k' || key == 'K'){
        if(abajuresLigado){
            abajuresLigado = FALSE;
        }
        else{
            abajuresLigado = TRUE;
        }
    }
    if(key == 'l' || key == 'L'){
        if(lampadasLigado){
            lampadasLigado = FALSE;
        }
        else{
            lampadasLigado = TRUE;
        }
    }
    if(key == 'j' || key == 'J'){
        if(janelaAberta){
            janelaAberta = FALSE;
        }
        else{
            janelaAberta = TRUE;
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
        anguloVentilador+=1.0;
        if(anguloVentilador == 360){
            anguloVentilador =0;
        }
    }
    if (janelaAberta) {
        posicaoJanelaEsquerda += 0.2f;
        if(posicaoJanelaEsquerda >= 15){
            posicaoJanelaEsquerda = 15;
            janelaAberta = TRUE;
        }
        posicaoJanelaDireita -= 0.2f;
        if(posicaoJanelaDireita <= -15){
            posicaoJanelaDireita = -15;
            janelaAberta = TRUE;
        }
    } else {
        posicaoJanelaEsquerda -= 0.2f;
        if(posicaoJanelaEsquerda <= 0){
            posicaoJanelaEsquerda = 0;
            janelaAberta = FALSE;
        }
        posicaoJanelaDireita += 0.2f;
        if(posicaoJanelaDireita >= 0){
            posicaoJanelaDireita = 0;
            janelaAberta = FALSE;
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