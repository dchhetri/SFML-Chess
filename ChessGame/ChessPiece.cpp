//
//  ChessPiece.cpp
//  ChessGame
//
//  Created by Dibash Chhetri on 1/16/12.
//  Copyright (c) 2012 University of Connecticut. All rights reserved.
//

#include "ChessPiece.h"
#include "ChessPieceImageManager.h"

namespace ChessGame 
{
  
    //returns the types chess piece
    detail::IChessPieceEnums::PieceType IChessPiece::pieceType()const{ return m_pieceType; }
    
    //returns constant sprite object
    const sf::Sprite& IChessPiece::getSprite()const{ return m_sprite; }
    
    //returns the sprite object
    sf::Sprite& IChessPiece::getSprite(){ return m_sprite; }
    
    //sets new position
    void IChessPiece::setPosition(const sf::Vector2f& newPosition){
        m_sprite.SetPosition(newPosition);
    }
    //set direction
    void IChessPiece::setPieceDirection(const detail::IChessPieceEnums::PieceDirection& dir){ 
        m_direction = dir; 
    }
    //get current move direction
    detail::IChessPieceEnums::PieceDirection IChessPiece::getPieceDirection()const{ 
        return m_direction;
    }
    //set the current piece id
    void IChessPiece::setPieceID(const detail::IChessPieceEnums::PieceId& id){
        m_pieceId = id;
        //update image to accomidate the new id(i.e black or white )
        m_sprite.SetImage(ChessPieceImageManager::getChessPieceImage(m_pieceType, m_pieceId));
    }
    //get the current piece id
    detail::IChessPieceEnums::PieceId IChessPiece::getPieceID()const{
        return m_pieceId;
    }
    //set the current piece type
    void IChessPiece::setPieceType(const PieceType pieceType){
        m_pieceType = pieceType;
    }
    
    //returns the piece type
    detail::IChessPieceEnums::PieceType IChessPiece::getPieceType()const{
        return m_pieceType;
    }
    
    //tries to highlight the slot given by index by checking if its empty or a enemy's piece occupies it
    IChessPiece::HighlightedStatus IChessPiece::_tryToHighlight(ChessBoard& gameBoard,const sf::Vector2i& index)const
    {
        HighlightedStatus status = NOT_HIGHLIGHTED;
        //if not occupied highlight it
        if(!gameBoard.isOccupied(index.x, index.y)){
            gameBoard.makeHighlighted(index.x, index.y);
            status = EMPTY_SLOT_HIGHLIGHTED;
        }//else if occupied with enemy highlight it
        else if(gameBoard.isOccupiedWithEnemy(index.x, index.y, m_pieceId)){
            gameBoard.makeHighlighted(index.x, index.y);
            status = ENEMY_SLOT_HIGHLIGHTED;;
        }
        return status;
    }
    
    IChessPiece::HighlightedStatus IChessPiece::_canHighlightSlot(ChessBoard& gameBoard, const sf::Vector2i& index)const{
        HighlightedStatus status = NOT_HIGHLIGHTED;
        //if not occupied highlight it
        if(!gameBoard.isOccupied(index.x, index.y)){
            status = EMPTY_SLOT_HIGHLIGHTED;
        }//else if occupied with enemy highlight it
        else if(gameBoard.isOccupiedWithEnemy(index.x, index.y, m_pieceId)){
            status = ENEMY_SLOT_HIGHLIGHTED;;
        }
        return status;
    }
}
