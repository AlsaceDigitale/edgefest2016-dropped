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
#include <sstream>

#include "ResourcePath.hpp"

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
    
    score = 0;
}

void GameLoop::restart() {
    srand(time(NULL));
    
    tiles.clear();
    for (int i = 0 ; i < TILE_NUMBER + 1 ; ++i) {
        Tile* tile = new Tile(TILE_OUTLINE, (TILE_OUTLINE * 2.f + i *
                                             window.getSize().y / TILE_NUMBER) - window.getSize().y);
        tiles.push_back(tile);
    }
    
    delete grid;
    grid = new Grid();
    
    score = 0;
}

void GameLoop::run() {
    clock.restart();
    
    std::stringstream ss;
    
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf"))
        return EXIT_FAILURE;
    
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(40);
    scoreText.setPosition(0, 0);
    scoreText.setColor(sf::Color(255, 0, 0));
    
    ss << score;
    scoreText.setString(ss.str());

    while (window.isOpen()) {
        sf::Event event;
        
        bool btn[5] = { false };
        
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
            btn[4] |= event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num5;
            
            /*btn[0] |= event.type == sf::Event::JoystickButtonPressed && event.joystickButton.button == 0;
            btn[1] |= event.type == sf::Event::JoystickButtonPressed && event.joystickButton.button == 14;
            btn[2] |= event.type == sf::Event::JoystickButtonPressed && event.joystickButton.button == 3;*/

            if (TILE_WIDTH == 3) {
                btn[0] |= event.type == sf::Event::JoystickButtonPressed && event.joystickButton.button == 15;
                btn[1] |= event.type == sf::Event::JoystickButtonPressed && event.joystickButton.button == 12;
                btn[2] |= event.type == sf::Event::JoystickButtonPressed && event.joystickButton.button == 13;
            } else if (TILE_WIDTH == 5) {
                btn[0] |= event.type == sf::Event::JoystickButtonPressed && event.joystickButton.button == 15;
                btn[1] |= event.type == sf::Event::JoystickButtonPressed && event.joystickButton.button == 2;
                btn[2] |= event.type == sf::Event::JoystickButtonPressed && event.joystickButton.button == 12;
                btn[3] |= event.type == sf::Event::JoystickButtonPressed && event.joystickButton.button == 1;
                btn[4] |= event.type == sf::Event::JoystickButtonPressed && event.joystickButton.button == 13;
            }
            
            
            if (event.type == sf::Event::JoystickButtonPressed)
                std::cout << "Button " << event.joystickButton.button << " pressed." << std::endl;
        }
        
        window.clear();
        sf::Time elapsedTime = clock.getElapsedTime();
        clock.restart();
        
        Tile* last = NULL;
        
        for (int i = 0 ; i < TILE_NUMBER + 1 ; ++i) {
            Tile* tile = tiles[i];
            
            tile->move(elapsedTime.asSeconds());
            tile->draw();
            
            if ((tile->getYPosition() + window.getSize().y / TILE_NUMBER) <= window.getSize().y &&
                (tile->getYPosition() + window.getSize().y / TILE_NUMBER) >= window.getSize().y - window.getSize().y / TILE_NUMBER) {
                last = tile;
            }
            
            if ((tile->getYPosition()) <= window.getSize().y &&
                (tile->getYPosition()) >= window.getSize().y - window.getSize().y / TILE_NUMBER &&
                !tile->isClicked()) {
                tile->missed();
            }
        }
        
        for (int i = 0 ; i < TILE_WIDTH ; ++i) {
            if (btn[i]) {
                if (last == NULL) {
                    //GameLoop::Instance().restart();
                } else {
                    last->checkKeyPressed(i);
                }
            }
        }
        
        grid->draw();

        ss.str("");
        ss << score;
        scoreText.setString(ss.str());
        window.draw(scoreText);
        
        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / FRAMERATE - elapsedTime.asMilliseconds()));
    }
}

sf::RenderWindow& GameLoop::getWindow() {
    return window;
}

void GameLoop::incrementScore() {
    score += SCORE_INCR;
}

void GameLoop::decrementScore() {
    score -= 5 * SCORE_INCR;
}
