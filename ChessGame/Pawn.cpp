//
//  Pawn.cpp
//  ChessGame
//
//  Created by Dibash Chhetri on 1/9/12.
//  Copyright (c) 2012 University of Connecticut. All rights reserved.
//

#include "Pawn.h"
#include "ChessPieceImageManager.h"

namespace ChessGame {
    
    Pawn::Pawn(){
        m_pieceType = PAWN;
        m_sprite.SetImage(ChessPieceImageManager::getPawnImage());
        
    }
    
    //draws the chess piece
    void Pawn::draw(sf::RenderWindow& canvas)const {
        canvas.Draw(m_sprite);
    }
    
    //moves the chess piece to the new location
    void Pawn::animateTo(const sf::Vector2f& offsetPosition) {
        m_sprite.Move(offsetPosition);
    }
    
    //shows possible move location of where the piece could move to
    void Pawn::showPossibleMoveLocation(ChessBoard& gameBoard){
        sf::Vector2i spritePos( int(m_sprite.GetPosition().x),int(m_sprite.GetPosition().y));
        sf::Vector2i slotPos = gameBoard.convertToBoardIndex(spritePos.x,spritePos.y);
        //pawn can only move forward one step unless it initial start
        //NOTE: NEED TO HANDLE DIRECTION
        if( !gameBoard.isOccupied(slotPos.x + 1, slotPos.y) ){ 
            gameBoard.makeHighlighted(slotPos.x + 1, slotPos.y);
        }
    }

}