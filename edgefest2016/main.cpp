#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <iostream>
#include <vector>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TILE_NUMBER 6
#define TILE_OUTLINE 3
#define TILE_SPEED 400.f

class Tile {
public:
    Tile(sf::RenderWindow& window, float posx, float posy) :
        window(window),
        tile(sf::Vector2f((window.getSize().x - 2 * TILE_OUTLINE) / 4, window.getSize().y / TILE_NUMBER - TILE_OUTLINE * 4)),
        x(posx),
        y(posy)
    {
        tile.setPosition(posx, posy);
        tile.setFillColor(sf::Color(255, 0, 0));
        setHorizontalPosition();
    }
    
    void setHorizontalPosition() {
        xpos = rand() % 4;
        x = TILE_OUTLINE + ((window.getSize().x - 2 * TILE_OUTLINE) / 4) * xpos;
        tile.setPosition(x, y);
    }
    
    void move(float elapsedTime) {
        y += elapsedTime * TILE_SPEED;
        
        if (y > window.getSize().y) {
            y = (TILE_OUTLINE * 1.f + (TILE_NUMBER - 1) * window.getSize().y / TILE_NUMBER) - window.getSize().y + y - window.getSize().y;
            setHorizontalPosition();
        }
        
        tile.setPosition(x, y);
    }
    
    void draw() {
        window.draw(tile);
    }

private:
    sf::RenderWindow& window;
    sf::RectangleShape tile;
    float x, y;
    uint8_t xpos;
};

int main(int, char const**) {
    sf::RenderWindow window(sf::VideoMode(300, 1080), "SFML window");
    uint32_t width = window.getSize().x;
    uint32_t height = window.getSize().y;
    srand (time(NULL));

    sf::RectangleShape grid(sf::Vector2f(width - TILE_OUTLINE * 2, height / TILE_NUMBER - TILE_OUTLINE * 4));
    grid.setPosition(TILE_OUTLINE, TILE_OUTLINE);
    grid.setFillColor(sf::Color(0, 0, 0, 0));
    grid.setOutlineColor(sf::Color(255, 255, 255, 255));
    grid.setOutlineThickness(TILE_OUTLINE);
    
    std::vector<Tile*> tiles;
    for (int i = 0 ; i < TILE_NUMBER + 1 ; ++i) {
        Tile* tile = new Tile(window, TILE_OUTLINE, (TILE_OUTLINE * 2.f + i * height / TILE_NUMBER) - height);
        tiles.push_back(tile);
    }
    
    sf::Clock clock;
    clock.restart();
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }

        window.clear();
        sf::Time elapsedTime = clock.getElapsedTime();
        clock.restart();
        
        for (int i = 0 ; i < TILE_NUMBER + 1 ; ++i) {
            Tile* tile = tiles[i];
            
            tile->move(elapsedTime.asSeconds());
            tile->draw();
        }

        for (int i = 0 ; i < TILE_NUMBER ; ++i) {
            grid.setPosition(TILE_OUTLINE, TILE_OUTLINE * 2 + i * height / TILE_NUMBER);
            window.draw(grid);
        }

        window.display();
    }

    return EXIT_SUCCESS;
}
