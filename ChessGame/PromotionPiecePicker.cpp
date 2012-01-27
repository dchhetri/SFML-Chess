//
//  PromitionPiecePicker.cpp
//  ChessGame
//
//  Created by Dibash Chhetri on 1/26/12.
//  Copyright (c) 2012 University of Connecticut. All rights reserved.
//

#include "PromotionPiecePicker.h"
#include <iostream>
using namespace std;

namespace ChessGame 
{
    PromotionPiecePicker::PromotionPiecePicker(const sf::RenderWindow& window): mainWindow(window){
        m_window.Create(sf::VideoMode(200,200,32), "Promition Picker");
        m_window.Clear(sf::Color::White);
    }
    
    detail::IChessPieceEnums::PieceType PromotionPiecePicker::getUserPick()
    {
        m_window.SetActive();
        
        detail::IChessPieceEnums::PieceType pieceType;
        
        while(m_window.IsOpened())
        {
            sf::Event event;
            //handle event
            while(m_window.GetEvent(event))
            {
                /* handle event */
                if(m_window.GetInput().IsMouseButtonDown(sf::Mouse::Left)){
                    m_window.Close();
                    cout << "in event\n";
                }
            }
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            m_window.Display();
        }
        
        //make main window active again
        mainWindow.SetActive();
        
        return pieceType;
    }
}