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
#include "PromotionPiecePicker.h"

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
        whitePieces[0] = boost::shared_ptr<IChessPiece>(new Rook(detail::IChessPieceEnums::WHITE_PIECE_ID));
        whitePieces[1] = boost::shared_ptr<IChessPiece>(new Knight(detail::IChessPieceEnums::WHITE_PIECE_ID));
        whitePieces[2] = boost::shared_ptr<IChessPiece>(new Bishop(detail::IChessPieceEnums::WHITE_PIECE_ID));
        whitePieces[3] = boost::shared_ptr<IChessPiece>(new Queen(detail::IChessPieceEnums::WHITE_PIECE_ID));
        whitePieces[4] = boost::shared_ptr<IChessPiece>(new King(detail::IChessPieceEnums::WHITE_PIECE_ID));        
        whitePieces[5] = boost::shared_ptr<IChessPiece>(new Bishop(detail::IChessPieceEnums::WHITE_PIECE_ID));
        whitePieces[6] = boost::shared_ptr<IChessPiece>(new Knight(detail::IChessPieceEnums::WHITE_PIECE_ID));
        whitePieces[7] = boost::shared_ptr<IChessPiece>(new Rook(detail::IChessPieceEnums::WHITE_PIECE_ID));
        
        
        blackPieces[0 + ChessBoard::BOARD_WIDTH] = boost::shared_ptr<IChessPiece>(new Rook(detail::IChessPieceEnums::BLACK_PIECE_ID));
        blackPieces[1 + ChessBoard::BOARD_WIDTH] = boost::shared_ptr<IChessPiece>(new Knight(detail::IChessPieceEnums::BLACK_PIECE_ID));
        blackPieces[2 + ChessBoard::BOARD_WIDTH] = boost::shared_ptr<IChessPiece>(new Bishop(detail::IChessPieceEnums::BLACK_PIECE_ID));
        blackPieces[3 + ChessBoard::BOARD_WIDTH] = boost::shared_ptr<IChessPiece>(new Queen(detail::IChessPieceEnums::BLACK_PIECE_ID));
        blackPieces[4 + ChessBoard::BOARD_WIDTH] = boost::shared_ptr<IChessPiece>(new King(detail::IChessPieceEnums::BLACK_PIECE_ID));
        blackPieces[5 + ChessBoard::BOARD_WIDTH] = boost::shared_ptr<IChessPiece>(new Bishop(detail::IChessPieceEnums::BLACK_PIECE_ID));
        blackPieces[6 + ChessBoard::BOARD_WIDTH] = boost::shared_ptr<IChessPiece>(new Knight(detail::IChessPieceEnums::BLACK_PIECE_ID));
        blackPieces[7 + ChessBoard::BOARD_WIDTH] = boost::shared_ptr<IChessPiece>(new Rook(detail::IChessPieceEnums::BLACK_PIECE_ID));
        
        
        m_board.populate(whitePieces, blackPieces);
        
        m_leftWhiteUserPanel.setPosition(sf::Vector2f(25,100));
        m_righBlackUsertPanel.setPosition(sf::Vector2f(675,100));
        
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
        if(_isKingChecked(newSlot)){
            _onKingChecked(); 
        }
        
        //if stalemate alert it
        if(_isStaleMate()){
            _onStaleMate();
        }
        
        //if promotion possible, promote it
        //check if game is not over just for the case when pawn eats the king and 
        //the pawn is in position to be promoted
        if(!m_isGameOver && _shouldPromote(newSlot)){
            _onPromotion(newSlot);
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
    bool Chess::_isKingChecked(ChessBoard::BoardSlot& lastSlotUsed){
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
    bool Chess::_shouldPromote(ChessBoard::BoardSlot& slot){
        bool shouldPromote = false;
        
        //first check if the piece is pawn( only pawn gets promoted )
        if(slot.piece->getPieceType() == detail::IChessPieceEnums::PAWN){
            //get opposite end position
            int endPos = slot.piece->getPieceDirection() == detail::IChessPieceEnums::DOWN ? 0 : ChessBoard::BOARD_HEIGHT - 1;
            //get piece position and check if piece is on proper end
            sf::Vector2f rawPos = slot.rect.GetPosition();
            //get convertex booard position
            int indexPos =  m_board.convertToBoardIndex(rawPos.x, rawPos.y).x;
            //true if pawn is in proper end position
            shouldPromote = indexPos == endPos;
        }
        return shouldPromote;
    }
    void Chess::_onKingChecked(){
        //sf::String checkmateString("CHECKMATE!", sf::Font::GetDefaultFont());
        //checkmateString.SetColor(sf::Color(255,0,0));
        //checkmateString.Move(300, 0);
        //app.Draw(checkmateString);
        m_statusBar.setStatusType("Current Status : ");
        m_statusBar.setStatusMessage("CHECK!");
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
    void Chess::_onPromotion(ChessBoard::BoardSlot &slot){
        m_statusBar.setStatusType("Current Status: ");
        m_statusBar.setStatusMessage("PROMOTING!");
        PromotionPiecePicker picker(app, slot.piece->getPieceID());
        //waits until user picks one
        detail::IChessPieceEnums::PieceType type = picker.getUserPick();
        sf::Vector2f pos = slot.piece->getSprite().GetPosition();
        PiecePtr newPiece;
        //promote the piece to the choosen one
        switch (type) {
            case detail::IChessPieceEnums::KNIGHT:
                newPiece =  PiecePtr(new Knight(slot.piece->getPieceID()) );
                break;
            case detail::IChessPieceEnums::BISHOP:
                newPiece = PiecePtr(new Bishop(slot.piece->getPieceID()));
                break;
            case detail::IChessPieceEnums::ROOK:
                newPiece = PiecePtr(new Rook(slot.piece->getPieceID()));
                break;
            case detail::IChessPieceEnums::QUEEN:
                newPiece = PiecePtr( new Queen(slot.piece->getPieceID()));
            default:
                break;
        }
        //update new piece position and size
        newPiece->getSprite().SetPosition(slot.piece->getSprite().GetPosition());
        newPiece->getSprite().Resize(slot.piece->getSprite().GetSize());
        slot.piece = newPiece;
    }
}
