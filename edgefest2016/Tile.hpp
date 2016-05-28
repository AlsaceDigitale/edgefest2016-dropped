//
//  Tile.hpp
//  edgefest2016
//
//  Created by physiocheck on 14/05/2016.
//  Copyright © 2016 Alsace Digitale. All rights reserved.
//

#ifndef Tile_hpp
#define Tile_hpp

#include <SFML/Graphics.hpp>
#include <cstdint>

class Tile;

#include "configs.hpp"
#include "Gameloop.hpp"

class Tile {
public:
    Tile(float posx, float posy);
    
    uint8_t randomHorizontalPosition();
    uint8_t getHorizontalPosition();
    
    void move(float);
    void draw();
    
    bool checkKeyPressed(int);
    
    float getYPosition();
    
private:
    sf::RectangleShape tile;
    float x, y;
    uint8_t horizontalPosition;
    bool clicked;
};

#endif /* Tile_hpp */
