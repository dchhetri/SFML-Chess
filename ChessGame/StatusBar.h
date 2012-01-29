//
//  StatusBar.h
//  ChessGame
//
//  Created by Dibash Chhetri on 1/21/12.
//  Copyright (c) 2012 University of Connecticut. All rights reserved.
//

#ifndef ChessGame_StatusBar_h
#define ChessGame_StatusBar_h

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>

namespace ChessGame
{
    //Defines a class to update and show the current status of the game
    //the current status can be any descriptive information. The status bar has of the following form.
/** 
 **  |---------------------------------------------------------------------
 **  |   [StatusMessage::messageType]  |  [StatusMessage::message]        | 
 **  |____________________________________________________________________| 
 */
    
    struct StatusMessage{
        sf::String messageType;
        sf::String message;
        StatusMessage(){}
        StatusMessage(const sf::String& msgType, const sf::String& msg)
        :  messageType(msgType),message(msg){}
    };
    
    class StatusBar{
    public:
        
    private:
        StatusMessage m_statusInfo;
        sf::Sprite m_background;
        bool m_isVisible;
    public:
        StatusBar();
        //set the background of the status bar
        void setBackgroundColor(const sf::Color& newBackgroundColor);
        //set the text color of the current status
        void setTextColor(const sf::Color& newTextColor);
        //set the current status
        void setStatus(const StatusMessage& newStatus);
        //set only the messageType
        void setStatusType(const std::string& messageType);
        //set the actual message
        void setStatusMessage(const std::string& message);
        
        //set the dimension of the status bar
        void setDimension(const sf::Vector2f& dimension);
        //sets visibility
        void setVisibility(bool isVisible);
        //sets the status bar position
        void setPosition(const sf::Vector2f& newPosition);
        
        //returns if the status bar is set to visible
        bool isVisible()const;

        //returns the current background color
        sf::Color  getBackgroundColor()const;
        //returns the current text color
        sf::Color  getTextColor()const;
        //returns the current status message
        StatusMessage getStatus()const;
        //returns the current status type
        sf::String getStatusType()const;
        //returns the current status message
        sf::String getStatusMessage()const;
        //returns the current position of the status
        sf::Vector2f getPosition()const;
        
        //draws the status bar if visible
        void draw(sf::RenderWindow& canvas)const;
    private:
        sf::String _makeStatusType(const std::string& msgType);
        sf::String _makeStatusMsg(const std::string& msg);
    };

}
#endif
