#include <GL/glut.h>
#include <GL/gl.h>
#include <SOIL/SOIL.h>  // Requer SOIL para carregamento de imagens
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
//gcc -std=c99 -o pokebola pokebola.c -lGL -lGLU -lglut -lSOIL


/* --- DEFINIÇÕES GERAIS --- */
#define TIMER_INTERVAL 16   // aproximadamente 60fps

// Estados da cena
enum { SCENE_3D = 1, SCENE_2D_INPUT, SCENE_2D_FINAL };
int currentScene = SCENE_3D;
bool sceneTransitioned = false; // Para garantir transição única

// Tamanho da janela
int windowWidth = 800, windowHeight = 600;

// Variáveis para interação 3D
float rotateX = 20.0f, rotateY = 30.0f;
int lastMouseX, lastMouseY;
bool mouseDown = false;

// Variáveis para animação da abertura da pokebola
float openAngle = 0.0f;       // ângulo de abertura (graus)
bool opening = false;         // se true: abrindo; false: fechando (no SCENE_3D)
float openSpeed = 1.0f;       // velocidade (graus por frame)

// Variáveis para input 2D
char inputBuffer[256] = "";
char* palavra_chave;
int inputIndex = 0;

// IDs de textura para imagens de fundo (Cena 2 e 3)
GLuint bgTexture;     // imagem de fundo para cena 2 (input)
GLuint finalTexture;  // imagem exibida na cena 3 (quando o usuário digita "pikachu")

/* --- FUNÇÕES AUXILIARES --- */

