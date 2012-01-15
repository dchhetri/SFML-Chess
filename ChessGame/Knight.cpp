//
//  Knight.cpp
//  ChessGame
//
//  Created by Dibash Chhetri on 1/14/12.
//  Copyright (c) 2012 University of Connecticut. All rights reserved.
//

#include "Knight.h"
#include "ChessPieceImageManager.h"

namespace ChessGame {
    Knight::Knight(){
        m_pieceType = KNIGHT;
        m_sprite.SetImage(ChessPieceImageManager::getKnightImage());
    }
    //draws the chess piece
    void Knight::draw(sf::RenderWindow& canvas)const{
        canvas.Draw(m_sprite);
    }
    
    //moves the chess piece to the new location
    void Knight::animateTo(const sf::Vector2f& offsetPosition){
        m_sprite.Move(offsetPosition);
    }
    
    //shows possible move location of where the piece could move to
    void Knight::showPossibleMoveLocation(ChessBoard& gameBoard)const{
        using sf::Vector2i;
        Vector2i spritePos( int(m_sprite.GetPosition().x),int(m_sprite.GetPosition().y));
        Vector2i slotPos = gameBoard.convertToBoardIndex(spritePos.x,spritePos.y);
        
        //check if the possible move position are valid

        //front mid left
        if(slotPos.x + 1 < ChessBoard::BOARD_HEIGHT && slotPos.y - 2 >= 0)
        {
            if(!gameBoard.isOccupied(slotPos.x + 1, slotPos.y - 2) ||
                gameBoard.isOccupiedWithEnemy(slotPos.x + 1, slotPos.y - 2, m_pieceId))
            {
                gameBoard.makeHighlighted(slotPos.x + 1, slotPos.y - 2);
            }
        }
        //front mid right
        if(slotPos.x + 1 < ChessBoard::BOARD_HEIGHT && slotPos.y + 2 < ChessBoard::BOARD_WIDTH){
            if(!gameBoard.isOccupied(slotPos.x + 1, slotPos.y + 2) ||
                gameBoard.isOccupiedWithEnemy(slotPos.x + 1, slotPos.y + 2, m_pieceId))
            {
                    gameBoard.makeHighlighted(slotPos.x + 1, slotPos.y + 2);
            }
        }
        //back mid left
        if(slotPos.x - 1 >= 0 &&  slotPos.y - 2 >= 0){
            if(!gameBoard.isOccupied(slotPos.x - 1, slotPos.y - 2) ||
               gameBoard.isOccupiedWithEnemy(slotPos.x - 1, slotPos.y - 2, m_pieceId))
            {
                gameBoard.makeHighlighted(slotPos.x - 1, slotPos.y - 2);
            }
        }
        //back mid right
        if(slotPos.x - 1 >= 0 && slotPos.y + 2 < ChessBoard::BOARD_WIDTH){
            if(!gameBoard.isOccupied(slotPos.x - 1, slotPos.y + 2) ||
               gameBoard.isOccupiedWithEnemy(slotPos.x - 1, slotPos.y + 2, m_pieceId))
            {
                gameBoard.makeHighlighted(slotPos.x - 1, slotPos.y + 2);
            }
        }
        //front top left
        if(slotPos.x + 2 < ChessBoard::BOARD_HEIGHT && slotPos.y - 1 >= 0){
            if(!gameBoard.isOccupied(slotPos.x + 2, slotPos.y - 1) ||
                gameBoard.isOccupiedWithEnemy(slotPos.x + 2, slotPos.y - 1, m_pieceId))
            {
                gameBoard.makeHighlighted(slotPos.x + 2, slotPos.y - 1);
            }
        }
        //front top right
        if(slotPos.x + 2 < ChessBoard::BOARD_WIDTH && slotPos.y + 1 < ChessBoard::BOARD_WIDTH ){
            if(!gameBoard.isOccupied(slotPos.x + 2, slotPos.y + 1) ||
               gameBoard.isOccupiedWithEnemy(slotPos.x + 2, slotPos.y + 1, m_pieceId))
            {
                gameBoard.makeHighlighted(slotPos.x + 2, slotPos.y + 1);
            }
        }
        //back bottom left
        if(slotPos.x - 2 >= 0 && slotPos.y - 1 >= 0){
            if(!gameBoard.isOccupied(slotPos.x - 2, slotPos.y - 1) ||
               gameBoard.isOccupiedWithEnemy(slotPos.x - 2, slotPos.y - 1, m_pieceId))
            {
                gameBoard.makeHighlighted(slotPos.x - 2, slotPos.y - 1);
            }
        }
        //back bottom right
        if(slotPos.x - 2 >= 0 && slotPos.y + 1 < ChessBoard::BOARD_WIDTH){
            if(!gameBoard.isOccupied(slotPos.x - 2, slotPos.y + 1) ||
               gameBoard.isOccupiedWithEnemy(slotPos.x - 2, slotPos.y + 1, m_pieceId))
            {
                gameBoard.makeHighlighted(slotPos.x - 2, slotPos.y + 1);
            }
        }
    }
    
}