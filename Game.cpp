#include "Game.h"
#include <cstdlib> // Pour la fonction rand()
#include <GLFW/glfw3.h>

const int WIDTH = 800;
const int HEIGHT = 600;
const int CELL_SIZE = 10;

Game::Game() {
    grid.resize(WIDTH / CELL_SIZE, std::vector<Cell>(HEIGHT / CELL_SIZE));
}

void Game::randomize() {
    for (int i = 0; i < WIDTH / CELL_SIZE; ++i) {
        for (int j = 0; j < HEIGHT / CELL_SIZE; ++j) {
            grid[i][j].alive = rand() % 2 == 0;
        }
    }
}

void Game::reset() {
    for (int i = 0; i < WIDTH / CELL_SIZE; ++i) {
        for (int j = 0; j < HEIGHT / CELL_SIZE; ++j) {
            grid[i][j].alive = false;
        }
    }
}

void Game::update() {
    std::vector<std::vector<Cell>> newGrid = grid;
    for (int i = 0; i < WIDTH / CELL_SIZE; ++i) {
        for (int j = 0; j < HEIGHT / CELL_SIZE; ++j) {
            int aliveNeighbors = countAliveNeighbors(i, j);
            if (grid[i][j].alive) {
                if (aliveNeighbors < 2 || aliveNeighbors > 3) {
                    newGrid[i][j].alive = false; // Mort par sous-population ou surpopulation
                }
            }
            else {
                if (aliveNeighbors == 3) {
                    newGrid[i][j].alive = true; // Naissance
                }
            }
        }
    }
    grid = newGrid;
}

int Game::countAliveNeighbors(int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            int neighborX = (x + i + WIDTH / CELL_SIZE) % (WIDTH / CELL_SIZE);
            int neighborY = (y + j + HEIGHT / CELL_SIZE) % (HEIGHT / CELL_SIZE);
            if (grid[neighborX][neighborY].alive) {
                ++count;
            }
        }
    }
    if (grid[x][y].alive) {
        --count;
    }
    return count;
}

void Game::draw() {
    for (int i = 0; i < WIDTH / CELL_SIZE; ++i) {
        for (int j = 0; j < HEIGHT / CELL_SIZE; ++j) {
            grid[i][j].draw(i * CELL_SIZE, j * CELL_SIZE);
        }
    }
}