// Carrega as texturas usando SOIL. Substitua os nomes dos arquivos conforme desejar.
void loadTextures(void) {
    // Array de pares de imagens: cada par é composto pelo nome da imagem de fundo e da imagem final
    const char *pares[][2] = {
        {"pikachu.jpg",       "pikachu-found.jpg"},  // Par: Pikachu
        {"mankey.jpg",        "mankey-found.jpg"}    // Par: Mankey
        // Você pode adicionar outros pares aqui, se desejar.
    };
    
    // Número de pares disponíveis
    int numPares = sizeof(pares) / sizeof(pares[0]);
    
    // Inicializa a seed para a randomização com o tempo atual
    srand((unsigned)time(NULL));
    
    // Seleciona um par aleatório
    int indice = rand() % numPares;
    
    // Carrega a textura de fundo (imagem 1)
    bgTexture = SOIL_load_OGL_texture(pares[indice][0], SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    if(bgTexture == 0)
        printf("Erro ao carregar %s\n", pares[indice][0]);
    
    // Carrega a textura final (imagem 2)
    finalTexture = SOIL_load_OGL_texture(pares[indice][1], SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    if(finalTexture == 0)
        printf("Erro ao carregar %s\n", pares[indice][1]);
}

// Função para renderizar uma string usando fonte bitmap
void renderBitmapString(float x, float y, void *font, const char *string) {
    const char *c;
    glRasterPos2f(x, y);
    for(c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void transitionToScene2D(int value) {
    currentScene = SCENE_2D_INPUT;
    glutPostRedisplay();
}


/* --- CENA 3D: POKÉBOLA --- */

// Inicializa iluminação e materiais
void initLighting(void) {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    GLfloat lightPos[]  = { 0.0f, 5.0f, 5.0f, 1.0f };
    GLfloat ambient[]   = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat diffuse[]   = { 0.8f, 0.8f, 0.8f, 1.0f };
    
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  diffuse);
    
    // Permite que o glColor3f afete os materiais
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

// Desenha um hemisfério (usa glClipPlane)  
// Se isTop for true, desenha a parte com y >= 0; senão, y <= 0.
void drawHemisphere(int isTop) {
    GLdouble eq[4];
    if (isTop) {
        eq[0] = 0.0; eq[1] = 1.0; eq[2] = 0.0; eq[3] = 0.0;
    } else {
        eq[0] = 0.0; eq[1] = -1.0; eq[2] = 0.0; eq[3] = 0.0;
    }
    
    glClipPlane(GL_CLIP_PLANE0, eq);
    glEnable(GL_CLIP_PLANE0);
    
    GLUquadric *quad = gluNewQuadric();
    gluQuadricNormals(quad, GLU_SMOOTH);
    gluSphere(quad, 1.0, 50, 50);
    gluDeleteQuadric(quad);
    
    glDisable(GL_CLIP_PLANE0);
}

// Desenha a pokebola composta pela parte inferior (branca) e superior (vermelha)
// A parte superior é rotacionada em torno do pivô (0,0,1) para simular a abertura.
void drawPokebola(void) {
    // Parte inferior (branca)
    glPushMatrix();
        glColor3f(1.0f, 1.0f, 1.0f);
        drawHemisphere(0);
    glPopMatrix();
    
    // Parte superior (vermelha)
    glPushMatrix();
        // Transladar para que o pivô (0,0,1) fique na origem, rotacionar e voltar
        glTranslatef(0.0f, 0.0f, -1.0f);
        // Se necessário, inverta o sinal para que a abertura ocorra para cima
        glRotatef(-openAngle, 1.0f, 0.0f, 0.0f);
        glTranslatef(0.0f, 0.0f, 1.0f);
        glColor3f(1.0f, 0.0f, 0.0f);
        drawHemisphere(1);
    glPopMatrix();
}

// Desenha a cena 3D: configura a projeção perspectiva e a câmera
void drawScene3D(void) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)windowWidth/windowHeight, 1.0, 20.0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0,   // posição do olho
              0.0, 0.0, 0.0,   // para onde olha
              0.0, 1.0, 0.0);  // vetor "up"
    
    // Aplica rotação da cena (via mouse)
    glRotatef(rotateX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotateY, 0.0f, 1.0f, 0.0f);
    
    drawPokebola();
}

/* --- CENA 2: INTERFACE 2D (INPUT) --- */

// Desenha a cena 2D com a imagem de fundo e uma caixa de input de texto
void drawScene2D(void) {
    // Desabilita iluminação e depth test para desenhar 2D
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    
    // Desenha o fundo
    glBindTexture(GL_TEXTURE_2D, bgTexture);
    glColor3f(1,1,1);
    glBegin(GL_QUADS);
        glTexCoord2f(0,0); glVertex2f(0, 0);
        glTexCoord2f(1,0); glVertex2f(windowWidth, 0);
        glTexCoord2f(1,1); glVertex2f(windowWidth, windowHeight);
        glTexCoord2f(0,1); glVertex2f(0, windowHeight);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
    
    // Desenha uma "caixa" de input (retângulo sem preenchimento)
    int boxWidth = 400, boxHeight = 40;
    int boxX = (windowWidth - boxWidth) / 2;
    int boxY = 50;
    glColor3f(1,1,1);
    glBegin(GL_QUADS);
        glVertex2i(boxX, boxY);
        glVertex2i(boxX + boxWidth, boxY);
        glVertex2i(boxX + boxWidth, boxY + boxHeight);
        glVertex2i(boxX, boxY + boxHeight);
    glEnd();
    glColor3f(0,0,0);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2i(boxX, boxY);
        glVertex2i(boxX + boxWidth, boxY);
        glVertex2i(boxX + boxWidth, boxY + boxHeight);
        glVertex2i(boxX, boxY + boxHeight);
    glEnd();
    // Renderiza o texto digitado dentro da caixa
    glColor3f(0,0,0);
    renderBitmapString(boxX + 10, boxY + boxHeight/2 - 5, GLUT_BITMAP_HELVETICA_18, inputBuffer);
    
    // Reativa depth test (caso precise em outros trechos)
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
}

// Desenha a cena 3D final (imagem exibida quando o usuário digita "pikachu")
void drawScene3(void) {
    // Desabilita iluminação e depth test para a cena 2D
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, finalTexture);
    glColor3f(1,1,1);
    glBegin(GL_QUADS);
        glTexCoord2f(0,0); glVertex2f(0, 0);
        glTexCoord2f(1,0); glVertex2f(windowWidth, 0);
        glTexCoord2f(1,1); glVertex2f(windowWidth, windowHeight);
        glTexCoord2f(0,1); glVertex2f(0, windowHeight);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
}

