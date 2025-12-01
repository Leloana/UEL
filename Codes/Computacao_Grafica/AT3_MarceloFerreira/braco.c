#include <GLFW/glfw3.h>
#include <cmath>

void drawRectangle(float width, float height, float r, float g, float b);

int main() {
    if (!glfwInit()) {
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "Braco Mecanico", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-400, 400, -300, 300, -1, 1);
    glMatrixMode(GL_MODELVIEW);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        float time = glfwGetTime();

        float lowerArmAngle = sin(time) * 90.0f;
        float upperArmAngle = sin(time * 1.5f) * 45.0f;

        glPushMatrix();
        //Fixo
        drawRectangle(-50.0f, -110.0f, 0.5f, 0.5f, 0.5f);
        
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0.0f, 20.0f, 0.0f); 
        glRotatef(lowerArmAngle, 0.0f, 0.0f, 1.0f); 
        //Vermelho
        drawRectangle(25.0f, 100.0f, 1.0f, 0.0f, 0.0f);

        glTranslatef(0.0f, 140.0f, 0.0f);
        glRotatef(upperArmAngle, 0.0f, 0.0f, 1.0f); 
        //Azul
        drawRectangle(25.0f, 100.0f, 0.0f, 0.0f, 1.0f); 

        glPopMatrix();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}


void drawRectangle(float width, float height, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2f(-width / 2, 0.0f);
    glVertex2f(width / 2, 0.0f);
    glVertex2f(width / 2, height);
    glVertex2f(-width / 2, height);
    glEnd();
}