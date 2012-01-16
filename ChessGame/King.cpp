//
//  King.cpp
//  ChessGame
//
//  Created by Dibash Chhetri on 1/16/12.
//  Copyright (c) 2012 University of Connecticut. All rights reserved.
//

#include "King.h"
#include "ChessPieceImageManager.h"

namespace ChessGame 
{
    
    King::King(){
        m_pieceType = KING;
        m_sprite.SetImage(ChessPieceImageManager::getKingImage());
    }

    //draws the chess piece
    void King::draw(sf::RenderWindow& canvas)const{
        canvas.Draw(m_sprite);
    }
    
    //moves the chess piece to the new location
    void King::animateTo(const sf::Vector2f& offsetPosition) {
        m_sprite.Move(offsetPosition);
    }
    
    //shows possible move location of where the piece could move to
    void King::showPossibleMoveLocation(ChessBoard& gameBoard)const{
        using sf::Vector2i;
        Vector2i spritePos( int(m_sprite.GetPosition().x),int(m_sprite.GetPosition().y));
        Vector2i slotPos = gameBoard.convertToBoardIndex(spritePos.x,spritePos.y);
        
        Vector2i tmp(slotPos.x - 1, slotPos.y - 1);
        
        //check possible moves in previous row if any 
        if(tmp.x >= 0)
        {
            
            for(int i = 0; i < 3; ++i, ++tmp.y )
            {
                if(tmp.y >= 0 && tmp.y < ChessBoard::BOARD_WIDTH){
                    //if not occupied highlight it
                    if(!gameBoard.isOccupied(tmp.x, tmp.y)){
                        gameBoard.makeHighlighted(tmp.x, tmp.y);
                    }//else if occupied with enemy highlight it
                    else if(gameBoard.isOccupiedWithEnemy(tmp.x, tmp.y, m_pieceId)){
                        gameBoard.makeHighlighted(tmp.x, tmp.y);
                    }
                }
            }
        }
        //check possible moves in forward row if any
        tmp = Vector2i(slotPos.x + 1, slotPos.y - 1);
        if(tmp.x < ChessBoard::BOARD_HEIGHT)
        {
            for(int i = 0; i < 3; ++i, ++tmp.y )
            {
                if(tmp.y >= 0 && tmp.y < ChessBoard::BOARD_WIDTH){
                    //if not occupied highlight it
                    if(!gameBoard.isOccupied(tmp.x, tmp.y)){
                        gameBoard.makeHighlighted(tmp.x, tmp.y);
                    }//else if occupied with enemy highlight it
                    else if(gameBoard.isOccupiedWithEnemy(tmp.x, tmp.y, m_pieceId)){
                        gameBoard.makeHighlighted(tmp.x, tmp.y);
                    }
                }
            }
        }
        //check left and right slots
        tmp = Vector2i(slotPos.x, slotPos.y - 1);
        if(tmp.y >= 0){
            if(!gameBoard.isOccupied(tmp.x, tmp.y)){
                gameBoard.makeHighlighted(tmp.x, tmp.y);
            }
            else if(gameBoard.isOccupiedWithEnemy(tmp.x, tmp.y, m_pieceId)){
                gameBoard.makeHighlighted(tmp.x, tmp.y);
            }
        }
        tmp = Vector2i(slotPos.x, slotPos.y + 1);
        if(tmp.y < ChessBoard::BOARD_WIDTH){
            if(!gameBoard.isOccupied(tmp.x, tmp.y)){
                gameBoard.makeHighlighted(tmp.x, tmp.y);
            }
            else if(gameBoard.isOccupiedWithEnemy(tmp.x, tmp.y, m_pieceId)){
                gameBoard.makeHighlighted(tmp.x, tmp.y);
            }
        }
        
    }
}
