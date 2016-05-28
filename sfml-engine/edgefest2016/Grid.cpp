//
//  Grid.cpp
//  edgefest2016
//
//  Created by physiocheck on 14/05/2016.
//  Copyright © 2016 Alsace Digitale. All rights reserved.
//

#include "Grid.hpp"

Grid::Grid() :
    gridElement(sf::Vector2f(GameLoop::Instance().getWindow().getSize().x - TILE_OUTLINE * 2,
                             GameLoop::Instance().getWindow().getSize().y / TILE_NUMBER - TILE_OUTLINE * 4))
{
    gridElement.setPosition(TILE_OUTLINE, TILE_OUTLINE);
    gridElement.setFillColor(sf::Color(0, 0, 0, 0));
    gridElement.setOutlineColor(sf::Color(255, 255, 255));
    gridElement.setOutlineThickness(TILE_OUTLINE);
}

void Grid::draw() {
    for (int i = 0 ; i < TILE_NUMBER ; ++i) {
        gridElement.setPosition(TILE_OUTLINE, TILE_OUTLINE * 2 + i *
                                (GameLoop::Instance().getWindow().getSize().y) / TILE_NUMBER);
        GameLoop::Instance().getWindow().draw(gridElement);
    }
}
