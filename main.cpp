#include <GLFW/glfw3.h>
#include <vector>
#include <cstdlib>

#include"Cell.h"
#include"Game.h"


Game game;
bool isPaused = false;
double updateTime = 0.1; // Temps d'intervalle pour l'actualisation en secondes
const int width = 800;
const int height = 600;
const int scale = 10; // Echelle des cases de la grille

// Définition des zones des boutons
const int pauseX = 700;
const int pauseY = 550;
const int pauseWIDTH = 80;
const int pauseHEIGHT = 30;

const int resetX = 600;
const int resetY = 550;
const int resetWIDTH = 80;
const int resetHEIGHT = 30;

const int speedX = 500;
const int speedY = 550;
const int speedWIDTH = 80;
const int speedHEIGHT = 30;

const int slowX = 400;
const int slowY = 550;
const int slowWIDTH = 80;
const int slowHEIGHT = 30;

void draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    game.draw();


    // DESSIN DES BOUTONS
    // PAUSE
    if (isPaused) {
        glColor3f(1.0f, 0.0f, 0.0f); // Rouge si en pause
    }
    else {
        glColor3f(0.0f, 1.0f, 0.0f); // Vert si en cours
    }
    glBegin(GL_QUADS);
    glVertex2f(pauseX, pauseY);
    glVertex2f(pauseX + pauseWIDTH, pauseY);
    glVertex2f(pauseX + pauseWIDTH, pauseY + pauseHEIGHT);
    glVertex2f(pauseX, pauseY + pauseHEIGHT);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    if (isPaused) { // Logo play
        glBegin(GL_TRIANGLES);
        glVertex2f(pauseX + 30, pauseY + 5);
        glVertex2f(pauseX + 50, pauseY + 15);
        glVertex2f(pauseX + 30, pauseY + 25);
        glEnd();
    }
    else { // Logo pause
        glBegin(GL_QUADS);
        glVertex2f(pauseX + 25, pauseY + 5);
        glVertex2f(pauseX + 35, pauseY + 5);
        glVertex2f(pauseX + 35, pauseY + 25);
        glVertex2f(pauseX + 25, pauseY + 25);

        glVertex2f(pauseX + 45, pauseY + 5);
        glVertex2f(pauseX + 55, pauseY + 5);
        glVertex2f(pauseX + 55, pauseY + 25);
        glVertex2f(pauseX + 45, pauseY + 25);
        glEnd();
    }

    // RESET
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(resetX, resetY);
    glVertex2f(resetX + resetWIDTH, resetY);
    glVertex2f(resetX + resetWIDTH, resetY + resetHEIGHT);
    glVertex2f(resetX, resetY + resetHEIGHT);
    glEnd();

    
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex2f(resetX + 20, resetY + 10);
    glVertex2f(resetX + 60, resetY + 10);
    glVertex2f(resetX + 60, resetY + 10);
    glVertex2f(resetX + 60, resetY + 20);
    glVertex2f(resetX + 60, resetY + 20);
    glVertex2f(resetX + 20, resetY + 20);
    glVertex2f(resetX + 20, resetY + 20);
    glVertex2f(resetX + 20, resetY + 10);
    glEnd();

    // SPEED
    glColor3f(0.0f, 1.0f, 1.0f); // Cyan pour augmenter la vitesse
    glBegin(GL_QUADS);
    glVertex2f(speedX, speedY);
    glVertex2f(speedX + speedWIDTH, speedY);
    glVertex2f(speedX + speedWIDTH, speedY + speedHEIGHT);
    glVertex2f(speedX, speedY + speedHEIGHT);
    glEnd();

    // SLOW
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(speedX + 30, speedY + 5);
    glVertex2f(speedX + 50, speedY + 15);
    glVertex2f(speedX + 30, speedY + 25);
    glEnd();

    // Dessiner le bouton pour diminuer la vitesse
    glColor3f(1.0f, 0.0f, 1.0f); // Magenta pour diminuer la vitesse
    glBegin(GL_QUADS);
    glVertex2f(slowX, slowY);
    glVertex2f(slowX + slowWIDTH, slowY);
    glVertex2f(slowX + slowWIDTH, slowY + slowHEIGHT);
    glVertex2f(slowX, slowY + slowHEIGHT);
    glEnd();

    // Dessiner le symbole pour diminuer la vitesse
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(slowX + 30, slowY + 25);
    glVertex2f(slowX + 50, slowY + 15);
    glVertex2f(slowX + 30, slowY + 5);
    glEnd();

    glfwSwapBuffers(glfwGetCurrentContext());
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        // Vérifie si le clic est dans la zone du bouton de pause
        if (xpos >= pauseX && xpos <= pauseX + pauseWIDTH &&
            ypos >= pauseY && ypos <= pauseY + pauseHEIGHT) {
            isPaused = !isPaused; // On passe de en cours à pause et inversement
        }
        else if (xpos >= resetX && xpos <= resetX + resetWIDTH &&
            ypos >= resetY && ypos <= resetY + resetHEIGHT) {
            game.randomize(); // Reset du jeu
        }
        else if (xpos >= speedX && xpos <= speedX + speedWIDTH &&
            ypos >= speedY && ypos <= speedY + speedHEIGHT) {
            if (updateTime > 0.1) {
                updateTime -= 0.1; // Diminue l'intervale d'actualisation
            }
        }
        else if (xpos >= slowX && xpos <= slowX + slowWIDTH &&
            ypos >= slowY && ypos <= slowY + slowHEIGHT) {
            updateTime += 0.1; // Augmente l'intervale d'actualisation
        }
    }
}

int main(void) {
    if (!glfwInit())
        return -1;

    GLFWwindow* window = glfwCreateWindow(width, height, "Jeu de la vie", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glOrtho(0, width, height, 0, 0, 1);

    game.randomize();

    glfwSetMouseButtonCallback(window, mouse_button_callback);

    double previousTime = glfwGetTime();

    while (!glfwWindowShouldClose(window)) {
        double currentTime = glfwGetTime();
        if (!isPaused && currentTime - previousTime >= updateTime) {
            game.update();
            previousTime = currentTime;
        }

        draw();
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}