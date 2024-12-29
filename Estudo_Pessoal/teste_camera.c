#include <GL/glut.h>
#include <stdlib.h>

double angleX = 0.0; // Ângulo de rotação em torno do eixo X
double angleY = 0.0; // Ângulo de rotação em torno do eixo Y
double speed = 1.0;  // Velocidade de rotação

void drawCube() {
    glColor3f(1.0, 0.0, 0.0); // Define a cor do cubo (vermelho)
    glutWireCube(1.0);        // Desenha um cubo "wireframe"
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpa o buffer de cor e profundidade
    glLoadIdentity();

    // Move a "câmera" para trás
    glTranslatef(0.0, 0.0, -5.0);

    // Aplica a rotação na "câmera"
    glRotated(angleX, 1.0, 0.0, 0.0); // Rotação no eixo X
    glRotated(angleY, 0.0, 1.0, 0.0); // Rotação no eixo Y

    // Desenha o cubo no centro da cena
    drawCube();

    glutSwapBuffers(); // Troca os buffers para exibir o que foi renderizado
}

void timer(int value) {
    angleY += speed; // Incrementa o ângulo no eixo Y
    if (angleY >= 360.0) angleY -= 360.0; // Mantém o ângulo entre 0 e 360

    glutPostRedisplay();           // Solicita a redistribuição da tela
    glutTimerFunc(16, timer, 0);   // Define o próximo callback do timer
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'a': // Rotação para a esquerda
            angleY -= 5.0;
            break;
        case 'd': // Rotação para a direita
            angleY += 5.0;
            break;
        case 'w': // Rotação para cima
            angleX -= 5.0;
            break;
        case 's': // Rotação para baixo
            angleX += 5.0;
            break;
        case 27:  // Tecla ESC para sair
            exit(0);
            break;
    }

    glutPostRedisplay(); // Solicita a redistribuição da tela
}

void init() {
    glEnable(GL_DEPTH_TEST);                 // Habilita o teste de profundidade
    glClearColor(0.0, 0.0, 0.0, 1.0);        // Define a cor de fundo como preto
    glMatrixMode(GL_PROJECTION);             // Configura o modo de projeção
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 100.0);   // Define uma perspectiva 3D
    glMatrixMode(GL_MODELVIEW);              // Retorna ao modo de modelagem
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Rotação da Câmera com glRotated");

    init();

    glutDisplayFunc(display);
    glutTimerFunc(16, timer, 0);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
