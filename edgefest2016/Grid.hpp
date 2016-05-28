//
//  Grid.hpp
//  edgefest2016
//
//  Created by physiocheck on 14/05/2016.
//  Copyright © 2016 Alsace Digitale. All rights reserved.
//

#ifndef Grid_hpp
#define Grid_hpp

#include <SFML/Graphics.hpp>

class Grid;

#include "Gameloop.hpp"

class Grid {
public:
    Grid();

    void draw();

private:
    sf::RectangleShape gridElement;
};

#endif /* Grid_hpp */
