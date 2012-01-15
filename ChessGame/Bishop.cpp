//
//  Bishop.cpp
//  ChessGame
//
//  Created by Dibash Chhetri on 1/14/12.
//  Copyright (c) 2012 University of Connecticut. All rights reserved.
//

#include "Bishop.h"
#include "ChessPieceImageManager.h"

namespace ChessGame 
{
    Bishop::Bishop(){
        m_pieceType = BISHOP;
        m_sprite.SetImage(ChessPieceImageManager::getBishopImage());
    }
    //draws the chess piece
    void Bishop::draw(sf::RenderWindow& canvas)const{
        canvas.Draw(m_sprite);
    }
    
    //moves the chess piece to the new location
    void Bishop::animateTo(const sf::Vector2f& offsetPosition){
        m_sprite.Move(offsetPosition);
    }
    
    //shows possible move location of where the piece could move to
    void Bishop::showPossibleMoveLocation(ChessBoard& gameBoard)const{
        using sf::Vector2i;
        Vector2i spritePos( int(m_sprite.GetPosition().x),int(m_sprite.GetPosition().y));
        Vector2i slotPos = gameBoard.convertToBoardIndex(spritePos.x,spritePos.y);
        
        Vector2i tmp(slotPos.x - 1, slotPos.y - 1);
        //check top left-diagnol if available
        while(tmp.x >= 0 && tmp.y >= 0)
        {
            //if not occupied, highlight it
            if(!gameBoard.isOccupied(tmp.x, tmp.y)){
                gameBoard.makeHighlighted(tmp.x, tmp.y);
                --tmp.x;
                --tmp.y;
            }
            //else if occupied, check if its with enemy and if so highlight it and exit out loop
            else if(gameBoard.isOccupiedWithEnemy(tmp.x, tmp.y, m_pieceId)){
                gameBoard.makeHighlighted(tmp.x, tmp.y);
                break;
            }
            //else ouccupied with own piece type
            else break;
        }
        //check top right-diagnol
        tmp = Vector2i(slotPos.x - 1, slotPos.y + 1);
        while(tmp.x >= 0 && tmp.y < ChessBoard::BOARD_WIDTH){
            if(!gameBoard.isOccupied(tmp.x, tmp.y)){
                gameBoard.makeHighlighted(tmp.x, tmp.y);
                --tmp.x;
                ++tmp.y;
            }
            else if(gameBoard.isOccupiedWithEnemy(tmp.x, tmp.y, m_pieceId)){
                gameBoard.makeHighlighted(tmp.x, tmp.y);
                break;
            }
            else break;
            
        }
        //check bottom left-diagnol
        tmp = Vector2i(slotPos.x + 1, slotPos.y - 1);
        while(tmp.x < ChessBoard::BOARD_HEIGHT && tmp.y >= 0){
            if(!gameBoard.isOccupied(tmp.x, tmp.y)){
                gameBoard.makeHighlighted(tmp.x, tmp.y);
                ++tmp.x;
                --tmp.y;
            }
            else if(gameBoard.isOccupiedWithEnemy(tmp.x, tmp.y, m_pieceId)){
                gameBoard.makeHighlighted(tmp.x, tmp.y);
                break;
            }
            else break;
            
        }
        //check bottom right-diagnol
        tmp = Vector2i(slotPos.x + 1, slotPos.y + 1);
        while(tmp.x < ChessBoard::BOARD_HEIGHT && tmp.y < ChessBoard::BOARD_HEIGHT){
            if(!gameBoard.isOccupied(tmp.x, tmp.y)){
                gameBoard.makeHighlighted(tmp.x, tmp.y);
                ++tmp.x;
                ++tmp.y;
            }
            else if(gameBoard.isOccupiedWithEnemy(tmp.x, tmp.y, m_pieceId)){
                gameBoard.makeHighlighted(tmp.x, tmp.y);
                break;
            }
            else break;
            
        }
    }
}
