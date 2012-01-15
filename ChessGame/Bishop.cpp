//
//  Bishop.cpp
//  ChessGame
//
//  Created by Dibash Chhetri on 1/14/12.
//  Copyright (c) 2012 University of Connecticut. All rights reserved.
//

#include "Bishop.h"

namespace ChessGame 
{
    Bishop::Bishop(){
        m_pieceType = BISHOP;
        m_sprite.SetImage(ChessPieceImageManager::getBishopImage());
    }
    //draws the chess piece
    void Bishop::draw(sf::RenderWindow&)const{
        
    }
    
    //moves the chess piece to the new location
    void Bishop::animateTo(const sf::Vector2f& offsetPosition){
        
    }
    
    //shows possible move location of where the piece could move to
    void Bishop::showPossibleMoveLocation(ChessBoard& gameBoard)const{
        
    }
}
