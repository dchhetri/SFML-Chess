//
//  PromitionPiecePicker.cpp
//  ChessGame
//
//  Created by Dibash Chhetri on 1/26/12.
//  Copyright (c) 2012 University of Connecticut. All rights reserved.
//


#include "Knight.h"
#include "Rook.h"
#include "Bishop.h"
#include "Queen.h"
#include "PromotionPiecePicker.h"
#include "utils.h"

#include <iostream>
#include <string>
using namespace std;
namespace ChessGame 
{
    PromotionPiecePicker::PromotionPiecePicker(const sf::RenderWindow& window): mainWindow(window){
        m_window.Create(sf::VideoMode(150,150), "Promition Picker");
        m_window.SetFramerateLimit(60);
        
        m_pieceOptions[0][0] = PieceType(new Knight());
        m_pieceOptions[0][1] = PieceType(new Rook());
        m_pieceOptions[1][0] = PieceType(new Bishop());
        m_pieceOptions[1][1] = PieceType(new Queen());
        
        const int CELL_SIZE = 50;
        int offset = 20;
        for(int i = 0; i < ROW_SIZE; ++i){
            for(int j = 0; j < COL_SIZE; ++j){
                m_pieceOptions[i][j]->getSprite().Resize(CELL_SIZE, CELL_SIZE);
                m_pieceOptions[i][j]->setPosition(sf::Vector2f(10 + i*(CELL_SIZE+offset) ,10 + j * (CELL_SIZE+offset)));
            }
        }
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
                // Close window : exit
                if (event.Type == sf::Event::Closed){
                    m_window.Close();
                }
                
                // Escape key : exit
                if ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::Escape)){
                    m_window.Close();
                }
                /* handle event */
                if(m_window.GetInput().IsMouseButtonDown(sf::Mouse::Left))
                {
                    //check if a promotion was picked
                    bool isPicked = _onMouseClick(m_window.GetInput().GetMouseX(),m_window.GetInput().GetMouseY(), pieceType);
                    if(isPicked) m_window.Close();
                }
            }
            
            m_window.Clear(sf::Color(200,200,200));
            
            _displaySelections();
            
            m_window.Display();
        }
        
        //make main window active again
        mainWindow.SetActive();
  
        return pieceType;
    }
    void PromotionPiecePicker::_displaySelections(){

        for(int i = 0; i < ROW_SIZE; ++i){
            for(int j = 0; j < COL_SIZE; ++j){
                m_pieceOptions[i][j]->draw(m_window);
            }
        }
    }
    bool PromotionPiecePicker::_onMouseClick(float x, float y, detail::IChessPieceEnums::PieceType& pieceType){
        bool isPicked = false;
        bool found = false;
        for(int i = 0; i < ROW_SIZE && !found; ++i){
            for(int j = 0; j < COL_SIZE; ++j){
                //check if (x,y) is inside sprite's area, if so then save proper state
                if(util::contains(x,y, m_pieceOptions[i][j]->getSprite()))
                {
                    isPicked = true;
                    found = true;
                    pieceType = m_pieceOptions[i][j]->getPieceType();
                    break;
                }
            }
        }
        return isPicked;
    }
}