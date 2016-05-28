//
//  Tile.cpp
//  edgefest2016
//
//  Created by physiocheck on 14/05/2016.
//  Copyright © 2016 Alsace Digitale. All rights reserved.
//

#include "Tile.hpp"

#include <iostream>

Tile::Tile(float posx, float posy) {
    tile.setSize(sf::Vector2f((GameLoop::Instance().getWindow().getSize().x - 2 * TILE_OUTLINE) / 4,
                                  GameLoop::Instance().getWindow().getSize().y / TILE_NUMBER - TILE_OUTLINE * 4));
    x = posx;
    y = posy;
    randomHorizontalPosition();
}

uint8_t Tile::randomHorizontalPosition() {
    horizontalPosition = rand() % 4;
    x = TILE_OUTLINE + ((GameLoop::Instance().getWindow().getSize().x - 2 * TILE_OUTLINE) / 4) * horizontalPosition;
    tile.setFillColor(sf::Color(255, 0, 0));
    tile.setPosition(x, y);
    clicked = false;
}

uint8_t Tile::getHorizontalPosition() {
    return horizontalPosition;
}

void Tile::move(float elapsedTime) {
    y += elapsedTime * TILE_SPEED;
    
    uint32_t winHeight = GameLoop::Instance().getWindow().getSize().y;
    
    if (y > winHeight) {
        y = (TILE_OUTLINE * 1.f + (TILE_NUMBER - 1) * winHeight / TILE_NUMBER) - winHeight + y - winHeight;
        if (!clicked) {
            exit(0);
        }
        randomHorizontalPosition();
    }
    
    tile.setPosition(x, y);
}

void Tile::draw() {
    GameLoop::Instance().getWindow().draw(tile);
}

bool Tile::checkKeyPressed(int pos) {
    if (pos != horizontalPosition || clicked) {
        exit(0);
    } else {
        tile.setFillColor(sf::Color(150, 150, 255));
    }
    clicked = true;
}

float Tile::getYPosition() {
    return y;
}
