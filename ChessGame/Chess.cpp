//
//  Chess.cpp
//  ChessGame
//
//  Created by Dibash Chhetri on 1/10/12.
//  Copyright (c) 2012 University of Connecticut. All rights reserved.
//

#include "Chess.h"
#include "Pawn.h"
#include "Knight.h"
#include "Bishop.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"

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
        m_leftWhiteUserPanel.draw(app);
        m_righBlackUsertPanel.draw(app);
    }

    //reset board
    void Chess::reset(){}
    
    //save state
    void Chess::saveState(){}
    
    //load state
    void Chess::loadState(){}
    
    //returns true if its user one's turn
    bool Chess::isUserOneTurn()const{
        return m_isUserOneTurn;
    }
    //returns user1 id
    int Chess::getUserOneId()const{
        return m_whiteUser.first.id;
    }
    //returns user2 id
    int Chess::getUserTwoId()const{
        return m_blackUser.first.id;
    }
    
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
        //set id
        m_whiteUser.first.id = detail::IChessPieceEnums::WHITE_PIECE_ID;
        m_blackUser.first.id = detail::IChessPieceEnums::BLACK_PIECE_ID;
        
        PieceSet& whitePieces = m_whiteUser.second;
        PieceSet& blackPieces = m_blackUser.second;

        //insert pawn
        for(int i = 0; i < 8; ++i){
            whitePieces[i + ChessBoard::BOARD_WIDTH] = boost::shared_ptr<IChessPiece>(new Pawn());
            blackPieces[i] = boost::shared_ptr<IChessPiece>(new Pawn());
        }
        //insert other piece manually
        whitePieces[0] = boost::shared_ptr<IChessPiece>(new Rook());
        whitePieces[1] = boost::shared_ptr<IChessPiece>(new Knight());
        whitePieces[2] = boost::shared_ptr<IChessPiece>(new Bishop());
        whitePieces[3] = boost::shared_ptr<IChessPiece>(new King());
        whitePieces[4] = boost::shared_ptr<IChessPiece>(new Queen());
        whitePieces[5] = boost::shared_ptr<IChessPiece>(new Bishop());
        whitePieces[6] = boost::shared_ptr<IChessPiece>(new Knight());
        whitePieces[7] = boost::shared_ptr<IChessPiece>(new Rook());
        
        
        blackPieces[0 + ChessBoard::BOARD_WIDTH] = boost::shared_ptr<IChessPiece>(new Rook());
        blackPieces[1 + ChessBoard::BOARD_WIDTH] = boost::shared_ptr<IChessPiece>(new Knight());
        blackPieces[2 + ChessBoard::BOARD_WIDTH] = boost::shared_ptr<IChessPiece>(new Bishop());
        blackPieces[3 + ChessBoard::BOARD_WIDTH] = boost::shared_ptr<IChessPiece>(new King());
        blackPieces[4 + ChessBoard::BOARD_WIDTH] = boost::shared_ptr<IChessPiece>(new Queen());
        blackPieces[5 + ChessBoard::BOARD_WIDTH] = boost::shared_ptr<IChessPiece>(new Bishop());
        blackPieces[6 + ChessBoard::BOARD_WIDTH] = boost::shared_ptr<IChessPiece>(new Knight());
        blackPieces[7 + ChessBoard::BOARD_WIDTH] = boost::shared_ptr<IChessPiece>(new Rook());
        
        //set id
        for(int i = 0; i < m_whiteUser.second.size(); ++i){
            whitePieces[i]->setPieceID(detail::IChessPieceEnums::WHITE_PIECE_ID);
            blackPieces[i]->setPieceID(detail::IChessPieceEnums::BLACK_PIECE_ID);
        }
        
        m_board.populate(whitePieces, blackPieces);
        
        m_leftWhiteUserPanel.setPosition(sf::Vector2f(25,100));
        m_righBlackUsertPanel.setPosition(sf::Vector2f(675 , 100));
        
        m_righBlackUsertPanel.setBackgoundColor(m_leftWhiteUserPanel.getCellColor());
        m_righBlackUsertPanel.setCellColor(m_leftWhiteUserPanel.getBackgroundColor());
    }
    
    void Chess::_onHighlightedEntryClicked(ChessBoard::BoardSlot& newSlot){
        //move piece
        //if highlighted entry has piece add it to the correct side panel
        if(newSlot.piece.get() != NULL){
            _addEatenPieceToSidePanel(newSlot); //add eaten piece to side panel
        }
        m_board.moveChessPiece(*m_lastActiveSlot, newSlot);
        _alternateUserTurn();
    }
    //updates only if current user's piece has been clicked
    void Chess::_onOccupiedEntryClicked(ChessBoard::BoardSlot& entry){
        int currentUserId = isUserOneTurn() ? getUserOneId() : getUserTwoId();
        if(entry.piece->getPieceID() == currentUserId){
            m_lastActiveSlot = &entry; //mark active slot
            m_board.clearHighlightedEntries();
            entry.piece->showPossibleMoveLocation(m_board);
        } else m_board.clearHighlightedEntries();
    }
    //alternates user's turn
    void Chess::_alternateUserTurn(){
        m_isUserOneTurn ^= 1;
    }
    void Chess::_addEatenPieceToSidePanel(ChessBoard::BoardSlot& slot){
        //if black piece eaten, add it to the left
        if(slot.piece->getPieceID() == m_blackUser.first.id ){
            m_leftWhiteUserPanel.addNext(slot.piece);
        }else{
            m_righBlackUsertPanel.addNext(slot.piece);
        }

    }
}
