//
//  utils.cpp
//  ChessGame
//
//  Created by Dibash Chhetri on 1/28/12.
//  Copyright (c) 2012 University of Connecticut. All rights reserved.
//

#include "utils.h"

namespace ChessGame {
    namespace util
    {
        //returns true if [min <= target <= max]
        template<typename T>
        bool isBetween(T target, T min, T max){
            return min <= target && target <= max;
        }
        
        //returns true if (x,y) is inside sprite fiure
        bool contains(float x, float y, const sf::Sprite& sprite)
        {
            
            float minX = sprite.GetPosition().x;
            float minY = sprite.GetPosition().y;
            
            float maxX = sprite.GetPosition().x + sprite.GetSize().x;
            float maxY = sprite.GetPosition().y + sprite.GetSize().y;
            
            //return if x and y falls in between sprite's range
            return isBetween(x,minX, maxX) && isBetween(y,minY, maxY);
        }
    }
}
