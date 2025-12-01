#define GL_SILENCE_DEPRECATION
#include <iostream>
#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int coord = 300; // Coordenada basica usada para delimitar as divisoes dos triangulos
float movimento_pulsando = 1.0f;
float movimento_vertical = -100.0f;
float movimento_pulsandoDirection = 1.0f;
float movimento_horizontal = 100.0f;

void movimentos(int value);
void desenhaTriangulo();
void drawLines();
void init(void);
void myDisplay(void);

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(150, 150);
    glutCreateWindow("Transformacoes 2D");

    init();

    glutDisplayFunc(myDisplay);
    glutTimerFunc(60, movimentos, 0); // Essa funcao chama as transformacoes

    glutMainLoop();
    return 0;
}

void desenhaTriangulo() {
    glBegin(GL_TRIANGLES);
        glVertex2i(0, 50);
        glVertex2i(50, -50);
        glVertex2i(-50, -50);
    glEnd();
}

void myDisplay(void) {
    glClear(GL_COLOR_BUFFER_BIT); 
    glViewport(0, 0, 600, 600);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100.0f, 100.0f, -100.0f, 100.0f);
    drawLines();
    // Triangulo estatico
    glViewport(0, coord, coord, coord);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100.0f, 100.0f, -100.0f, 100.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    desenhaTriangulo();
    // Triangulo pulsando
    glViewport(coord, coord, coord, coord);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100.0f * movimento_pulsando, 100.0f * movimento_pulsando, -100.0f * movimento_pulsando, 100.0f * movimento_pulsando);
    glColor3f(0.0f, 1.0f, 0.0f);
    desenhaTriangulo();
    // Triangulo com movimento horizontal
    glViewport(coord, 0, coord, coord);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100.0f + movimento_horizontal, 100.0f + movimento_horizontal, -100.0f, 100.0f);
    glColor3f(1.0f, 1.0f, 0.0f);
    desenhaTriangulo();
    // Triangulo com movimento vertical
    glViewport(0, 0, coord, coord);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100.0f, 100.0f, -100.0f + movimento_vertical, 100.0f + movimento_vertical);
    glColor3f(0.0f, 0.0f, 1.0f);
    desenhaTriangulo();
    glutSwapBuffers();
}

void drawLines() {
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
        // Horizontal line
        glVertex2f(-100.0f, 0.0f);
        glVertex2f(100.0f, 0.0f);
        // Vertical line
        glVertex2f(0.0f, -100.0f);
        glVertex2f(0.0f, 100.0f);
    glEnd();
}

void init(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
}

void movimentos(int value) {
    // movimentos movimento_pulsando (zoom-in and zoom-out)
    movimento_pulsando += 0.05f * movimento_pulsandoDirection;
    if (movimento_pulsando > 4.0f || movimento_pulsando < 0.5f)movimento_pulsandoDirection = -movimento_pulsandoDirection;
    // movimentos horizontal movement (right to left)
    movimento_horizontal -= 2.0f;
    if (movimento_horizontal < -200.0f) movimento_horizontal = 200.0f; // Reseta o movimento
    // movimentos vertical movement (bottom to top)
    movimento_vertical += 2.0f;
    if (movimento_vertical > 200.0f)movimento_vertical = -200.0f; // Reseta o movimento
    glutPostRedisplay();
    glutTimerFunc(30, movimentos, 0);
}
