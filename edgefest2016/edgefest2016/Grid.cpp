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
                             BAR_SIZE))
{
    gridElement.setPosition(TILE_OUTLINE, TILE_OUTLINE);
    gridElement.setFillColor(sf::Color(255, 0, 0));
}

void Grid::draw() {
    for (int i = 0 ; i < TILE_NUMBER ; ++i) {
        if (i == TILE_NUMBER - 1) {
            gridElement.setPosition(TILE_OUTLINE, TILE_OUTLINE * 2 + i *
                                    (GameLoop::Instance().getWindow().getSize().y) / TILE_NUMBER - TILE_OUTLINE * 2);
            GameLoop::Instance().getWindow().draw(gridElement);
        }
    }
}
