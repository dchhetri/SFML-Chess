//
//  StatusBar.cpp
//  ChessGame
//
//  Created by Dibash Chhetri on 1/21/12.
//  Copyright (c) 2012 University of Connecticut. All rights reserved.
//

#include "StatusBar.h"
namespace ChessGame{
    
    StatusBar::StatusBar()
    : m_isVisible(true)
    {
        //set default settings
        //m_background.SetColor(sf::Color(127,127,127));
        m_background.SetColor(sf::Color::Black);
        m_background.Resize(800, 25);
        m_statusInfo.message.SetColor(sf::Color::White);
        m_statusInfo.messageType.SetColor(sf::Color::White);
    }
    
    //set the background of the status bar
    void StatusBar::setBackgroundColor(const sf::Color& newBackgroundColor){
        m_background.SetColor(newBackgroundColor);
    }
    //set the text color of the current status
    void StatusBar::setTextColor(const sf::Color& newTextColor){
        m_statusInfo.message.SetColor(newTextColor);
        m_statusInfo.messageType.SetColor(newTextColor);
    }
    //set the current status
    void StatusBar::setStatus(const StatusMessage& newStatus){
        m_statusInfo = newStatus;
    }
    //set only the messageType
    void StatusBar::setStatusType(const  std::string& messageType){
        m_statusInfo.messageType = _makeStatusType(messageType);
    }
    //set the actual message
    void StatusBar::setStatusMessage(const  std::string& message){
        m_statusInfo.message = _makeStatusMsg(message);
    }
    
    //set the dimension of the status bar
    void StatusBar::setDimension(const sf::Vector2f& dimension){
        m_background.Resize(dimension);
    }
    //sets visibility
    void StatusBar::setVisibility(bool isVisible){
        m_isVisible = isVisible;
    }
    void StatusBar::setPosition(const sf::Vector2f& newPosition){
        m_background.SetPosition(newPosition);
    }
    //returns the current 
    sf::Color  StatusBar::getBackgroundColor()const{
        return m_background.GetColor();
    }
    sf::Color  StatusBar::getTextColor()const{
        return m_statusInfo.message.GetColor();
    }
    StatusMessage  StatusBar::getStatus()const{
        return m_statusInfo;
    }
    sf::String StatusBar::getStatusType()const{
        return m_statusInfo.messageType;
    }
    //returns the current status message
    sf::String StatusBar::getStatusMessage()const{
        return m_statusInfo.message;
    }
    
    sf::Vector2f StatusBar::getPosition()const{
        return m_background.GetPosition();
    }
    //returns if the status bar is set to visible
    bool StatusBar::isVisible()const{
        return m_isVisible;
    }
    
    void StatusBar::draw(sf::RenderWindow& canvas)const
    {
        //if visible then draw it
        if(m_isVisible){
            
            canvas.Draw(m_statusInfo.messageType);
            canvas.Draw(m_statusInfo.message);
            canvas.Draw(m_background);
        }
    }
    //private helper functions
    sf::String StatusBar::_makeStatusType(const std::string& msg){
        sf::String msgType(msg, sf::Font::GetDefaultFont(),20);
        msgType.SetColor(sf::Color(141,141,141));
        msgType.Move(5,0);
        return msgType;
    }
    
    sf::String StatusBar::_makeStatusMsg(const std::string& msg){
        sf::String message(msg, sf::Font::GetDefaultFont(),20);
        message.Move(250,0);
        return message;
    }
}