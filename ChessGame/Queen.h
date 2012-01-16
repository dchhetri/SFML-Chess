//
//  Queen.h
//  ChessGame
//
//  Created by Dibash Chhetri on 1/15/12.
//  Copyright (c) 2012 University of Connecticut. All rights reserved.
//

#ifndef ChessGame_Queen_h
#define ChessGame_Queen_h

#include "ChessPiece.h"


namespace ChessGame 
{
    class Queen : public IChessPiece
    {
    public:
        Queen();
        
        //draws the chess piece
        void draw(sf::RenderWindow&)const ;
        
        //moves the chess piece to the new location
        void animateTo(const sf::Vector2f& offsetPosition) ;
        
        //shows possible move location of where the piece could move to
        void showPossibleMoveLocation(ChessBoard& gameBoard)const;
    };
}

#endif
