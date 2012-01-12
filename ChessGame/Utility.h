//
//  Utility.h
//  ChessGame
//
//  Created by Dibash Chhetri on 1/8/12.
//  Copyright (c) 2012 University of Connecticut. All rights reserved.
//

#ifndef ChessGame_Utility_h
#define ChessGame_Utility_h

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <OpenGL/OpenGL.h>

namespace ChessGame 
{
    
    //Defines a Color interface for any shape
    class Color{
    private:
        float color[4];
    public:
        static const Color RED;
        static const Color GREEN;
        static const Color BLUE;
        static const Color YELLOW;
        static const Color WHITE;
        static const Color BLACK;
        static const Color GRAY;
        
        enum Component{ RED_COMPONENT, GREEN_COMPONENT, BLUE_COMPONENT, ALPHA_COMPONENT };
    public:
        Color();
        Color(float r, float g ,float b, float alpha = 0.0f);
        Color(float col[4]);  
        
        float redComponent()const;
        float greenComponent()const;
        float blueComponent()const;
        
        const float& operator[](Component c)const;
        float operator[](Component c);
        
        void darken();
        void lighten();
        void scale(float factor);
    };
    
    //represents a dimension for an object
    class Dimension{
    public:
        typedef float DimensionType;
    private:
        DimensionType width;
        DimensionType height;
        DimensionType depth;
    public:
        Dimension();
        Dimension(DimensionType width, DimensionType height, DimensionType depth = 0);
        
        void scale(float factor);
        
        void setWidth(DimensionType width);
        void setHeight(DimensionType height);
        void setDepth(DimensionType depth);
        
        DimensionType getWidth()const;
        DimensionType getHeight()const;
        DimensionType getDepth()const;
    };
    
    class Cloneable{
    public:
        virtual ~Cloneable(){}
        virtual Cloneable* clone()const = 0;
    };
    
    
    //generate a random number between min and max
    int random(int min, int max);
    //convert window's coprdinates to opengl coordinates
    sf::Vector3f toOpenGLCoordinates(const sf::Vector2f& point);
}
#endif
