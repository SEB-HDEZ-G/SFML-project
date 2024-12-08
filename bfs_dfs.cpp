#include <SFML/Graphics.hpp>
#include "Maze.h"

int main() {
    int width = 21;
    int height = 21;
    int cellSize = 20;

    sf::RenderWindow window(sf::VideoMode(width * cellSize, height * cellSize), "Maze Solver");

    Maze maze(width, height, cellSize);
    maze.generateMaze();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        maze.draw(window);
        window.display();

      

        if(maze.solveMazeBFS(window)){
             sf::sleep(sf::seconds(2));
             break;
        }
    }

    return 0;
}
