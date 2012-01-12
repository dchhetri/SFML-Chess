//
//  Rectangle.cpp
//  C++
//
//  Created by Dibash Chhetri on 12/21/11.
//  Copyright (c) 2011 University of Connecticut. All rights reserved.
//

#include "Rectangle.h"
#include <OpenGL/OpenGL.h>

namespace ChessGame 
{

    Rectangle::Rectangle(){}

    Rectangle::Rectangle(float x, float y, float z)
    : position(x,y,z), dimension(1,1){}

    Rectangle::Rectangle(float x, float y, float z, 
                         Dimension::DimensionType w, 
                         Dimension::DimensionType h, 
                         Dimension::DimensionType d,
                         Color color)
                        : position(x,y,z), dimension(w,h,d), color(color)
    {
    }
    Rectangle::Rectangle(const sf::Vector3f& position, const Dimension& d)
    : position(position), dimension(d){}

    void Rectangle::draw()const{
      
        float width = dimension.getWidth();
        float height = dimension.getHeight();
        float x = position.x;
        float y = position.y;
        float z = position.z;
        
        glColor3f(color[Color::RED_COMPONENT],color[Color::GREEN_COMPONENT], color[Color::BLUE_COMPONENT]);  
        glBegin(GL_QUADS);
            glVertex3f(x - width/2,y - height/2,z);
            glVertex3f(x - width/2,y + height/2,z);
            glVertex3f(x + width/2,y + height/2,z);
            glVertex3f(x + width/2,y - height/2,z);
        glEnd();
    }

    void Rectangle::setPosition(float x, float y, float z){
        position = sf::Vector3f(x,y,z);
    }
    void Rectangle::setPosition(const sf::Vector3f& position){
        this->position = position;
    }
    void Rectangle::setColor(const Color &color){
        this->color = color;   
    }

    void Rectangle::setSize(const Dimension& dimension){
        this->dimension = dimension;
    }
    const Dimension& Rectangle::getSize()const{
        return dimension;
    }
    const Color& Rectangle::getColor()const{
        return this->color;
    }
    const sf::Vector3f& Rectangle::getPosition()const{
        return this->position;
    }

    Rectangle* Rectangle::clone()const{
        return new Rectangle(*this);
    }
}