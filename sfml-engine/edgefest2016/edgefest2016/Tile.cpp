//
//  Tile.cpp
//  edgefest2016
//
//  Created by physiocheck on 14/05/2016.
//  Copyright © 2016 Alsace Digitale. All rights reserved.
//

#include "Tile.hpp"
#include "configs.hpp"

#include <iostream>

Tile::Tile(float posx, float posy) {
    tile.setSize(sf::Vector2f((GameLoop::Instance().getWindow().getSize().x - 2 * TILE_OUTLINE) / TILE_WIDTH,
                                  GameLoop::Instance().getWindow().getSize().y / TILE_NUMBER - TILE_OUTLINE * 4));
    x = posx;
    y = posy;
    randomHorizontalPosition();
}

uint8_t Tile::randomHorizontalPosition() {
    horizontalPosition = rand() % TILE_WIDTH;
    x = TILE_OUTLINE + ((GameLoop::Instance().getWindow().getSize().x - 2 * TILE_OUTLINE) / TILE_WIDTH) * horizontalPosition;
    tile.setFillColor(sf::Color(255, 255, 255));
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
            missed();
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
        //GameLoop::Instance().restart();
    } else {
        tile.setFillColor(sf::Color(150, 255, 150));
        clicked = true;
        GameLoop::Instance().incrementScore();
    }
}

void Tile::missed() {
    if (!clicked) {
        tile.setFillColor(sf::Color(255, 150, 150));
        GameLoop::Instance().decrementScore();
        clicked = true;
    }
}

float Tile::getYPosition() {
    return y;
}

bool Tile::isClicked() {
    return clicked;
}
