#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

void display();
void reshape(int, int);

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

int main (int argc, char**argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);

    glutInitWindowPosition(200, 100);
    glutInitWindowSize(500, 500);

    glutCreateWindow("Window 1");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    //Mudando a cor do background
    init();

    glutMainLoop();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    //Reseta as coordenadas
    glLoadIdentity();

    //Desenhe coisas aqui

    //Dando cor ao retangulo
    glColor3f(1.0f, 0.2f, 0.5f);
    //Desenhando um retangulo
    glBegin(GL_POLYGON);
    glVertex2f(8.0, 5.0);     
    glVertex2f(8.0, -5.0);    
    glVertex2f(-8.0, -5.0);    
    glVertex2f(-8.0, 5.0);    
    glEnd();

    glFlush();
}

void reshape(int largura, int altura)
{
    //Viewport (area em que os objetos poderam ser vistos)
    glViewport(0, 0, (GLsizei)largura, (GLsizei)altura);
    
    //Projection
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluOrtho2D(-10, 10, -10, 10);

    glMatrixMode(GL_MODELVIEW);
}
