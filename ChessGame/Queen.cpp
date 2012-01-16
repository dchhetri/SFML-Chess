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
        
    }
    
}