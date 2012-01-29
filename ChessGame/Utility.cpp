//
//  utils.cpp
//  C++
//
//  Created by Dibash Chhetri on 12/21/11.
//  Copyright (c) 2011 University of Connecticut. All rights reserved.
//

#include "Utility.h"
#include <OpenGL/glu.h>
#include <cstdlib>

namespace ChessGame 
{
 
    const Color Color::RED = Color(1.0f,0.0f,0.0f);
    const Color Color::GREEN = Color(0.0f,1.0f,0.0f);
    const Color Color::BLUE = Color(0.0f,0.0f,1.0f);
    const Color Color::YELLOW = Color(1.0f,0.0f,0.0f);
    const Color Color::WHITE = Color(1.0f,1.0f,1.0f);
    const Color Color::BLACK = Color(0.0f,0.0f,0.0f);
    const Color Color::GRAY = Color(0.3f,0.3f,0.3f);
    Color::Color(){
        color[0] = color[1] = color[2] = color[3] = 1.0f;
    }
    Color::Color(float r, float g, float b, float alph){
        color[0] = r;
        color[1] = g;
        color[2] = b;
        color[3] = alph;
    }

    float Color::redComponent()const{
        return color[RED_COMPONENT];
    }
    float Color::greenComponent()const{
        return color[GREEN_COMPONENT];
    }
    float Color::blueComponent()const{
        return color[BLUE_COMPONENT];
    }

    Color::Color(float color[3]){
        for(int i = 0; i < 4; ++i){
            this->color[i] = color[i];
        }
    }
    void Color::darken(){
        scale(0.1f);
    }
    void Color::lighten(){ 
        scale(1.1f);
    }
    void Color::scale(float factor){
        for(int i = 0; i < 3; ++i){
            color[i] *= factor;
        }
    }
    float Color::operator[](Color::Component c){
        return color[c];
    }
    const float& Color::operator[](const Color::Component c)const{
        return color[c];
    }


    Dimension::Dimension(): width(0), height(0), depth(0){}
    Dimension::Dimension(Dimension::DimensionType width, 
                         Dimension::DimensionType height,
                         Dimension::DimensionType depth )
    : width(width), height(height), depth(depth){}

    void Dimension::setWidth(Dimension::DimensionType width){
        this->width = width;
    }
    void Dimension::setHeight(Dimension::DimensionType height){
        this->height = height;
    }
    void Dimension::setDepth(DimensionType depth){
        this->depth = depth;
    }
    Dimension::DimensionType Dimension::getWidth()const{
        return this->width;
    }
    Dimension::DimensionType Dimension::getHeight()const{
        return this->height;
    }
    Dimension::DimensionType Dimension::getDepth()const{
        return this->depth;
    }
    void Dimension::scale(float factor){
        width *= factor;
        height *= factor;
        depth *= factor;
    }

    int random(int min, int max){ 
        return rand() % (max-min)+min;
    }
    
    //convert window coordinates to opengl coordinates
    sf::Vector3f toOpenGLCoordinates(const sf::Vector2f& point)
    {
        
        GLdouble modelview[16];
        glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
        
        GLdouble projection[16];
        glGetDoublev( GL_PROJECTION_MATRIX, projection );
        
        GLint viewport[4];
        glGetIntegerv( GL_VIEWPORT, viewport );
        
        GLfloat winX = point.x;
        GLfloat winY = (float)viewport[3] - (float)point.y;
        GLfloat winZ = 0 ;
        
        GLdouble posX, posY, posZ;
        
        glReadPixels( winX, winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );
        
        gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
        
        return sf::Vector3f(posX, posY, posZ);
    }
}