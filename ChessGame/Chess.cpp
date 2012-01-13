//
//  Chess.cpp
//  ChessGame
//
//  Created by Dibash Chhetri on 1/10/12.
//  Copyright (c) 2012 University of Connecticut. All rights reserved.
//

#include "Chess.h"
#include "Pawn.h"
#include <iostream>
using namespace std;

namespace ChessGame
{
    Chess::Chess(sf::RenderWindow& app):app(app), m_isUserOneTurn(true){
        _initialize();
    }
    
    //start the game
    void Chess::play(){
        m_board.draw(app);
    }

    //reset board
    void Chess::reset(){}
    
    //save state
    void Chess::saveState(){}
    
    //load state
    void Chess::loadState(){}
    
    //handle mouse clicked
    void Chess::onMouseClicked(int x, int y){
        sf::Vector2i index = m_board.convertToBoardIndex(x, y);
        //if valid index 
        if(index != ChessBoard::BAD_INDEX)
        {
            ChessBoard::BoardSlot& entry = m_board.getSlot(index.x, index.y);
        
            switch(entry.status)
            {
                case ChessBoard::HIGHLIGHTED: _onHighlightedEntryClicked(entry);
                                              break;
                    
                case ChessBoard::OCCUPIED:  _onOccupiedEntryClicked(entry); 
                                            break;
                    
                case ChessBoard::EMPTY:     m_board.clearHighlightedEntries(); 
                                            break;
                    
            }
           
        }
    }
    
    //private helper function
    void Chess::_initialize(){
        //initialize white pieces
        PieceSet whitePieces = m_whiteUser.second;
        PieceSet blackPieces = m_blackUser.second;

        //for now make all pawns
        for(int i = 0; i < whitePieces.size(); ++i){
            whitePieces[i] = boost::shared_ptr<IChessPiece>(new Pawn());
            blackPieces[i] = boost::shared_ptr<IChessPiece>(new Pawn());
        }
        
        m_board.populate(whitePieces, blackPieces);
    }
    void Chess::_onHighlightedEntryClicked(ChessBoard::BoardSlot& newSlot){
        m_board.moveChessPiece(*m_lastActiveSlot, newSlot);
    }
    void Chess::_onOccupiedEntryClicked(ChessBoard::BoardSlot& entry){
        m_lastActiveSlot = &entry; //mark active slot
        m_board.clearHighlightedEntries();
        entry.piece->showPossibleMoveLocation(m_board);
    }
}