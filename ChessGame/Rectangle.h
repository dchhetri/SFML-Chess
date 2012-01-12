//
//  Rectangle.h
//  C++
//
//  Created by Dibash Chhetri on 12/21/11.
//  Copyright (c) 2011 University of Connecticut. All rights reserved.
//

#ifndef C___Rectangle_h
#define C___Rectangle_h

#include "Shape.h"
#include <SFML/System/Vector3.hpp>
#include "util.h"

namespace ChessGame {
    
class Rectangle : public IShape {
private:
    Dimension dimension;
    sf::Vector3<float> position;
    Color color;
public:
    //constructs a rectangle at centered at position(0,0) with size(0,0)
    Rectangle();
    //creates a unit rectangle centered at (x,y,z)
    Rectangle(float x, float y, float z = 0);
    //constructs a rectangle centered at position(x,y,z) whose size is given my width and height
    Rectangle(float x, float y, float z, 
              Dimension::DimensionType width,
              Dimension::DimensionType height,
              Dimension::DimensionType depth = 0,
              Color color = Color::WHITE);
    //constructs a rectangle centered at position 'position' with size 'dimension]
    Rectangle(const sf::Vector3<float>& position, const Dimension& dimension);
    //draws the object
    void draw()const;
    
    //sets the new center position
    void setPosition(float x, float y, float z);
    void setPosition(const sf::Vector3f& position);
    //sets the new color of current rectangle
    void setColor(const Color& color);
    //sets a new size for the rectangle
    void setSize(const Dimension& dimension);
    //retrives current dimension
    const Dimension& getSize()const;
    //retrives current color
    const Color& getColor()const;
    //retrives current position
    const sf::Vector3f& getPosition()const;
    //clones current rectangle
    Rectangle* clone()const;
};

}
#endif
