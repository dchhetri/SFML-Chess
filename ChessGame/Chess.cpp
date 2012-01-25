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
#include "details.h"
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
        m_statusBar.draw(app);
    }

    //reset board
    void Chess::reset(){}
    
    //save state
    void Chess::saveState(){}
    
    //load state
    void Chess::loadState(){}
    
    bool Chess::isGameOver()const{
        return m_isGameOver;
    }
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
        if(index != ChessBoard::BAD_INDEX && !m_isGameOver)
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
        //setup status bar 
        m_statusBar.setStatusType("Current active player: ");
        m_statusBar.setStatusMessage("Player #1");
        
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
        //alternate the turn
        _alternateUserTurn();
        
        //if highlighted entry has piece add it to the correct side panel
        if(newSlot.piece.get() != NULL)
        {
            //add eaten piece to side panel
            _addEatenPieceToSidePanel(newSlot);             
            
            //king was eaten, game over
            if(newSlot.piece->getPieceType() == detail::IChessPieceEnums::KING){
                _onGameOver();
            }
        }
        
        //move actual piece
        m_board.moveChessPiece(*m_lastActiveSlot, newSlot);
        
        //if checkmate alert it
        if(_isCheckmate(newSlot)){
            _onCheckmate(); 
        }
        //if stalemate alert it
        if(_isStaleMate()){
            _onStaleMate();
        }
         
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
        m_statusBar.setStatusType("Current active player: ");
        m_statusBar.setStatusMessage((m_isUserOneTurn? "Player #1": "Player #2"));
    }
    void Chess::_addEatenPieceToSidePanel(ChessBoard::BoardSlot& slot){
        //if black piece eaten, add it to the left
        if(slot.piece->getPieceID() == m_blackUser.first.id ){
            m_leftWhiteUserPanel.addNext(slot.piece);
        }else{
            m_righBlackUsertPanel.addNext(slot.piece);
        }

    }
    //check if the last move caused a checkmate
    bool Chess::_isCheckmate(ChessBoard::BoardSlot& lastSlotUsed){
        bool isCheckMate = false;
        if(lastSlotUsed.piece.get() != NULL)
        {
            std::vector<sf::Vector2i> nextPossibleMoves = lastSlotUsed.piece->getPossibleMoveLocation(m_board);
            
            for(int i = 0; i < nextPossibleMoves.size(); ++i){
                sf::Vector2i& nextLocation = nextPossibleMoves[i];
                ChessBoard::BoardSlot& slot = m_board.getSlot(nextLocation.x, nextLocation.y);
                //check if king can be eaten next move
                if(slot.piece.get() != NULL && slot.piece->getPieceType() == detail::IChessPieceEnums::KING){
                    isCheckMate = true;
                    break;
                }
                //else continue;
            }
        }
        return isCheckMate;
    }
    //returns true if current state is stalemate, that is, it returns true if the opponent has no moves left
    bool Chess::_isStaleMate(){
        bool isStaleMate = true;
        const PieceSet& set = m_isUserOneTurn?  m_board.getWhiteSet() : m_board.getBlackSet();
        for(int i = 0; i < set.size(); ++i){
            std::vector<sf::Vector2i> moves = set[i]->getPossibleMoveLocation(m_board);
            if(moves.size() > 0){
                isStaleMate = false;
                break;
            }
        }
        return isStaleMate;
    }
    
    void Chess::_onCheckmate(){
        //sf::String checkmateString("CHECKMATE!", sf::Font::GetDefaultFont());
        //checkmateString.SetColor(sf::Color(255,0,0));
        //checkmateString.Move(300, 0);
        //app.Draw(checkmateString);
        m_statusBar.setStatusType("Current Status : ");
        m_statusBar.setStatusMessage("CHECKMATE!");
    }
    void Chess::_onGameOver(){
        //sf::String checkmateString("GAME OVER!", sf::Font::GetDefaultFont());
        //checkmateString.SetColor(sf::Color(255,0,0));
        //checkmateString.Move(300, 0);
        //app.Draw(checkmateString);
        m_statusBar.setStatusType("Current Status: ");
        m_statusBar.setStatusMessage("GAME OVER!");
        m_isGameOver = true;
    }
    void Chess::_onStaleMate(){
        m_statusBar.setStatusType("Current Status: ");
        m_statusBar.setStatusMessage("STALEMATE!");
        m_isGameOver = true;
    }
}
