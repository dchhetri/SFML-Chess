//
//  utils.h
//  ChessGame
//
//  Created by Dibash Chhetri on 1/28/12.
//  Copyright (c) 2012 University of Connecticut. All rights reserved.
//

#ifndef ChessGame_utils_h
#define ChessGame_utils_h

#include <SFML/Graphics/Sprite.hpp>

namespace ChessGame 
{
    namespace util
    {   
        //returns true if (x,y) is inside sprite fiure
        bool contains(float x, float y, const sf::Sprite& sprite);
    }
}

#endif
