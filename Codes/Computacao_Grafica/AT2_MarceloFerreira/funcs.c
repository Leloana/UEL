//gcc funcs.c glad.c -lGL -lGLU -lglut -lglfw -lm
#include <GLFW/glfw3.h>
#include <math.h>

void drawLineDDA(float x1, float y1, float x2, float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    int steps = (fabs(dx) > fabs(dy)) ? fabs(dx) : fabs(dy);
    float xIncrement = dx / steps;
    float yIncrement = dy / steps;

    float x = x1;
    float y = y1;
    glBegin(GL_POINTS);
    for (int i = 0; i <= steps; i++) {
        
        glVertex2f(x / 400.0f, y / 300.0f);
        x += xIncrement;
        y += yIncrement;
        y = round(y);
    }
    glEnd();
}

void drawLineBresenham(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int d = 2 * dy - dx;
    int dE = 2 * dy;
    int dNE = 2 * (dy - dx);
    int x = x1;
    int y = y1;

    glBegin(GL_POINTS);
    glVertex2f(x / 400.0f, y / 300.0f);
    while (x < x2) {
        if (d <= 0) {
            d += dE;
            x++;
        } else {
            d += dNE;
            x++;
            y++;
        }
        glVertex2f(x / 400.0f, y / 300.0f);
    }
    glEnd();
}

void drawCircleMidpoint(int xc, int yc, int r) {
    int x = 0;
    int y = r;
    int d = 1 - r;
    glBegin(GL_POINTS);
    while (x <= y) {
        glVertex2f((xc + x) / 400.0f, (yc + y) / 300.0f);
        glVertex2f((xc - x) / 400.0f, (yc + y) / 300.0f);
        glVertex2f((xc + x) / 400.0f, (yc - y) / 300.0f);
        glVertex2f((xc - x) / 400.0f, (yc - y) / 300.0f);
        glVertex2f((xc + y) / 400.0f, (yc + x) / 300.0f);
        glVertex2f((xc - y) / 400.0f, (yc + x) / 300.0f);
        glVertex2f((xc + y) / 400.0f, (yc - x) / 300.0f);
        glVertex2f((xc - y) / 400.0f, (yc - x) / 300.0f);
        x++;
        if (d < 0) {
            d += 2 * x + 1;
        } else {
            y--;
            d += 2 * (x - y) + 1;
        }
    }
    glEnd();
}

int main() {
    if (!glfwInit()) {
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "Algoritmos de Bresenham e DDA", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Desenhar uma linha com DDA
        glColor3f(1.0f, 0.0f, 0.0f); // Vermelho
        drawLineDDA(-1000, 0, 1000, 0);

        // Desenhar uma linha com Bresenham
        glColor3f(0.0f, 1.0f, 0.0f); // Verde
        drawLineBresenham(-200, -200, 200, 200);

        // Desenhar uma circunferência com o algoritmo do ponto médio
        glColor3f(0.0f, 0.0f, 1.0f); // Azul
        drawCircleMidpoint(0, 0, 150);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}