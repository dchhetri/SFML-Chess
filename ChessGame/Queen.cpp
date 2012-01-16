//
//  Queen.cpp
//  ChessGame
//
//  Created by Dibash Chhetri on 1/15/12.
//  Copyright (c) 2012 University of Connecticut. All rights reserved.
//

#include "Queen.h"
#include "ChessPieceImageManager.h"

namespace ChessGame 
{
    Queen::Queen(){
        m_pieceType = QUEEN;
        m_sprite.SetImage(ChessPieceImageManager::getQueenImage());
    }
    
    //draws the chess piece
    void Queen::draw(sf::RenderWindow& canvas)const{
        canvas.Draw(m_sprite);
    }
    
    //moves the chess piece to the new location
    void Queen::animateTo(const sf::Vector2f& offsetPosition){
        m_sprite.Move(offsetPosition);
    }
    
    //shows possible move location of where the piece could move to
    void Queen::showPossibleMoveLocation(ChessBoard& gameBoard)const{
        using sf::Vector2i;
        Vector2i spritePos( int(m_sprite.GetPosition().x),int(m_sprite.GetPosition().y));
        Vector2i slotPos = gameBoard.convertToBoardIndex(spritePos.x,spritePos.y);

        //check north squares
        Vector2i tmp(slotPos.x - 1, slotPos.y );
        while(tmp.x >= 0){
            if(!gameBoard.isOccupied(tmp.x, tmp.y)){
                gameBoard.makeHighlighted(tmp.x, tmp.y);
                --tmp.x;
            }else if(gameBoard.isOccupiedWithEnemy(tmp.x, tmp.y, m_pieceId)){
                gameBoard.makeHighlighted(tmp.x, tmp.y);
                break;
            }else break; //occupied with own piece type
        }
        //check south squares
        tmp = Vector2i(slotPos.x + 1, slotPos.y );
        while(tmp.x < ChessBoard::BOARD_HEIGHT){
            if(!gameBoard.isOccupied(tmp.x, tmp.y)){
                gameBoard.makeHighlighted(tmp.x, tmp.y);
                ++tmp.x;
            }else if(gameBoard.isOccupiedWithEnemy(tmp.x, tmp.y, m_pieceId)){
                gameBoard.makeHighlighted(tmp.x, tmp.y);
                break;
            }else break; //occupied with own piece type
        }
        //check east squares
        tmp = Vector2i(slotPos.x , slotPos.y - 1);
        while(tmp.y >= 0){
            if(!gameBoard.isOccupied(tmp.x, tmp.y)){
                gameBoard.makeHighlighted(tmp.x, tmp.y);
                --tmp.y;
            }else if(gameBoard.isOccupiedWithEnemy(tmp.x, tmp.y, m_pieceId)){
                gameBoard.makeHighlighted(tmp.x, tmp.y);
                break;
            }else break; //occupied with own piece type
        }
        //check west squares
        tmp = Vector2i(slotPos.x , slotPos.y + 1);
        while(tmp.y < ChessBoard::BOARD_WIDTH){
            if(!gameBoard.isOccupied(tmp.x,tmp.y)){
                gameBoard.makeHighlighted(tmp.x, tmp.y);
                ++tmp.y;
            }else if(gameBoard.isOccupiedWithEnemy(tmp.x, tmp.y, m_pieceId)){
                gameBoard.makeHighlighted(tmp.x, tmp.y);
                break;
            }else break; //occupied with own piece type
        }
        tmp = Vector2i(slotPos.x - 1, slotPos.y - 1);
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