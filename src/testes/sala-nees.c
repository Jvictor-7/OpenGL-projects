#include <GL/glut.h>
#include <math.h>

// Posição do observador na cena
float obsX = 0.0, obsY = 0.0, obsZ = 5.0;

void display() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 800.0 / 600.0, 1.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(obsX, obsY, obsZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(1.0, 1.0, 1.0);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0); glVertex3f(-4.0, -4.0, -10.0);
   glTexCoord2f(4.0, 0.0); glVertex3f(4.0, -4.0, -10.0);
   glTexCoord2f(4.0, 4.0); glVertex3f(4.0, 4.0, -10.0);
   glTexCoord2f(0.0, 4.0); glVertex3f(-4.0, 4.0, -10.0);
   glEnd();

    // Desenha a porta azul marinho
    glColor3f(0.0, 0.0, 0.5);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -1.0, -4.99);
    glTexCoord2f(1.0, 0.0); glVertex3f(0.5, -1.0, -4.99);
    glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 1.0, -4.99);
    glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 1.0, -4.99);
    glEnd();

    glutSwapBuffers();
}

void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            obsX -= 0.1;
            break;
        case GLUT_KEY_RIGHT:
            obsX += 0.1;
            break;
        case GLUT_KEY_UP:
            obsZ -= 0.1;
            break;
        case GLUT_KEY_DOWN:
            obsZ += 0.1;
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Sala NEES");
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);
    glutMainLoop();
    return 0;
}