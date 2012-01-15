//
//  Bishop.h
//  ChessGame
//
//  Created by Dibash Chhetri on 1/14/12.
//  Copyright (c) 2012 University of Connecticut. All rights reserved.
//

#ifndef ChessGame_Bishop_h
#define ChessGame_Bishop_h

#include "ChessPiece.h"
#include "ChessBoard.h"

namespace ChessGame 
{
    
    class Bishop : public IChessPiece
    {
    public:
        Bishop();
        
        //draws the chess piece
        void draw(sf::RenderWindow&)const ;
        
        //moves the chess piece to the new location
        void animateTo(const sf::Vector2f& offsetPosition) ;
        
        //shows possible move location of where the piece could move to
        void showPossibleMoveLocation(ChessBoard& gameBoard)const;
    private:
        
    };
    
}

#endif
