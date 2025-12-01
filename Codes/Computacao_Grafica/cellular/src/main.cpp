#include <cell/app.hpp>
#include <iostream>
#include <util/util.hpp>

void print_help() {
    println("Pression ENTER para reiniciar as celulas");
    println("Pression '1' para o conjunto de regras padrao");
    println("Pression '2' para o conjunto de regras '68'");
    println("Pression '3' para o conjunto de regras 'cloud'");
    println("Pression '4' para o conjunto de regras 'decay'");
    println("Pression '+' para aumentar a velocidade do jogo");
    println("Pression '-' para diminuir a velocidade do jogo");
    println("Use o scroll do mouse para aumentar/diminuir as dimensoes do "
            "jogo");
}

int main(void) {
    if (!glfwInit()) {
        return 1;
    }
    GLFWwindow *window = glfwCreateWindow(
        WINDOW_WIDTH, WINDOW_HEIGHT, "3D Cellular Automaton", NULL, NULL
    );
    if (!window) {
        std::cerr << "Failed to create window\n";
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGL(glfwGetProcAddress)) {
        std::cerr << "Failed to initialize Glad\n";
        return 1;
    }

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glfwSetKeyCallback(window, keyboard);
    glfwSetScrollCallback(window, scroll);
    glfwSetFramebufferSizeCallback(window, framebuffer_size);
    glfwSwapInterval(1);

    init();

    print_help();

    size_t i = 0;
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        display(window);
        timer(i);
        i += 1;

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    deinit();

    glfwTerminate();

    return 0;
}
