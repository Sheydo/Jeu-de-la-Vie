#include "Cell.h"
#include <GLFW/glfw3.h>

const int CELL_SIZE = 10;

Cell::Cell() : alive(false) {}

void Cell::draw(int x, int y) {
    if (alive) {
        glColor3f(1.0f, 1.0f, 1.0f); // Blanc si vivant
    }
    else {
        glColor3f(0.0f, 0.0f, 0.0f); // Noir si mort
    }
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + CELL_SIZE, y);
    glVertex2f(x + CELL_SIZE, y + CELL_SIZE);
    glVertex2f(x, y + CELL_SIZE);
    glEnd();
}