/* --- CALLBACKS DE RENDERIZAÇÃO --- */

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    if(currentScene == SCENE_3D) {
        drawScene3D();
    } else {
        // Configura projeção ortográfica para as cenas 2D
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0, windowWidth, 0, windowHeight);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        if(currentScene == SCENE_2D_INPUT)
            drawScene2D();
        else if(currentScene == SCENE_2D_FINAL)
            drawScene3();
    }
    
    glutSwapBuffers();
}

/* --- CALLBACK DE REDIMENSIONAMENTO --- */
void reshape(int w, int h) {
    if(h == 0) h = 1;
    windowWidth = w;
    windowHeight = h;
    glViewport(0, 0, w, h);
}

/* --- CALLBACKS DE MOUSE (para cena 3D) --- */
void mouseButton(int button, int state, int x, int y) {
    if(currentScene != SCENE_3D) return;
    
    if(button == GLUT_LEFT_BUTTON) {
        if(state == GLUT_DOWN) {
            mouseDown = true;
            lastMouseX = x;
            lastMouseY = y;
        } else {
            mouseDown = false;
        }
    }
}

void mouseMotion(int x, int y) {
    if(currentScene != SCENE_3D) return;
    
    if(mouseDown) {
        int dx = x - lastMouseX;
        int dy = y - lastMouseY;
        rotateY += dx * 0.5f;
        rotateX += dy * 0.5f;
        lastMouseX = x;
        lastMouseY = y;
        glutPostRedisplay();
    }
}

/* --- CALLBACK DE TECLADO --- */
void keyboard(unsigned char key, int x, int y) {
    if(currentScene == SCENE_3D) {
        // Na cena 3D, a tecla ENTER (ASCII 13) alterna o estado de abertura
        if(key == 13) {
            opening = !opening;
        }
    } else if(currentScene == SCENE_2D_INPUT) {
        // Na cena 2D, processa o input de texto
        if(key == 13) {  // ENTER: verifica a palavra digitada
            if(strcmp(inputBuffer, "pikachu") == 0) {
                currentScene = SCENE_2D_FINAL;
            }
            // Opcional: limpar o buffer ou manter o texto
                inputIndex = 0;
                inputBuffer[0] = '\0';
        } else if(key == 8 || key == 127) { // Backspace
            if(inputIndex > 0) {
                inputIndex--;
                inputBuffer[inputIndex] = '\0';
            }
        } else if(key >= 32 && key <= 126) { // Caracteres imprimíveis
            if(inputIndex < (int)sizeof(inputBuffer)-1) {
                inputBuffer[inputIndex++] = key;
                inputBuffer[inputIndex] = '\0';
            }
        }
    } else if(currentScene == SCENE_2D_FINAL) {
        // Você pode definir outras interações na cena final, se desejar.
    }
    
    glutPostRedisplay();
}

/* --- FUNÇÃO DE TIMER --- */
void timer(int value) {
    if(currentScene == SCENE_3D) {
        // Atualiza o ângulo de abertura
        if(opening) {
            if(openAngle < 90.0f)
                openAngle += openSpeed;
            if(openAngle >= 90.0f)
                openAngle = 90.0f;
        } else {
            if(openAngle > 0.0f)
                openAngle -= openSpeed;
            if(openAngle < 0.0f)
                openAngle = 0.0f;
        }
        
        // Quando a pokebola estiver totalmente aberta, agenda a transição para a cena 2D
        if(openAngle == 90.0f && !sceneTransitioned) {
            sceneTransitioned = true;
            glutTimerFunc(500, transitionToScene2D, 0);
        }
    }
    
    glutPostRedisplay();
    glutTimerFunc(TIMER_INTERVAL, timer, 0);
}

/* --- FUNÇÃO MAIN --- */
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    // Modo de exibição: double buffer, RGB e z-buffer
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Pokebola + Interface 2D");
    
    glEnable(GL_DEPTH_TEST);
    initLighting();
    loadTextures();
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMotion);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(TIMER_INTERVAL, timer, 0);
    
    glutMainLoop();
    return 0;
}
