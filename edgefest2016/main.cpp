#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

#define TILE_NUMBER 12
#define TILE_OUTLINE 3
#define TILE_SPEED 200.f

int main(int, char const**) {
    sf::RenderWindow window(sf::VideoMode(300, 1080), "SFML window");
    uint32_t width = window.getSize().x;
    uint32_t height = window.getSize().y;

    sf::RectangleShape grid(sf::Vector2f(width - TILE_OUTLINE * 2, height / TILE_NUMBER - TILE_OUTLINE * 4));
    grid.setPosition(TILE_OUTLINE, TILE_OUTLINE);
    grid.setFillColor(sf::Color(0, 0, 0, 0));
    grid.setOutlineColor(sf::Color(255, 255, 255, 255));
    grid.setOutlineThickness(TILE_OUTLINE);
    
    sf::RectangleShape tile(sf::Vector2f((width - 2 * TILE_OUTLINE) / 4, height / TILE_NUMBER - TILE_OUTLINE * 4));
    tile.setPosition(TILE_OUTLINE, TILE_OUTLINE * 2);
    tile.setFillColor(sf::Color(255, 0, 0));
    
    sf::Clock clock;
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
        
        tile.setPosition(tile.getPosition().x, tile.getPosition().y + (elapsedTime.asSeconds() * TILE_SPEED));
        window.draw(tile);

        for (int i = 0 ; i < TILE_NUMBER ; ++i) {
            grid.setPosition(TILE_OUTLINE, TILE_OUTLINE * 2 + i * height / TILE_NUMBER);
            window.draw(grid);
        }

        window.display();
    }

    return EXIT_SUCCESS;
}
