//
//  Rook.cpp
//  ChessGame
//
//  Created by Dibash Chhetri on 1/15/12.
//  Copyright (c) 2012 University of Connecticut. All rights reserved.
//

#include "Rook.h"
#include "ChessPieceImageManager.h"

namespace ChessGame {
    Rook::Rook(){
        m_pieceType = ROOK;
        m_sprite.SetImage(ChessPieceImageManager::getRookImage());
    }
    
    //draws the chess piece
    void Rook::draw(sf::RenderWindow& canvas)const{
        canvas.Draw(m_sprite);
    }
    
    //moves the chess piece to the new location
    void Rook::animateTo(const sf::Vector2f& offsetPosition){
        m_sprite.Move(offsetPosition);
    }
    
    //shows possible move location of where the piece could move to
    void Rook::showPossibleMoveLocation(ChessBoard& gameBoard)const{
        using sf::Vector2i;
        
        Vector2i spritePos( int(m_sprite.GetPosition().x),int(m_sprite.GetPosition().y));
        Vector2i slotPos = gameBoard.convertToBoardIndex(spritePos.x,spritePos.y);

        //check north squares
        Vector2i tmp(slotPos.x - 1, slotPos.y );
        while(tmp.x >= 0){
            if(_tryToHighlight(gameBoard, tmp) == EMPTY_SLOT_HIGHLIGHTED){ 
                tmp += Vector2i(-1,0); 
            }
            else break;
        }
        //check south squares
        tmp = Vector2i(slotPos.x + 1, slotPos.y );
        while(tmp.x < ChessBoard::BOARD_HEIGHT){
            if(_tryToHighlight(gameBoard, tmp) == EMPTY_SLOT_HIGHLIGHTED){ 
                tmp += Vector2i(1,0); 
            }
            else break;
        }
        //check east squares
        tmp = Vector2i(slotPos.x , slotPos.y - 1);
        while(tmp.y >= 0){
            if(_tryToHighlight(gameBoard, tmp) == EMPTY_SLOT_HIGHLIGHTED){ 
                tmp += Vector2i(0,-1); 
            }
            else break;
        }
        //check west squares
        tmp = Vector2i(slotPos.x , slotPos.y + 1);
        while(tmp.y < ChessBoard::BOARD_WIDTH){
            if(_tryToHighlight(gameBoard, tmp) == EMPTY_SLOT_HIGHLIGHTED){ 
                tmp += Vector2i(0,1); 
            }
            else break;
        }
    }

}