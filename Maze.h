#ifndef MAZE_H
#define MAZE_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>

class Maze {
public:
    Maze(int width, int height, int cellSize);
    void generateMaze();
    bool solveMazeDFS(sf::RenderWindow& window); //DFS
    bool solveMazeBFS(sf::RenderWindow& window);  // Método para resolver con BFS
    void draw(sf::RenderWindow& window);

private:
    enum Cell { WALL, PATH, VISITED, START, END, SOLUTION };

    struct Position {
        int x, y;
        Position(int x, int y) : x(x), y(y) {}
    };

    int width, height, cellSize;
    std::vector<std::vector<Cell>> grid;
    Position start, end;

    void generateDFS(Position pos);
    bool solveDFS(Position pos, sf::RenderWindow& window);  // Declaración de la función solveDFS
    bool solveBFS(sf::RenderWindow& window);
    std::vector<Position> getNeighbors(const Position& pos);
};

#endif
