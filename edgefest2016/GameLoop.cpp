//
//  GameLoop.cpp
//  edgefest2016
//
//  Created by physiocheck on 14/05/2016.
//  Copyright © 2016 Alsace Digitale. All rights reserved.
//

#include "GameLoop.hpp"
#include <chrono>
#include <thread>
#include <iostream>

GameLoop& GameLoop::Instance() {
    static GameLoop instance;
    return instance;
}

GameLoop::GameLoop() :
    window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE)
{
}

void GameLoop::init() {
    srand(time(NULL));
    
    for (int i = 0 ; i < TILE_NUMBER + 1 ; ++i) {
        Tile* tile = new Tile(TILE_OUTLINE, (TILE_OUTLINE * 2.f + i *
                                             window.getSize().y / TILE_NUMBER) - window.getSize().y);
        tiles.push_back(tile);
    }
    
    grid = new Grid();
}

void GameLoop::run() {
    clock.restart();
    while (window.isOpen()) {
        sf::Event event;
        
        bool btn[4] = { false };
        
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            btn[0] |= event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num1;
            btn[1] |= event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num2;
            btn[2] |= event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num3;
            btn[3] |= event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num4;
        }
        
        window.clear();
        sf::Time elapsedTime = clock.getElapsedTime();
        clock.restart();
        
        Tile* last = NULL;
        
        for (int i = 0 ; i < TILE_NUMBER + 1 ; ++i) {
            Tile* tile = tiles[i];
            
            tile->move(elapsedTime.asSeconds());
            tile->draw();
            
            if ((tile->getYPosition() + window.getSize().y / TILE_NUMBER) <= window.getSize().y && (tile->getYPosition() + window.getSize().y / TILE_NUMBER) >= window.getSize().y - window.getSize().y / TILE_NUMBER) {
                last = tile;
            }
        }
        
        for (int i = 0 ; i < 4 ; ++i) {
            if (btn[i]) {
                if (last == NULL) {
                    exit(0);
                } else {
                    last->checkKeyPressed(i);
                }
            }
        }
        
        grid->draw();
        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / FRAMERATE - elapsedTime.asMilliseconds()));
    }
}

sf::RenderWindow& GameLoop::getWindow() {
    return window;
}
