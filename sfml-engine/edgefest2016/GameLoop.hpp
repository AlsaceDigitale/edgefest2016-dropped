//
//  GameLoop.hpp
//  edgefest2016
//
//  Created by physiocheck on 14/05/2016.
//  Copyright © 2016 Alsace Digitale. All rights reserved.
//

#ifndef GameLoop_hpp
#define GameLoop_hpp

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

#include <vector>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

class GameLoop;

#include "configs.hpp"
#include "Tile.hpp"
#include "Grid.hpp"

class GameLoop {
public:
    static GameLoop& Instance();
    
    void init();
    void run();
    
    sf::RenderWindow& getWindow();
    
private:
    GameLoop();
    
    sf::RenderWindow window;
    std::vector<Tile*> tiles;
    Grid* grid;
    sf::Clock clock;
};

#endif /* GameLoop_hpp */
