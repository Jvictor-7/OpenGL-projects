#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

void display();
void reshape(int, int);
void timer(int);

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

int main (int argc, char**argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutInitWindowPosition(200, 100);
    glutInitWindowSize(500, 500);

    glutCreateWindow("Window 1");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    // Com glutTimerFunc a função timer é chamada de 0 milisegundos em 0 milisegundos
    glutTimerFunc(0, timer, 0);

    //Mudando a cor do background
    init();

    glutMainLoop();
}

float x_position = -8.0;
int state = 1;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    //Reseta as coordenadas
    glLoadIdentity();

    glTranslatef(x_position, x_position, 0.0);

    //Desenhe coisas aqui

    //Desenhando um retangulo
    glBegin(GL_POLYGON);
        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(-1.0, 1.0);       
        glColor3f(1.0, 1.0, 0.0);
        glVertex2f(-1.0, -1.0);       
        glColor3f(0.0, 1.0, 0.0);
        glVertex2f(1.0, -1.0);       
        glColor3f(0.0, 0.0, 1.0);
        glVertex2f(1.0, 1.0);       
    glEnd();


    glutSwapBuffers();
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

void timer(int)
{
    glutPostRedisplay();
    // Definindo a animação com 60FPS
    glutTimerFunc(1000/60, timer, 0);

    switch(state)
    {
        case 1:
            if(x_position < 9)
                x_position += 0.10;
            else
                state = -1;
            break;
        case -1:
            if(x_position > -9)
                x_position -= 0.10;
            else
                state = 1;
            break;
    }
    
}
