#include <GLFW/glfw3.h>

void drawHouse() {
    // Fundo branco
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Base da casa (quadrado cinza)
    glBegin(GL_QUADS);
        glColor3f(0.5f, 0.5f, 0.5f); // Cinza
        glVertex2f(-0.5f, -0.7f);
        glVertex2f(0.5f, -0.7f);
        glVertex2f(0.5f, 0.0f);
        glVertex2f(-0.5f, 0.0f);
    glEnd();
    
    // Chaminé (retângulo marrom)
    glBegin(GL_QUADS);
        glColor3f(0.6f, 0.3f, 0.0f); // Marrom
        glVertex2f(-0.2f, 0.2f);
        glVertex2f(-0.3f, 0.2f);
        glVertex2f(-0.3f, 0.5f);
        glVertex2f(-0.2f, 0.5f);
    glEnd();

    // Telhado (triângulo vermelho)
    glBegin(GL_TRIANGLES);
        glColor3f(0.8f, 0.2f, 0.0f); // Vermelho
        glVertex2f(-0.5f, 0.0f);
        glVertex2f(0.0f, 0.5f);
        glVertex2f(0.5f, 0.0f);
    glEnd();

    // Porta (quadrado azul claro)
    glBegin(GL_QUADS);
        glColor3f(0.5f, 1.0f, 1.0f); // Azul claro
        glVertex2f(-0.3f, -0.7f);
        glVertex2f(-0.1f, -0.7f);
        
        glVertex2f(-0.1f, -0.2f);
        glVertex2f(-0.3f, -0.2f);
    glEnd();

    // Janela (quadrado azul claro)
    glBegin(GL_QUADS);
        glColor3f(0.5f, 1.0f, 1.0f); // Azul claro
        glVertex2f(0.1f, -0.4f);
        glVertex2f(0.4f, -0.4f);
        
        glVertex2f(0.4f, -0.1f);
        glVertex2f(0.1f, -0.1f);
    glEnd();

}

int main() {
    if (!glfwInit()) {
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "Desenho da Casa", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)) {
        drawHouse();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
