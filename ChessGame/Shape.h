//
//  Shape.h
//  C++
//
//  Created by Dibash Chhetri on 12/21/11.
//  Copyright (c) 2011 University of Connecticut. All rights reserved.
//

#ifndef C___Shape_h
#define C___Shape_h

#include <SFML/System/Vector3.hpp>
#include "Utility.h"

namespace ChessGame {        

    struct IShape : public Cloneable
    {
        //draws the shape
        virtual void draw()const = 0;
        
        //sets the center position of the shape
        virtual void setPosition(float x, float y, float z)=0;
        virtual void setPosition(const sf::Vector3f& position)=0;
        
        //sets the color of the shape
        virtual void setColor(const Color& color)=0;
        //sets the size of the shape
        virtual void setSize(const Dimension& dimension)=0;
        
        virtual const Dimension& getSize()const=0;
        virtual const Color&     getColor()const=0;
        virtual const sf::Vector3f&   getPosition()const=0;
        
        IShape * clone()const = 0;
        
        virtual ~IShape(){}
    };
}
#endif
